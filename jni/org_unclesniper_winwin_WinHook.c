#include "winmac.h"
#include "global.h"
#include "org_unclesniper_winwin_Msg.h"
#include "org_unclesniper_winwin_WinHook.h"

#define WM_STOP_HOOKING ((UINT)org_unclesniper_winwin_Msg_WM_STOP_HOOKING)
#define WM_KEY_HOOK_EVENT ((UINT)org_unclesniper_winwin_Msg_WM_KEY_HOOK_EVENT)
#define CWPR_SHOWWINDOW_EVENT ((UINT)org_unclesniper_winwin_Msg_CWPR_SHOWWINDOW_EVENT)

static ATOM hookClassAtom = (ATOM)0;
static HWND hookRelayWindow = NULL;

#define UMODST_ALT   0001
#define UMODST_CTRL  0002
#define UMODST_SHIFT 0004
#define UMODST_WIN   0010
#define UMODST_MASK  0017

typedef enum llhotkey_kind_t {
	LLHK_NONE,
	LLHK_WINDOW,
	LLHK_THREAD
} llhotkey_kind_t;

#define LLHK_FL_DOWN 001

typedef struct llhotkey_t {
	llhotkey_kind_t kind;
	union {
		HWND windowID;
		DWORD threadID;
	};
	int hotkeyID;
	int flags;
} llhotkey_t;

static llhotkey_t llhotkeys[4096];

void zeroLLHotkeyTable() {
	ZeroMemory(llhotkeys, (SIZE_T)sizeof(llhotkeys));
}

