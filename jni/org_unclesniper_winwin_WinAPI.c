#include <jni.h>
#include <string.h>
#include <windows.h>

void zeroLLHotkeyTable();

HANDLE theHeap;

JavaVM *theJVM = NULL;

jclass cls_WinAPI;
jmethodID mth_WinAPI_setRelayedLastError;

jclass cls_Enum;
jmethodID mth_Enum_ordinal;

jclass cls_OutOfMemoryError;

jclass cls_HWnd;
jfieldID fld_HWnd_handle;
jmethodID ctor_HWnd;
jmethodID mth_HWnd_getWndProcByHandle;
jmethodID mth_HWnd_registerWndProc;
jmethodID mth_HWnd_unregisterWndProc;

jclass cls_WndClassEx;
jfieldID fld_WndClassEx_style;
jfieldID fld_WndClassEx_lpfnWndProc;
jfieldID fld_WndClassEx_hIcon;
jfieldID fld_WndClassEx_hCursor;
jfieldID fld_WndClassEx_hbrBackground;
jfieldID fld_WndClassEx_lpszClassName;
jfieldID fld_WndClassEx_hIconSm;

jclass cls_HIcon;
jfieldID fld_HIcon_handle;

jclass cls_HCursor;
jfieldID fld_HCursor_handle;

jclass cls_HBrush;
jfieldID fld_HBrush_handle;

jclass cls_HMenu;
jfieldID fld_HMenu_handle;

jclass cls_WndProc;

jclass cls_HWinEventHook;
jmethodID mth_HWinEventHook_getWinEventProcByHandle;

jclass cls_WinEventProc;
jmethodID mth_WinEventProc_windowCloaked;
jmethodID mth_WinEventProc_windowCreate;
jmethodID mth_WinEventProc_windowDestroy;
jmethodID mth_WinEventProc_windowFocus;
jmethodID mth_WinEventProc_windowNameChange;
jmethodID mth_WinEventProc_windowReorder;
jmethodID mth_WinEventProc_windowShow;
jmethodID mth_WinEventProc_windowUncloaked;
jmethodID mth_WinEventProc_desktopSwitch;
jmethodID mth_WinEventProc_foreground;
jmethodID mth_WinEventProc_windowMinimizeEnd;
jmethodID mth_WinEventProc_windowMinimizeStart;
jmethodID mth_WinEventProc_windowMoveSizeEnd;
jmethodID mth_WinEventProc_windowMoveSizeStart;

jclass cls_Hotkey;
jmethodID mth_Hotkey_dispatchHandler;

jclass cls_VirtualKey;
jmethodID mth_VirtualKey_byCode;

jclass cls_WmDestroy;
jmethodID mth_WmDestroy_wmDestroy;

jclass cls_WmClose;
jmethodID mth_WmClose_wmClose;

jclass cls_WmActivateApp;
jmethodID mth_WmActivateApp_wmActivateApp;

jclass cls_WmCancelMode;
jmethodID mth_WmCancelMode_wmCancelMode;

jclass cls_WmChildActivate;
jmethodID mth_WmChildActivate_wmChildActivate;

jclass cls_WmEnable;
jmethodID mth_WmEnable_wmEnable;

jclass cls_WmEnterSizeMove;
jmethodID mth_WmEnterSizeMove_wmEnterSizeMove;

jclass cls_WmExitSizeMove;
jmethodID mth_WmExitSizeMove_wmExitSizeMove;

jclass cls_WmGetIcon;
jmethodID mth_WmGetIcon_wmGetIcon;
jclass cls_WmGetIcon_GetIconType;
jmethodID mth_WmGetIcon_GetIconType_byOrdinal;

jclass cls_WmMove;
jmethodID mth_WmMove_wmMove;

jclass cls_WmSize;
jmethodID mth_WmSize_wmSize;
jclass cls_WmSize_SizeType;
jmethodID mth_WmSize_SizeType_byOrdinal;

jclass cls_WmActivate;
jmethodID mth_WmActivate_wmActivate;
jclass cls_WmActivate_ActivateType;
jmethodID mth_WmActivate_ActivateType_byOrdinal;

jclass cls_WmSetFocus;
jmethodID mth_WmSetFocus_wmSetFocus;

jclass cls_WmKillFocus;
jmethodID mth_WmKillFocus_wmKillFocus;

jclass cls_WmSetText;
jmethodID mth_WmSetText_wmSetText;

