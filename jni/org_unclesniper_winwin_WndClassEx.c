#include "stringutils.h"

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
		case WM_ACTIVATEAPP:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmActivateApp_wmActivateApp,
						winwrap, wparam ? JNI_TRUE : JNI_FALSE);
			return (LRESULT)0;
		case WM_CANCELMODE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmCancelMode_wmCancelMode, winwrap);
			return (LRESULT)0;
		case WM_CHILDACTIVATE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmChildActivate_wmChildActivate, winwrap);
			return (LRESULT)0;
		case WM_ENABLE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmEnable_wmEnable,
						winwrap, wparam ? JNI_TRUE : JNI_FALSE);
			return (LRESULT)0;
		case WM_ENTERSIZEMOVE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmEnterSizeMove_wmEnterSizeMove, winwrap);
			return (LRESULT)0;
		case WM_EXITSIZEMOVE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmExitSizeMove_wmExitSizeMove, winwrap);
			return (LRESULT)0;
		case WM_GETICON:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			/*TODO*/
			return (LRESULT)0;
		default:
			return DefWindowProc(win, msg, wparam, lparam);
	}
}

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_WndClassEx_registerClassExImpl(JNIEnv *env, jobject clswrap) {
	WNDCLASSEX info;
	jobject child;
	jstring className;
	WCHAR *classChars;
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
		classChars = jstringToLPWSTR(env, className);
		if(!classChars)
			return (jint)0;
		info.lpszClassName = classChars;
	}
	else {
		classChars = NULL;
		info.lpszClassName = L"jwinwinStubClass";
	}
	child = (*env)->GetObjectField(env, clswrap, fld_WndClassEx_hIconSm);
	info.hIconSm = child ? getIconHandle(env, child) : NULL;
	if((*env)->ExceptionCheck(env) != JNI_FALSE) {
		if(classChars)
			HeapFree(theHeap, (DWORD)0u, classChars);
		return (jint)0;
	}
	atom = RegisterClassEx(&info);
	if(classChars)
		HeapFree(theHeap, (DWORD)0u, classChars);
	return (jint)atom;
}