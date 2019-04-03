#include <shlwapi.h>

#include "stringutils.h"

static LRESULT CALLBACK commonWndproc(HWND win, UINT msg, WPARAM wparam, LPARAM lparam) {
	JNIEnv *env;
	jobject cbobj, winwrap, objresult, shuntobj, otherwinwrap;
	jstring string;
	jint intval;
	const jchar *jstrchars;
	HICON icnhndl;
	int i;
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
			shuntobj = (*env)->CallStaticObjectMethod(env, cls_WmGetIcon_GetIconType,
					mth_WmGetIcon_GetIconType_byOrdinal, (jint)wparam);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			objresult = (*env)->CallObjectMethod(env, cbobj, mth_WmGetIcon_wmGetIcon,
					winwrap, shuntobj, (jint)lparam);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			icnhndl = objresult ? getIconHandle(env, objresult) : NULL;
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			return (LRESULT)icnhndl;
		case WM_MOVE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmMove_wmMove, winwrap,
						(jint)(short)LOWORD(lparam), (jint)(short)HIWORD(lparam));
			return (LRESULT)0;
		case WM_SIZE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			shuntobj = (*env)->CallStaticObjectMethod(env, cls_WmSize_SizeType,
					mth_WmSize_SizeType_byOrdinal, (jint)wparam);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmSize_wmSize, winwrap, shuntobj,
						(jint)(short)LOWORD(lparam), (jint)(short)HIWORD(lparam));
			return (LRESULT)0;
		case WM_ACTIVATE:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			if(lparam) {
				otherwinwrap = wrapWndHandle(env, (HWND)lparam);
				if((*env)->ExceptionCheck(env) != JNI_FALSE)
					return (LRESULT)0;
			}
			else
				otherwinwrap = NULL;
			shuntobj = (*env)->CallStaticObjectMethod(env, cls_WmActivate_ActivateType,
					mth_WmActivate_ActivateType_byOrdinal, (jint)LOWORD(wparam));
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				(*env)->CallVoidMethod(env, cbobj, mth_WmActivate_wmActivate, winwrap, otherwinwrap,
						shuntobj, HIWORD(wparam) ? JNI_TRUE : JNI_FALSE);
			return (LRESULT)0;
		case WM_SETFOCUS:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			if(wparam) {
				otherwinwrap = wrapWndHandle(env, (HWND)wparam);
				if((*env)->ExceptionCheck(env) != JNI_FALSE)
					return (LRESULT)0;
			}
			else
				otherwinwrap = NULL;
			(*env)->CallVoidMethod(env, cbobj, mth_WmSetFocus_wmSetFocus, winwrap, otherwinwrap);
			return (LRESULT)0;
		case WM_KILLFOCUS:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			if(wparam) {
				otherwinwrap = wrapWndHandle(env, (HWND)wparam);
				if((*env)->ExceptionCheck(env) != JNI_FALSE)
					return (LRESULT)0;
			}
			else
				otherwinwrap = NULL;
			(*env)->CallVoidMethod(env, cbobj, mth_WmKillFocus_wmKillFocus, winwrap, otherwinwrap);
			return (LRESULT)0;
		case WM_SETTEXT:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)FALSE;
			string = lpcwstrToJString(env, (LPCWSTR)lparam);
			if(!string)
				return (LRESULT)FALSE;
			objresult = (*env)->CallObjectMethod(env, cbobj, mth_WmSetText_wmSetText, winwrap, string);
			if(!objresult || (*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)FALSE;
			intval = (*env)->CallIntMethod(env, objresult, mth_Enum_ordinal);
			switch((int)intval) {
				case 0:
				default:
					return (LRESULT)FALSE;
				case 1:
					return (LRESULT)TRUE;
				case 2:
					return (LRESULT)LB_ERRSPACE;
				case 3:
					return (LRESULT)CB_ERRSPACE;
				case 4:
					return (LRESULT)CB_ERR;
			}
		case WM_GETTEXT:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)FALSE;
			objresult = (*env)->CallObjectMethod(env, cbobj, mth_WmGetText_wmGetText, winwrap);
			if(!objresult || (*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			i = (int)(*env)->GetStringLength(env, objresult) + 1;
			if((WPARAM)i > wparam)
				i = (int)wparam;
			jstrchars = (*env)->GetStringChars(env, objresult, NULL);
			if(i > 1)
				StrCpyNW((PWSTR)lparam, (PCWSTR)jstrchars, i - 1);
			if(i)
				((PWSTR)lparam)[i - 1] = (WCHAR)0;
			(*env)->ReleaseStringChars(env, objresult, jstrchars);
			return (LRESULT)i;
		case WM_GETTEXTLENGTH:
			winwrap = wrapWndHandle(env, win);
			if((*env)->ExceptionCheck(env) != JNI_FALSE)
				return (LRESULT)0;
			intval = (*env)->CallIntMethod(env, cbobj, mth_WmGetTextLength_wmGetTextLength, winwrap);
			if((*env)->ExceptionCheck(env) == JNI_FALSE)
				return (LRESULT)0;
			return (LRESULT)intval;
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
