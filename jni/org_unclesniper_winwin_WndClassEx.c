#include "global.h"

static LRESULT CALLBACK commonWndproc(HWND win, UINT msg, WPARAM wparam, LPARAM lparam) {
	JNIEnv *env;
	jobject cbobj, winwrap;
	if((*theJVM)->GetEnv(theJVM, (void**)&env, JNI_VERSION_1_8) != JNI_OK)
		return DefWindowProc(win, msg, wparam, lparam);
	cbobj = (*env)->CallStaticObjectMethod(env, cls_HWnd, mth_HWnd_getWndProcByHandle, (jlong)win);
	if(!cbobj)
		return DefWindowProc(win, msg, wparam, lparam);
	switch(msg) {
		case WM_DESTROY:
			(*env)->CallStaticVoidMethod(env, cls_HWnd, mth_HWnd_unregisterWndProc, (jlong)win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE) {
				winwrap = wrapWndHandle(env, win);
				if((*env)->ExceptionCheck(env) == JNI_FALSE)
					(*env)->CallVoidMethod(env, cbobj, mth_WmDestroy_wmDestroy, winwrap);
			}
			return (LRESULT)0;
		case WM_CLOSE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmClose_wmClose, winwrap);
			return (LRESULT)0;
		default:
		skip:
			return DefWindowProc(win, msg, wparam, lparam);
	}
}

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_WndClassEx_registerClassExImpl(JNIEnv *env, jobject clswrap) {
	WNDCLASSEX info;
	jobject child;
	jstring className;
	ATOM atom;
	ZeroMemory(&info, (SIZE_T)sizeof(info));
	info.cbSize = (UINT)sizeof(info);
	info.style = (UINT)(*env)->GetIntField(env, clswrap, fld_WndClassEx_style);
	info.lpfnWndProc = commonWndproc;
	info.cbClsExtra = info.cbWndExtra = 0;
	info.hInstance = NULL;
	child = (*env)->GetObjectField(env, clswrap, fld_WndClassEx_hIcon);
	info.hIcon = child ? getIconHandle(env, child) : NULL;
	child = (*env)->GetObjectField(env, clswrap, fld_WndClassEx_hCursor);
	info.hCursor = child ? getCursorHandle(env, child) : NULL;
	child = (*env)->GetObjectField(env, clswrap, fld_WndClassEx_hbrBackground);
	info.hbrBackground = child ? getBrushHandle(env, child) : NULL;
	info.lpszMenuName = NULL;
	className = (*env)->GetObjectField(env, clswrap, fld_WndClassEx_lpszClassName);
	if(className) {
		info.lpszClassName = (*env)->GetStringUTFChars(env, className, NULL);
		if(!info.lpszClassName)
			return (jint)0;
	}
	else
		info.lpszClassName = "jwinwinStubClass";
	child = (*env)->GetObjectField(env, clswrap, fld_WndClassEx_hIconSm);
	info.hIconSm = child ? getIconHandle(env, child) : NULL;
	atom = RegisterClassEx(&info);
	if(className)
		(*env)->ReleaseStringUTFChars(env, className, info.lpszClassName);
	return (jint)atom;
}
