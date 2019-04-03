#include "stringutils.h"

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

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmActivateImpl(JNIEnv *env,
		jclass clazz, jlong hwnd, jlong other, jint type, jboolean minimized) {
	WORD tw, mw;
	tw = (WORD)type;
	mw = (WORD)(minimized != JNI_FALSE);
	DefWindowProc((HWND)hwnd, WM_ACTIVATE, (WPARAM)((DWORD)tw | ((DWORD)mw << 16)), (LPARAM)other);
}

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmSetFocus(JNIEnv *env,
		jclass clazz, jobject winwrap, jobject otherwinwrap) {
	HWND hwnd, ohwnd;
	hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return;
	if(otherwinwrap) {
		ohwnd = getWndHandle(env, otherwinwrap);
		if(!ohwnd)
			return;
	}
	else
		ohwnd = NULL;
	DefWindowProc(hwnd, WM_SETFOCUS, (WPARAM)ohwnd, (LPARAM)0);
}

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmKillFocus(JNIEnv *env,
		jclass clazz, jobject winwrap, jobject otherwinwrap) {
	HWND hwnd, ohwnd;
	hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return;
	if(otherwinwrap) {
		ohwnd = getWndHandle(env, otherwinwrap);
		if(!ohwnd)
			return;
	}
	else
		ohwnd = NULL;
	DefWindowProc(hwnd, WM_KILLFOCUS, (WPARAM)ohwnd, (LPARAM)0);
}

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmSetTextImpl(JNIEnv *env,
		jclass clazz, jlong hwnd, jstring text) {
	WCHAR *chars;
	LRESULT result;
	chars = jstringToLPWSTR(env, text);
	if(!chars)
		return (jint)0;
	result = DefWindowProc((HWND)hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)chars);
	HeapFree(theHeap, (DWORD)0u, chars);
	switch(result) {
		case (LRESULT)FALSE:
		default:
			return (jint)0;
		case (LRESULT)TRUE:
			return (jint)1;
		case (LRESULT)LB_ERRSPACE:
			return (jint)2;
#if LB_ERRSPACE != CB_ERRSPACE
		case (LRESULT)CB_ERRSPACE:
			return (jint)3;
#endif
		case (LRESULT)CB_ERR:
			return (jint)4;
	}
}

JNIEXPORT jstring JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmGetText(JNIEnv *env,
		jclass clazz, jobject winwrap) {
	HWND hwnd;
	WCHAR buffer[512];
	LRESULT count;
	hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return NULL;
	count = DefWindowProc(hwnd, WM_GETTEXT, (WPARAM)sizeof(buffer), (LPARAM)buffer);
	return (*env)->NewString(env, (const jchar*)buffer, (jsize)count);
}

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_DefWindowProc_wmGetTextLength(JNIEnv *env,
		jclass clazz, jobject winwrap) {
	HWND hwnd;
	hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return (jint)0;
	return (jint)DefWindowProc(hwnd, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0);
}