jclass cls_WmGetText;
jmethodID mth_WmGetText_wmGetText;

jclass cls_WmGetTextLength;
jmethodID mth_WmGetTextLength_wmGetTextLength;

jclass cls_WmQueryEndSession;
jmethodID mth_WmQueryEndSession_wmQueryEndSession;

jclass cls_WmEndSession;
jmethodID mth_WmEndSession_wmEndSession;

jclass cls_WmHotkey;
jmethodID mth_WmHotkey_wmHotkey;

jclass cls_WndEnumProc;
jmethodID mth_WndEnumProc_foundWindow;

#define BEGIN_BIND_CLASS(vname, qname) \
	cls_ ## vname = (*env)->FindClass(env, qname); \
	if(cls_ ## vname) {
#define BIND_UCLASS(vname) BEGIN_BIND_CLASS(vname, "org/unclesniper/winwin/" #vname)
#define BIND_UNCLASS(ovname, ivname) \
	BEGIN_BIND_CLASS(ovname ## _ ## ivname, "org/unclesniper/winwin/" #ovname "$" #ivname)
#define END_BIND_CLASS(vname) \
		cls_ ## vname = (*env)->NewGlobalRef(env, cls_ ## vname); \
	}

#define BIND_FIELD(cvname, fvname, type) \
	fld_ ## cvname ## _ ## fvname = (*env)->GetFieldID(env, cls_ ## cvname, #fvname, type);
#define BIND_UFIELD(cvname, fvname, stname) BIND_FIELD(cvname, fvname, "Lorg/unclesniper/winwin/" #stname ";")
#define BIND_YFIELD(cvname, fvname, stname) BIND_FIELD(cvname, fvname, "Ljava/lang/" #stname ";")

#define BIND_SMETHOD(cvname, mvname, type) \
	mth_ ## cvname ## _ ## mvname = (*env)->GetStaticMethodID(env, cls_ ## cvname, #mvname, type);
#define BIND_IMETHOD(cvname, mvname, type) \
	mth_ ## cvname ## _ ## mvname = (*env)->GetMethodID(env, cls_ ## cvname, #mvname, type);
#define BIND_CTOR(cvname, type) \
	ctor_ ## cvname = (*env)->GetMethodID(env, cls_ ## cvname, "<init>", type);

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_WinAPI_initNative(JNIEnv *env, jclass clazz) {
	BEGIN_BIND_CLASS(Enum, "java/lang/Enum")
		BIND_IMETHOD(Enum, ordinal, "()I")
	END_BIND_CLASS(Enum)
	BEGIN_BIND_CLASS(OutOfMemoryError, "java/lang/OutOfMemoryError")
	END_BIND_CLASS(OutOfMemoryError)
	BIND_UCLASS(WinAPI)
		BIND_SMETHOD(WinAPI, setRelayedLastError, "(I)V")
	END_BIND_CLASS(WinAPI)
	BIND_UCLASS(HWnd)
		BIND_FIELD(HWnd, handle, "J")
		BIND_CTOR(HWnd, "(J)V")
		BIND_SMETHOD(HWnd, getWndProcByHandle, "(J)Lorg/unclesniper/winwin/WndProc;")
		BIND_SMETHOD(HWnd, registerWndProc, "(JLorg/unclesniper/winwin/WndProc;)V")
		BIND_SMETHOD(HWnd, unregisterWndProc, "(J)V")
	END_BIND_CLASS(HWnd)
	BIND_UCLASS(WndClassEx)
		BIND_FIELD(WndClassEx, style, "I")
		BIND_UFIELD(WndClassEx, lpfnWndProc, WndProc)
		BIND_UFIELD(WndClassEx, hIcon, HIcon)
		BIND_UFIELD(WndClassEx, hCursor, HCursor)
		BIND_UFIELD(WndClassEx, hbrBackground, HBrush)
		BIND_YFIELD(WndClassEx, lpszClassName, String)
		BIND_UFIELD(WndClassEx, hIconSm, HIcon)
	END_BIND_CLASS(WndClassEx)
	BIND_UCLASS(HIcon)
		BIND_FIELD(HIcon, handle, "J")
	END_BIND_CLASS(HIcon)
	BIND_UCLASS(HCursor)
		BIND_FIELD(HCursor, handle, "J")
	END_BIND_CLASS(HCursor)
	BIND_UCLASS(HBrush)
		BIND_FIELD(HBrush, handle, "J")
	END_BIND_CLASS(HBrush)
	BIND_UCLASS(HMenu)
		BIND_FIELD(HMenu, handle, "J")
	END_BIND_CLASS(HMenu)
	BIND_UCLASS(WndProc)
	END_BIND_CLASS(WndProc)
	BIND_UCLASS(HWinEventHook)
		BIND_SMETHOD(HWinEventHook, getWinEventProcByHandle, "(J)Lorg/unclesniper/winwin/WinEventProc;")
	END_BIND_CLASS(HWinEventHook)
	BIND_UCLASS(WinEventProc)
		BIND_IMETHOD(WinEventProc, windowCloaked, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, windowCreate, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, windowDestroy, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, windowFocus, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, windowNameChange, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, windowReorder, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, windowShow, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, windowUncloaked, "(Lorg/unclesniper/winwin/HWnd;J)V")
		BIND_IMETHOD(WinEventProc, desktopSwitch, "(J)V")
		BIND_IMETHOD(WinEventProc, foreground, "(Lorg/unclesniper/winwin/HWnd;)V")
		BIND_IMETHOD(WinEventProc, windowMinimizeEnd, "(Lorg/unclesniper/winwin/HWnd;)V")
		BIND_IMETHOD(WinEventProc, windowMinimizeStart, "(Lorg/unclesniper/winwin/HWnd;)V")
		BIND_IMETHOD(WinEventProc, windowMoveSizeEnd, "(Lorg/unclesniper/winwin/HWnd;)V")
		BIND_IMETHOD(WinEventProc, windowMoveSizeStart, "(Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WinEventProc)
	BIND_UCLASS(Hotkey)
		BIND_SMETHOD(Hotkey, dispatchHandler, "(JIIS)V")
	END_BIND_CLASS(Hotkey)
	BIND_UCLASS(VirtualKey)
		BIND_SMETHOD(VirtualKey, byCode, "(S)Lorg/unclesniper/winwin/VirtualKey;")
	END_BIND_CLASS(VirtualKey)
	BIND_UCLASS(WmDestroy)
		BIND_IMETHOD(WmDestroy, wmDestroy, "(Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmDestroy)
	BIND_UCLASS(WmClose)
		BIND_IMETHOD(WmClose, wmClose, "(Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmClose)
	BIND_UCLASS(WmActivateApp)
		BIND_IMETHOD(WmActivateApp, wmActivateApp, "(Lorg/unclesniper/winwin/HWnd;Z)V")
	END_BIND_CLASS(WmActivateApp)
	BIND_UCLASS(WmCancelMode)
		BIND_IMETHOD(WmCancelMode, wmCancelMode, "(Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmCancelMode)
	BIND_UCLASS(WmChildActivate)
		BIND_IMETHOD(WmChildActivate, wmChildActivate, "(Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmChildActivate)
	BIND_UCLASS(WmEnable)
		BIND_IMETHOD(WmEnable, wmEnable, "(Lorg/unclesniper/winwin/HWnd;Z)V")
	END_BIND_CLASS(WmEnable)
	BIND_UCLASS(WmEnterSizeMove)
		BIND_IMETHOD(WmEnterSizeMove, wmEnterSizeMove, "(Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmEnterSizeMove)
	BIND_UCLASS(WmExitSizeMove)
		BIND_IMETHOD(WmExitSizeMove, wmExitSizeMove, "(Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmExitSizeMove)
	BIND_UCLASS(WmGetIcon)
		BIND_IMETHOD(WmGetIcon, wmGetIcon, "(Lorg/unclesniper/winwin/HWnd;"
				"Lorg/unclesniper/winwin/WmGetIcon$GetIconType;I)Lorg/unclesniper/winwin/HIcon;")
	END_BIND_CLASS(WmGetIcon)
	BIND_UNCLASS(WmGetIcon, GetIconType)
		BIND_SMETHOD(WmGetIcon_GetIconType, byOrdinal, "(I)Lorg/unclesniper/winwin/WmGetIcon$GetIconType;")
	END_BIND_CLASS(WmGetIcon_GetIconType)
	BIND_UCLASS(WmMove)
		BIND_IMETHOD(WmMove, wmMove, "(Lorg/unclesniper/winwin/HWnd;II)V")
	END_BIND_CLASS(WmMove)
	BIND_UCLASS(WmSize)
		BIND_IMETHOD(WmSize, wmSize, "(Lorg/unclesniper/winwin/HWnd;Lorg/unclesniper/winwin/WmSize$SizeType;II)V")
	END_BIND_CLASS(WmSize)
	BIND_UNCLASS(WmSize, SizeType)
		BIND_SMETHOD(WmSize_SizeType, byOrdinal, "(I)Lorg/unclesniper/winwin/WmSize$SizeType;")
	END_BIND_CLASS(WmSize_SizeType)
	BIND_UCLASS(WmActivate)
		BIND_IMETHOD(WmActivate, wmActivate, "(Lorg/unclesniper/winwin/HWnd;Lorg/unclesniper/winwin/HWnd;"
				"Lorg/unclesniper/winwin/WmActivate$ActivateType;Z)V")
	END_BIND_CLASS(WmActivate)
	BIND_UNCLASS(WmActivate, ActivateType)
		BIND_SMETHOD(WmActivate_ActivateType, byOrdinal, "(I)Lorg/unclesniper/winwin/WmActivate$ActivateType;")
	END_BIND_CLASS(WmActivate_ActivateType)
	BIND_UCLASS(WmSetFocus)
		BIND_IMETHOD(WmSetFocus, wmSetFocus, "(Lorg/unclesniper/winwin/HWnd;Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmSetFocus)
	BIND_UCLASS(WmKillFocus)
		BIND_IMETHOD(WmKillFocus, wmKillFocus, "(Lorg/unclesniper/winwin/HWnd;Lorg/unclesniper/winwin/HWnd;)V")
	END_BIND_CLASS(WmKillFocus)
	BIND_UCLASS(WmSetText)
		BIND_IMETHOD(WmSetText, wmSetText, "(Lorg/unclesniper/winwin/HWnd;Ljava/lang/String;)"
				"Lorg/unclesniper/winwin/WmSetText$SetTextResult;")
	END_BIND_CLASS(WmSetText)
	BIND_UCLASS(WmGetText)
		BIND_IMETHOD(WmGetText, wmGetText, "(Lorg/unclesniper/winwin/HWnd;)Ljava/lang/String;")
	END_BIND_CLASS(WmGetText)
	BIND_UCLASS(WmGetTextLength)
		BIND_IMETHOD(WmGetTextLength, wmGetTextLength, "(Lorg/unclesniper/winwin/HWnd;)I")
	END_BIND_CLASS(WmGetTextLength)
	BIND_UCLASS(WmQueryEndSession)
		BIND_IMETHOD(WmQueryEndSession, wmQueryEndSession, "(Lorg/unclesniper/winwin/HWnd;I)Z")
	END_BIND_CLASS(WmQueryEndSession)
	BIND_UCLASS(WmEndSession)
		BIND_IMETHOD(WmEndSession, wmEndSession, "(Lorg/unclesniper/winwin/HWnd;ZI)V")
	END_BIND_CLASS(WmEndSession)
	BIND_UCLASS(WmHotkey)
		BIND_IMETHOD(WmHotkey, wmHotkey, "(Lorg/unclesniper/winwin/HWnd;IILorg/unclesniper/winwin/VirtualKey;)V")
	END_BIND_CLASS(WmHotkey)
	BIND_UCLASS(WndEnumProc)
		BIND_IMETHOD(WndEnumProc, foundWindow, "(Lorg/unclesniper/winwin/HWnd;)Z")
	END_BIND_CLASS(WndEnumProc)
	(*env)->GetJavaVM(env, &theJVM);
	theHeap = GetProcessHeap();
	/*
	zeroLLHotkeyTable();
	*/
}

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_WinAPI_getLastError(JNIEnv *env, jclass clazz) {
	return (jint)GetLastError();
}

JNIEXPORT jstring JNICALL Java_org_unclesniper_winwin_WinAPI_rawErrorMessageFromCode(JNIEnv *env,
		jclass clazz, jint errorCode) {
	WCHAR *buffer;
	jstring message;
	size_t len;
	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, (DWORD)errorCode,
			(DWORD)0u, (LPWSTR)&buffer, (DWORD)0u, NULL))
		return NULL;
	len = wcslen(buffer);
	if(len > (size_t)2u && buffer[len - 2] == (WCHAR)'\r' && buffer[len - 1] == (WCHAR)'\n')
		len -= (size_t)2u;
	message = (*env)->NewString(env, (const jchar*)buffer, (jsize)len);
	LocalFree(buffer);
	return message;
}
