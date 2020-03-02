#ifndef JWINWIN_JNI_GLOBAL_H
#define JWINWIN_JNI_GLOBAL_H

#include <jni.h>
#include <stdint.h>
#include <windows.h>

extern HANDLE theHeap;

extern JavaVM *theJVM;

extern jclass cls_Enum;
extern jmethodID mth_Enum_ordinal;

extern jclass cls_OutOfMemoryError;

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

extern jclass cls_HWinEventHook;
extern jmethodID mth_HWinEventHook_getWinEventProcByHandle;

extern jclass cls_WinEventProc;
extern jmethodID mth_WinEventProc_windowCloaked;
extern jmethodID mth_WinEventProc_windowCreate;
extern jmethodID mth_WinEventProc_windowDestroy;
extern jmethodID mth_WinEventProc_windowFocus;
extern jmethodID mth_WinEventProc_windowNameChange;
extern jmethodID mth_WinEventProc_windowReorder;
extern jmethodID mth_WinEventProc_windowShow;
extern jmethodID mth_WinEventProc_windowUncloaked;
extern jmethodID mth_WinEventProc_desktopSwitch;
extern jmethodID mth_WinEventProc_foreground;
extern jmethodID mth_WinEventProc_windowMinimizeEnd;
extern jmethodID mth_WinEventProc_windowMinimizeStart;
extern jmethodID mth_WinEventProc_windowMoveSizeEnd;
extern jmethodID mth_WinEventProc_windowMoveSizeStart;

extern jclass cls_Hotkey;
extern jmethodID mth_Hotkey_dispatchHandler;

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

extern jclass cls_WmKillFocus;
extern jmethodID mth_WmKillFocus_wmKillFocus;

extern jclass cls_WmSetText;
extern jmethodID mth_WmSetText_wmSetText;

extern jclass cls_WmGetText;
extern jmethodID mth_WmGetText_wmGetText;

extern jclass cls_WmGetTextLength;
extern jmethodID mth_WmGetTextLength_wmGetTextLength;

extern jclass cls_WmQueryEndSession;
extern jmethodID mth_WmQueryEndSession_wmQueryEndSession;

extern jclass cls_WmEndSession;
extern jmethodID mth_WmEndSession_wmEndSession;

extern jclass cls_WmHotkey;
extern jmethodID mth_WmHotkey_wmHotkey;

extern jclass cls_WndEnumProc;
extern jmethodID mth_WndEnumProc_foundWindow;

HWND getWndHandle(JNIEnv *env, jobject winwrap);

HICON getIconHandle(JNIEnv *env, jobject iconwrap);

HCURSOR getCursorHandle(JNIEnv *env, jobject curwrap);

HBRUSH getBrushHandle(JNIEnv *env, jobject brshwrap);

jobject wrapWndHandle(JNIEnv *env, HWND handle);

#endif /* JWINWIN_JNI_GLOBAL_H */
