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