static void doSwallowHotkeyFixup(UINT modifiers, UINT vk) {
	INPUT keys[2];
	WORD breakVk;
	switch(modifiers) {
		case UMODST_ALT:
		case UMODST_WIN:
			break;
		default:
			return;
	}
	switch(vk) {
		case VK_LCONTROL:
		case VK_RCONTROL:
			breakVk = VK_LSHIFT;
			break;
		default:
			breakVk = VK_LCONTROL;
			break;
	}
	ZeroMemory(keys, (SIZE_T)sizeof(keys));
	keys[0].type = INPUT_KEYBOARD;
	keys[0].ki.wVk = breakVk;
	keys[1].type = INPUT_KEYBOARD;
	keys[1].ki.wVk = breakVk;
	keys[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput((UINT)2u, keys, (int)sizeof(INPUT));
}

static LRESULT CALLBACK hookWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	UINT modifiers, vk;
	unsigned index, down;
	volatile llhotkey_t *hotkey;
	JNIEnv *env;
	if(hwnd != hookRelayWindow)
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	switch(uMsg) {
		case WM_KEY_HOOK_EVENT:
			modifiers = (UINT)(wParam >> 8);
			modifiers &= (UINT)UMODST_MASK;
			vk = (UINT)(wParam & (WPARAM)0xFF);
			down = !!(lParam & (LPARAM)0x100);
			index = (unsigned)vk * 16u + (unsigned)modifiers;
			hotkey = llhotkeys + index;
			lParam = (LPARAM)modifiers;
			if(down)
				lParam |= (LPARAM)vk << 16;
			switch(hotkey->kind) {
				case LLHK_WINDOW:
					PostMessageW(hotkey->windowID, WM_HOTKEY, (WPARAM)hotkey->hotkeyID, lParam);
					break;
				case LLHK_THREAD:
					PostThreadMessageW(hotkey->threadID, WM_HOTKEY, (WPARAM)hotkey->hotkeyID, lParam);
					break;
				default:
					return (LRESULT)0;
			}
			if(down) {
				hotkey->flags |= LLHK_FL_DOWN;
				doSwallowHotkeyFixup(modifiers, vk);
			}
			else {
				if(!(hotkey->flags & LLHK_FL_DOWN))
					return (LRESULT)0;
				hotkey->flags &= ~LLHK_FL_DOWN;
			}
			return (LRESULT)1;
		case CWPR_SHOWWINDOW_EVENT:
			if((*theJVM)->GetEnv(theJVM, (void**)&env, JNI_VERSION_1_8) != JNI_OK)
				return (LRESULT)0;
			(*env)->CallStaticVoidMethod(env, cls_WinHook, mth_WinHook_dispatchCallWndRetProcShowWindow,
					(jlong)lParam, (jint)wParam);
			return (LRESULT)0;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

#define MODST_LALT   0001
#define MODST_LCTRL  0002
#define MODST_LSHIFT 0004
#define MODST_LWIN   0010
#define MODST_LALL   0017
#define MODST_RALT   0020
#define MODST_RCTRL  0040
#define MODST_RSHIFT 0100
#define MODST_RWIN   0200
#define MODST_RALL   0360

static volatile int modState;
static volatile int haveModState;

static void makeModState() {
	modState = 0;
#define key(vk, bit) \
	if(GetAsyncKeyState(vk) >> 1) \
		modState |= bit;
	key(VK_LSHIFT, MODST_LSHIFT)
	key(VK_RSHIFT, MODST_RSHIFT)
	key(VK_LCONTROL, MODST_LCTRL)
	key(VK_RCONTROL, MODST_RCTRL)
	key(VK_LWIN, MODST_LWIN)
	key(VK_RWIN, MODST_RWIN)
	key(VK_LMENU, MODST_LALT)
	key(VK_RMENU, MODST_RALT)
#undef key
	haveModState = 1;
}

static int doKeyboardLLHook(UINT msg, const KBDLLHOOKSTRUCT *info) {
	int bit, swallow;
	WPARAM wParam;
	LPARAM lParam;
	if(!haveModState)
		makeModState();
	/* WPARAM:
	 *   +---------+----+
	 *   | modmask | vk |
	 *   +---------+----+
	 * LPARAM:
	 *   +---+---+------+--------+
	 *   | ? | ? | down | hwscan |
	 *   +---+---+------+--------+
	 */
	wParam = (WPARAM)((modState & MODST_LALL) | (modState >> 4));
	wParam = (wParam << 8) | (WPARAM)info->vkCode;
	lParam = (LPARAM)info->scanCode | (LPARAM)((msg == WM_KEYDOWN) << 8);
	swallow = (int)SendMessageW(hookRelayWindow, WM_KEY_HOOK_EVENT, wParam, lParam);
	switch(info->vkCode) {
#define key(vk, mbit) \
	case vk: \
		bit = mbit; \
		break;
		key(VK_LSHIFT, MODST_LSHIFT)
		key(VK_RSHIFT, MODST_RSHIFT)
		key(VK_LCONTROL, MODST_LCTRL)
		key(VK_RCONTROL, MODST_RCTRL)
		key(VK_LWIN, MODST_LWIN)
		key(VK_RWIN, MODST_RWIN)
		key(VK_LMENU, MODST_LALT)
		key(VK_RMENU, MODST_RALT)
#undef key
		default:
			bit = 0;
			break;
	}
	switch(msg) {
		case WM_KEYDOWN:
			modState |= bit;
			break;
		case WM_KEYUP:
			modState &= ~bit;
			break;
	}
	return swallow;
}

LRESULT CALLBACK keyboardLLHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if(!nCode && hookRelayWindow) {
		switch(wParam) {
			case WM_KEYDOWN:
			case WM_KEYUP:
				if(doKeyboardLLHook((UINT)wParam, (const KBDLLHOOKSTRUCT*)lParam))
					return (LRESULT)1;
				break;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK callWndRetProcHook(int nCode, WPARAM wParam, LPARAM lParam) {
	const CWPRETSTRUCT *info;
	if(!nCode && hookRelayWindow) {
		info = (const CWPRETSTRUCT*)lParam;
		switch(info->message) {
			case WM_SHOWWINDOW:
				wParam = (WPARAM)(info->lParam & (LPARAM)07);
				if(info->wParam)
					wParam |= (WPARAM)010;
				PostMessageW(hookRelayWindow, CWPR_SHOWWINDOW_EVENT, wParam, (LPARAM)info->hwnd);
				break;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_WinHook_doYaThang(JNIEnv *env, jclass clazz, jint types) {
	static int dummy;
	MEMORY_BASIC_INFORMATION mbi;
	HINSTANCE instance;
	WNDCLASSEX clinfo;
	HHOOK llkbHook, cwprHook;
	MSG msg;
	if(!VirtualQuery(&dummy, &mbi, (SIZE_T)sizeof(mbi))) {
		setRelayedLastError(env, 0);
		return JNI_FALSE;
	}
	instance = (HINSTANCE)mbi.AllocationBase;
	if(!hookClassAtom) {
		ZeroMemory(&clinfo, (SIZE_T)sizeof(clinfo));
		clinfo.cbSize = (UINT)sizeof(clinfo);
		clinfo.lpfnWndProc = hookWndProc;
		clinfo.lpszClassName = L"jwinwin_hook_relay";
		hookClassAtom = RegisterClassExW(&clinfo);
		if(!hookClassAtom) {
			setRelayedLastError(env, 0);
			return JNI_FALSE;
		}
	}
	if(!hookRelayWindow) {
		hookRelayWindow = CreateWindowExW((DWORD)0u, (LPCWSTR)(intptr_t)hookClassAtom, L"jwinwin_hook_relay",
				(DWORD)0u, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
		if(!hookRelayWindow) {
			setRelayedLastError(env, 0);
			return JNI_FALSE;
		}
	}
	if(types & org_unclesniper_winwin_WinHook_WH_KEYBOARD_LL) {
		haveModState = 0;
		llkbHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardLLHook, instance, (DWORD)0u);
		if(!llkbHook) {
			setRelayedLastError(env, 0);
			return JNI_FALSE;
		}
	}
	else
		llkbHook = NULL;
	if(types & org_unclesniper_winwin_WinHook_WH_CALLWNDPROCRET) {
		cwprHook = SetWindowsHookEx(WH_CALLWNDPROCRET, callWndRetProcHook, instance, (DWORD)0u);
		if(!cwprHook) {
			setRelayedLastError(env, 0);
			if(llkbHook)
				UnhookWindowsHookEx(llkbHook);
			return JNI_FALSE;
		}
	}
	else
		cwprHook = NULL;
	while(GetMessage(&msg, NULL, (UINT)0u, (UINT)0u)) {
		if(msg.message == WM_STOP_HOOKING && msg.hwnd == hookRelayWindow)
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if(llkbHook && !UnhookWindowsHookEx(llkbHook)) {
		setRelayedLastError(env, 0);
		if(cwprHook)
			UnhookWindowsHookEx(cwprHook);
		return JNI_FALSE;
	}
	if(cwprHook && !UnhookWindowsHookEx(cwprHook)) {
		setRelayedLastError(env, 0);
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_WinHook_sendStopMessage(JNIEnv *env, jclass clazz) {
	if(PostMessageW(hookRelayWindow, WM_STOP_HOOKING, (WPARAM)0, (LPARAM)0))
		return JNI_TRUE;
	setRelayedLastError(env, 0);
	return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_WinHook_registerLowLevelHotKeyImpl(JNIEnv *env,
		jclass clazz, jlong hwnd, jint id, jint modifiers, jshort key) {
	unsigned index;
	volatile llhotkey_t *hotkey;
	index = (unsigned)key * 16u + ((unsigned)modifiers & (unsigned)UMODST_MASK);
	hotkey = llhotkeys + index;
	if(hotkey->kind != LLHK_NONE)
		return JNI_FALSE;
	hotkey->hotkeyID = (int)id;
	if(hwnd) {
		hotkey->windowID = (HWND)hwnd;
		hotkey->kind = LLHK_WINDOW;
	}
	else {
		hotkey->threadID = GetCurrentThreadId();
		hotkey->kind = LLHK_THREAD;
	}
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_WinHook_unregisterLowLevelHotKeyImpl(JNIEnv *env,
		jclass clazz, jint modifiers, jshort key) {
	unsigned index;
	volatile llhotkey_t *hotkey;
	index = (unsigned)key * 16u + ((unsigned)modifiers & (unsigned)UMODST_MASK);
	hotkey = llhotkeys + index;
	if(hotkey->kind == LLHK_NONE)
		return JNI_FALSE;
	hotkey->kind = LLHK_NONE;
	return JNI_TRUE;
}
