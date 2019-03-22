#include "global.h"

#define BEGIN_VMESSAGE(mname) \
	JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_ ## mname(JNIEnv *env, \
			jclass clazz, jobject winwrap) { \
		HWND hwnd = getWndHandle(env, winwrap); \
		if(!hwnd) \
			return;

#define BEGIN_VZMESSAGE(mname) \
	JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_ ## mname(JNIEnv *env, \
			jclass clazz, jobject winwrap, jboolean truth) { \
		HWND hwnd = getWndHandle(env, winwrap); \
		if(!hwnd) \
			return;

#define END_MESSAGE }

BEGIN_VMESSAGE(wmDestroy)
	DefWindowProc(hwnd, WM_DESTROY, (WPARAM)0, (LPARAM)0);
END_MESSAGE

BEGIN_VMESSAGE(wmClose)
	DefWindowProc(hwnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
END_MESSAGE

BEGIN_VZMESSAGE(wmActivateApp)
	DefWindowProc(hwnd, WM_ACTIVATEAPP, (WPARAM)(truth ? TRUE : FALSE), (LPARAM)0u);
END_MESSAGE

BEGIN_VMESSAGE(wmCancelMode)
	DefWindowProc(hwnd, WM_CANCELMODE, (WPARAM)0, (LPARAM)0);
END_MESSAGE

BEGIN_VMESSAGE(wmChildActivate)
	DefWindowProc(hwnd, WM_CHILDACTIVATE, (WPARAM)0, (LPARAM)0);
END_MESSAGE

BEGIN_VZMESSAGE(wmEnable)
	DefWindowProc(hwnd, WM_ENABLE, (WPARAM)(truth ? TRUE : FALSE), (LPARAM)0);
END_MESSAGE

BEGIN_VMESSAGE(wmEnterSizeMove)
	DefWindowProc(hwnd, WM_ENTERSIZEMOVE, (WPARAM)0, (LPARAM)0);
END_MESSAGE

BEGIN_VMESSAGE(wmExitSizeMove)
	DefWindowProc(hwnd, WM_EXITSIZEMOVE, (WPARAM)0, (LPARAM)0);
END_MESSAGE

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmGetIconImpl(JNIEnv *env,
		jclass clazz, jlong hwnd, jint type, jint dpi) {
	return (jlong)DefWindowProc((HWND)hwnd, WM_GETICON, (WPARAM)type, (LPARAM)dpi);
}

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmMove(JNIEnv *env,
		jclass clazz, jobject winwrap, jint x, jint y) {
	HWND hwnd = getWndHandle(env, winwrap);
	WORD xw, yw;
	if(!hwnd)
		return;
	xw = (WORD)(short)x;
	yw = (WORD)(short)y;
	DefWindowProc(hwnd, WM_MOVE, (WPARAM)0, (LPARAM)((DWORD)xw | ((DWORD)yw << 16)));
}

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmSizeImpl(JNIEnv *env,
		jclass clazz, jlong hwnd, jint type, jint width, jint height) {
	WORD ww, hw;
	ww = (WORD)(short)width;
	hw = (WORD)(short)height;
	DefWindowProc((HWND)hwnd, WM_SIZE, (WPARAM)type, (LPARAM)((DWORD)ww | ((DWORD)hw << 16)));
}
