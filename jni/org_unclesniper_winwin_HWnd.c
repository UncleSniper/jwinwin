#include <limits.h>

#include "winevent.h"
#include "hashtable.h"
#include "stringutils.h"
#include "org_unclesniper_winwin_Msg.h"
#include "org_unclesniper_winwin_HWinEventHook.h"

#define SYMBOLIC_CW_USEDEFAULT INT32_MIN
#define SYMBOLIC_HWND_MESSAGE INT64_MIN

#ifndef EVENT_OBJECT_CLOAKED
#define EVENT_OBJECT_CLOAKED 0x8017
#endif /* EVENT_OBJECT_CLOAKED */
#ifndef EVENT_OBJECT_UNCLOAKED
#define EVENT_OBJECT_UNCLOAKED 0x8018
#endif /* EVENT_OBJECT_UNCLOAKED */
#ifndef EVENT_SYSTEM_DESKTOPSWITCH
#define EVENT_SYSTEM_DESKTOPSWITCH 0x0020
#endif /* EVENT_SYSTEM_DESKTOPSWITCH */

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_HWnd_closeWindow(JNIEnv *env, jobject winwrap) {
	HWND hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return (jint)0;
	return CloseWindow(hwnd) ? (jint)0 : (jint)GetLastError();
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_HWnd_showWindowImpl(JNIEnv *env,
		jobject winwrap, jint nCmdShow) {
	HWND hwnd = getWndHandle(env, winwrap);
	return hwnd && ShowWindow(hwnd, (int)nCmdShow) ? JNI_TRUE : JNI_FALSE;
}

static jlong createWindowExCommon(JNIEnv *env,
		jint dwExStyle, LPCWSTR lpClassName, jstring lpWindowName, jint dwStyle, jint x, jint y,
		jint nWidth, jint nHeight, jlong hWndParent, jlong hMenu) {
	HWND parent, hwnd;
	WCHAR *titleChars;
	int wax, wawidth;
	if(lpWindowName) {
		titleChars = jstringToLPWSTR(env, lpWindowName);
		if(!titleChars)
			return (jlong)0;
	}
	else
		titleChars = NULL;
	wax = x == SYMBOLIC_CW_USEDEFAULT ? CW_USEDEFAULT : (int)x;
	wawidth = nWidth == SYMBOLIC_CW_USEDEFAULT ? CW_USEDEFAULT : (int)nWidth;
	parent = hWndParent == SYMBOLIC_HWND_MESSAGE ? HWND_MESSAGE : (HWND)hWndParent;
	if((*env)->ExceptionCheck(env) != JNI_FALSE)
		return (jlong)0;
	hwnd = CreateWindowEx((DWORD)dwExStyle, lpClassName, titleChars, (DWORD)dwStyle,
			wax, (int)y, wawidth, (int)nHeight, parent, (HMENU)hMenu, NULL, NULL);
	if(titleChars)
		HeapFree(theHeap, (DWORD)0u, titleChars);
	return (jlong)hwnd;
}

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_HWnd_createWindowExByClassAtom(JNIEnv *env, jclass clazz,
		jint dwExStyle, jint lpClassName, jstring lpWindowName, jint dwStyle, jint x, jint y,
		jint nWidth, jint nHeight, jlong hWndParent, jlong hMenu) {
	return createWindowExCommon(env, dwExStyle, (LPCWSTR)(intptr_t)lpClassName, lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu);
}

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_HWnd_createWindowExByClassName(JNIEnv *env, jclass clazz,
		jint dwExStyle, jstring lpClassName, jstring lpWindowName, jint dwStyle, jint x, jint y,
		jint nWidth, jint nHeight, jlong hWndParent, jlong hMenu) {
	WCHAR *classChars;
	LPCWSTR className;
	jlong hwnd;
	if(lpClassName) {
		classChars = jstringToLPWSTR(env, lpClassName);
		if(!classChars)
			return (jlong)0;
		className = classChars;
	}
	else {
		classChars = NULL;
		className = L"jwinwinStubClass";
	}
	hwnd = createWindowExCommon(env, dwExStyle, className, lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu);
	if(classChars)
		HeapFree(theHeap, (DWORD)0u, classChars);
	return hwnd;
}

struct HWnd_enumWindows {
	JNIEnv *env;
	jobject callback;
};

static BOOL CALLBACK HWnd_enumWindows_cb(HWND hwnd, LPARAM lparam) {
	const struct HWnd_enumWindows *cookie;
	jobject winwrap;
	jboolean result;
	cookie = (const struct HWnd_enumWindows*)lparam;
	winwrap = wrapWndHandle(cookie->env, hwnd);
	if((*cookie->env)->ExceptionCheck(cookie->env) != JNI_FALSE)
		return FALSE;
	result = (*cookie->env)->CallBooleanMethod(cookie->env, cookie->callback, mth_WndEnumProc_foundWindow, winwrap);
	if(result == JNI_FALSE || (*cookie->env)->ExceptionCheck(cookie->env) != JNI_FALSE)
		return FALSE;
	(*cookie->env)->DeleteLocalRef(cookie->env, winwrap);
	return TRUE;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_HWnd_enumWindowsImpl(JNIEnv *env, jclass clazz,
		jobject callback) {
	struct HWnd_enumWindows cookie;
	SetLastError((DWORD)0u);
	cookie.env = env;
	cookie.callback = callback;
	return EnumWindows(HWnd_enumWindows_cb, (LPARAM)&cookie) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jstring JNICALL Java_org_unclesniper_winwin_HWnd_getWindowTextImpl(JNIEnv *env, jobject winwrap) {
	HWND hwnd;
	int length;
	unsigned size;
	WCHAR *buffer;
	jstring result;
	hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return NULL;
	SetLastError((DWORD)0u);
	length = GetWindowTextLengthW(hwnd);
	if(!length)
		return NULL;
	if(++length < 0)
		--length;
	size = (unsigned)length * (unsigned)sizeof(WCHAR);
	if(size / (unsigned)sizeof(WCHAR) != (unsigned)length) {
		size = ~((unsigned)sizeof(WCHAR) - 1u);
		length = (int)(size / (unsigned)sizeof(WCHAR));
	}
	buffer = (WCHAR*)HeapAlloc(theHeap, (DWORD)0, (SIZE_T)size);
	if(!buffer)
		return NULL;
	SetLastError((DWORD)0u);
	length = GetWindowTextW(hwnd, buffer, length);
	if(!length)
		return NULL;
	result = lpcwstrToJString(env, buffer);
	HeapFree(theHeap, (DWORD)0u, buffer);
	return result;
}

JNIEXPORT jstring JNICALL Java_org_unclesniper_winwin_HWnd_getClassNameImpl(JNIEnv *env, jobject winwrap) {
	HWND hwnd;
	int length, next_length, copied;
	unsigned size;
	WCHAR *buffer, *next_buffer;
	jstring result;
	hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return NULL;
	SetLastError((DWORD)0u);
	/* Now it gets nasty, since there is no way to determine how much space we need... */
	length = 127;
	size = 127u * (unsigned)sizeof(WCHAR);
	buffer = NULL;
	for(;;) {
		next_buffer = (WCHAR*)HeapAlloc(theHeap, (DWORD)0, (SIZE_T)size);
		if(!next_buffer)
			break;
		copied = GetClassNameW(hwnd, next_buffer, length);
		if(!copied) {
			HeapFree(theHeap, (DWORD)0u, next_buffer);
			break;
		}
		if(buffer)
			HeapFree(theHeap, (DWORD)0u, buffer);
		if(copied < length - 1) {
			/* We definitely got all of it now. */
			result = lpcwstrToJString(env, next_buffer);
			HeapFree(theHeap, (DWORD)0u, next_buffer);
			return result;
		}
		/* We might not have all of it yet. */
		buffer = next_buffer;
		next_length = length * 2;
		if(next_length < length)
			next_length = INT_MAX;
		if(next_length <= length)
			break;
		size = (unsigned)next_length * (unsigned)sizeof(WCHAR);
		if(size / (unsigned)sizeof(WCHAR) != (unsigned)next_length) {
			size = ~((unsigned)sizeof(WCHAR) - 1u);
			next_length = (int)(size / (unsigned)sizeof(WCHAR));
			if(next_length <= length)
				break;
		}
		length = next_length;
	}
	if(!buffer)
		return NULL;
	result = lpcwstrToJString(env, buffer);
	HeapFree(theHeap, (DWORD)0u, buffer);
	return result;
}

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_HWnd_getForegroundWindowImpl(JNIEnv *env, jclass clazz) {
	return (jlong)GetForegroundWindow();
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_HWnd_setForegroundWindowImpl(JNIEnv *env, jclass clazz,
		jlong handle, jboolean force) {
	int alt_pressed;
	INPUT input;
	BOOL result;
	if(force != JNI_FALSE) {
		alt_pressed = !!(GetAsyncKeyState(VK_MENU) >> 1);
		if(!alt_pressed) {
			memset(&input, 0, sizeof(input));
			input.type = INPUT_KEYBOARD;
			input.ki.wVk = VK_MENU;
			if(SendInput((UINT)1u, &input, (int)sizeof(input)))
				Sleep((DWORD)100u);
			else
				alt_pressed = 1;
		}
	}
	result = SetForegroundWindow((HWND)handle);
	if(force != JNI_FALSE && !alt_pressed) {
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput((UINT)1u, &input, (int)sizeof(input));
	}
	return result ? JNI_TRUE : JNI_FALSE;
}

static int shouldPostWinEvent(DWORD event, LONG idObject) {
	switch(event) {
		case EVENT_OBJECT_CLOAKED:
		case EVENT_OBJECT_CREATE:
		case EVENT_OBJECT_DESTROY:
		case EVENT_OBJECT_FOCUS:
		case EVENT_OBJECT_NAMECHANGE:
		case EVENT_OBJECT_REORDER:
		case EVENT_OBJECT_SHOW:
		case EVENT_OBJECT_UNCLOAKED:
			return idObject == OBJID_WINDOW;
		case EVENT_SYSTEM_DESKTOPSWITCH:
		case EVENT_SYSTEM_FOREGROUND:
		case EVENT_SYSTEM_MINIMIZEEND:
		case EVENT_SYSTEM_MINIMIZESTART:
		case EVENT_SYSTEM_MOVESIZEEND:
		case EVENT_SYSTEM_MOVESIZESTART:
			return 1;
		default:
			return 0;
	}
}

#define WM_WINEVENT_RECEIVED ((UINT)org_unclesniper_winwin_Msg_WM_WINEVENT_RECEIVED)

static void CALLBACK winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject,
		LONG idChild, DWORD idEventThread, DWORD dwmsEventTime) {
	winevent_t *info;
	jlong receiver;
	/* There is no end to this nonsense; we really need to mask the stream... */
	if(!shouldPostWinEvent(event, idObject))
		return;
	if(!get_hashtable(&winevent_hashtable, (jlong)hWinEventHook, &receiver))
		return;
	/* If the node has been nixed by erase_hashtable(), skip the event. */
	if(!receiver)
		return;
	info = (winevent_t*)HeapAlloc(theHeap, (DWORD)0, (SIZE_T)sizeof(winevent_t));
	if(!info)
		return;
	info->event = event;
	info->hwnd = hwnd;
	info->idObject = idObject;
	info->idChild = idChild;
	info->idEventThread = idEventThread;
	info->dwmsEventTime = dwmsEventTime;
	if(!PostMessageW((HWND)receiver, WM_WINEVENT_RECEIVED, (WPARAM)0, (LPARAM)info))
		HeapFree(theHeap, (DWORD)0u, info);
}

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_HWnd_setWinEventHookImpl(JNIEnv *env, jclass clazz,
		jlong recipient, jint eventMin, jint eventMax, jint flags) {
	DWORD wflags;
	HWINEVENTHOOK hook;
	wflags = WINEVENT_OUTOFCONTEXT;
	if(flags & org_unclesniper_winwin_HWinEventHook_WINEVENT_SKIPOWNPROCESS)
		wflags |= WINEVENT_SKIPOWNPROCESS;
	else if(flags & org_unclesniper_winwin_HWinEventHook_WINEVENT_SKIPOWNTHREAD)
		wflags |= WINEVENT_SKIPOWNTHREAD;
	SetLastError((DWORD)0u);
	hook = SetWinEventHook((DWORD)eventMin, (DWORD)eventMax, NULL, winEventProc, (DWORD)0u, (DWORD)0u, wflags);
	if(!hook)
		return (jlong)0;
	if(!put_hashtable(&winevent_hashtable, (jlong)hook, recipient)) {
		UnhookWinEvent(hook);
		(*env)->ThrowNew(env, cls_OutOfMemoryError, "Not enough memory to insert into WinEvent hashtable");
		return (jlong)0;
	}
	return (jlong)hook;
}
