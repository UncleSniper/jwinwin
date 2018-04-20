#include <jni.h>
#include <windows.h>

HANDLE theHeap;

JavaVM *theJVM = NULL;

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

#define BEGIN_BIND_CLASS(vname, qname) \
	cls_ ## vname = (*env)->FindClass(env, qname); \
	if(cls_ ## vname) {
#define BIND_UCLASS(vname) BEGIN_BIND_CLASS(vname, "org/unclesniper/winwin/" #vname)
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
	(*env)->GetJavaVM(env, &theJVM);
	theHeap = GetProcessHeap();
}

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_WinAPI_getLastError(JNIEnv *env, jclass clazz) {
	return (jint)GetLastError();
}

JNIEXPORT jstring JNICALL Java_org_unclesniper_winwin_WinAPI_rawErrorMessageFromCode(JNIEnv *env,
		jclass clazz, jint errorCode) {
	char *buffer;
	jstring message;
	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, (DWORD)errorCode,
			(DWORD)0u, (LPTSTR)&buffer, (DWORD)0u, NULL))
		return NULL;
	message = (*env)->NewStringUTF(env, buffer);
	LocalFree(buffer);
	return message;
}
