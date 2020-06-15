#include "winmac.h"
#include "global.h"

HWND getWndHandle(JNIEnv *env, jobject winwrap) {
	return (HWND)(*env)->GetLongField(env, winwrap, fld_HWnd_handle);
}

HICON getIconHandle(JNIEnv *env, jobject iconwrap) {
	return (HICON)(*env)->GetLongField(env, iconwrap, fld_HIcon_handle);
}

HCURSOR getCursorHandle(JNIEnv *env, jobject curwrap) {
	return (HCURSOR)(*env)->GetLongField(env, curwrap, fld_HCursor_handle);
}

HBRUSH getBrushHandle(JNIEnv *env, jobject brshwrap) {
	return (HBRUSH)(*env)->GetLongField(env, brshwrap, fld_HBrush_handle);
}

jobject wrapWndHandle(JNIEnv *env, HWND handle) {
	return (*env)->NewObject(env, cls_HWnd, ctor_HWnd, (jlong)handle);
}

int setRelayedLastError(JNIEnv *env, int check) {
	DWORD error;
	error = GetLastError();
	if(check & SRE_CHECK_BEFORE) {
		if((*env)->ExceptionCheck(env) != JNI_FALSE)
			return 0;
	}
	(*env)->CallStaticVoidMethod(env, cls_WinAPI, mth_WinAPI_setRelayedLastError, (jint)error);
	if(check & SRE_CHECK_AFTER) {
		if((*env)->ExceptionCheck(env) != JNI_FALSE)
			return 0;
	}
	return 1;
}
