#ifndef JWINWIN_JNI_GLOBAL_H
#define JWINWIN_JNI_GLOBAL_H

#include <jni.h>
#include <stdint.h>
#include <windows.h>

extern HANDLE theHeap;

extern JavaVM *theJVM;

extern jclass cls_HWnd;
extern jfieldID fld_HWnd_handle;
extern jmethodID ctor_HWnd;
extern jmethodID mth_HWnd_getWndProcByHandle;
extern jmethodID mth_HWnd_registerWndProc;
extern jmethodID mth_HWnd_unregisterWndProc;

extern jclass cls_WndClassEx;
extern jfieldID fld_WndClassEx_style;
extern jfieldID fld_WndClassEx_lpfnWndProc;
extern jfieldID fld_WndClassEx_hIcon;
extern jfieldID fld_WndClassEx_hCursor;
extern jfieldID fld_WndClassEx_hbrBackground;
extern jfieldID fld_WndClassEx_lpszClassName;
extern jfieldID fld_WndClassEx_hIconSm;

extern jclass cls_HIcon;
extern jfieldID fld_HIcon_handle;

extern jclass cls_HCursor;
extern jfieldID fld_HCursor_handle;

extern jclass cls_HBrush;
extern jfieldID fld_HBrush_handle;

extern jclass cls_HMenu;
extern jfieldID fld_HMenu_handle;

extern jclass cls_WndProc;

extern jclass cls_WmDestroy;
extern jmethodID mth_WmDestroy_wmDestroy;

extern jclass cls_WmClose;
extern jmethodID mth_WmClose_wmClose;

extern jclass cls_WmCancelMode;
extern jmethodID mth_WmCancelMode_wmCancelMode;

extern jclass cls_WmActivateApp;
extern jmethodID mth_WmActivateApp_wmActivateApp;

extern jclass cls_WmChildActivate;
extern jmethodID mth_WmChildActivate_wmChildActivate;

extern jclass cls_WmEnable;
extern jmethodID mth_WmEnable_wmEnable;

extern jclass cls_WmEnterSizeMove;
extern jmethodID mth_WmEnterSizeMove_wmEnterSizeMove;

extern jclass cls_WmExitSizeMove;
extern jmethodID mth_WmExitSizeMove_wmExitSizeMove;

extern jclass cls_WmGetIcon;
extern jmethodID mth_WmGetIcon_wmGetIcon;
extern jclass cls_WmGetIcon_GetIconType;
extern jmethodID mth_WmGetIcon_GetIconType_byOrdinal;

extern jclass cls_WmMove;
extern jmethodID mth_WmMove_wmMove;

extern jclass cls_WmSize;
extern jmethodID mth_WmSize_wmSize;
extern jclass cls_WmSize_SizeType;
extern jmethodID mth_WmSize_SizeType_byOrdinal;

extern jclass cls_WmActivate;
extern jmethodID mth_WmActivate_wmActivate;
extern jclass cls_WmActivate_ActivateType;
extern jmethodID mth_WmActivate_ActivateType_byOrdinal;

extern jclass cls_WmSetFocus;
extern jmethodID mth_WmSetFocus_wmSetFocus;

inline HWND getWndHandle(JNIEnv *env, jobject winwrap) {
	return (HWND)(*env)->GetLongField(env, winwrap, fld_HWnd_handle);
}

inline HICON getIconHandle(JNIEnv *env, jobject iconwrap) {
	return (HICON)(*env)->GetLongField(env, iconwrap, fld_HIcon_handle);
}

inline HCURSOR getCursorHandle(JNIEnv *env, jobject curwrap) {
	return (HCURSOR)(*env)->GetLongField(env, curwrap, fld_HCursor_handle);
}

inline HBRUSH getBrushHandle(JNIEnv *env, jobject brshwrap) {
	return (HBRUSH)(*env)->GetLongField(env, brshwrap, fld_HBrush_handle);
}

inline jobject wrapWndHandle(JNIEnv *env, HWND handle) {
	return (*env)->NewObject(env, cls_HWnd, ctor_HWnd, (jlong)handle);
}

#endif /* JWINWIN_JNI_GLOBAL_H */
