#include "global.h"
#include "org_unclesniper_winwin_Msg.h"
#include "org_unclesniper_winwin_HWinEventHook.h"

#define WM_UNBLOCK_GETMESSAGE ((UINT)org_unclesniper_winwin_Msg_WM_UNBLOCK_GETMESSAGE)

#ifndef EVENT_OBJECT_CLOAKED
#define EVENT_OBJECT_CLOAKED 0x8017
#endif /* EVENT_OBJECT_CLOAKED */
#ifndef EVENT_OBJECT_UNCLOAKED
#define EVENT_OBJECT_UNCLOAKED 0x8018
#endif /* EVENT_OBJECT_UNCLOAKED */
#ifndef EVENT_SYSTEM_DESKTOPSWITCH
#define EVENT_SYSTEM_DESKTOPSWITCH 0x0020
#endif /* EVENT_SYSTEM_DESKTOPSWITCH */

static int willProcessWinEvent(DWORD event, LONG idObject) {
	switch(event) {
		case EVENT_OBJECT_CLOAKED:
		case EVENT_OBJECT_CREATE:
		case EVENT_OBJECT_DESTROY:
		case EVENT_OBJECT_FOCUS:
		case EVENT_OBJECT_NAMECHANGE:
		case EVENT_OBJECT_REORDER:
		case EVENT_OBJECT_SHOW:
		case EVENT_OBJECT_UNCLOAKED:
			return idObject == OBJID_WINDOW;
		case EVENT_SYSTEM_DESKTOPSWITCH:
		case EVENT_SYSTEM_FOREGROUND:
		case EVENT_SYSTEM_MINIMIZEEND:
		case EVENT_SYSTEM_MINIMIZESTART:
		case EVENT_SYSTEM_MOVESIZEEND:
		case EVENT_SYSTEM_MOVESIZESTART:
			return 1;
		default:
			return 0;
	}
}

static void CALLBACK winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject,
		LONG idChild, DWORD idEventThread, DWORD dwmsEventTime) {
	JNIEnv *env;
	jobject cbobj, winwrap;
	if(!willProcessWinEvent(event, idObject))
		return;
	if((*theJVM)->GetEnv(theJVM, (void**)&env, JNI_VERSION_1_8) != JNI_OK)
		return;
	if((*env)->PushLocalFrame(env, (jint)5))
		return;
	cbobj = (*env)->CallStaticObjectMethod(env, cls_HWinEventHook,
			mth_HWinEventHook_getWinEventProcByHandle, (jlong)hWinEventHook);
	if(!cbobj)
		return;
#define _yankmsg \
	PostThreadMessageW(GetCurrentThreadId(), WM_UNBLOCK_GETMESSAGE, (WPARAM)0, (LPARAM)0);
#define _wrapwin \
	if(!hwnd) \
		return; \
	winwrap = wrapWndHandle(env, hwnd); \
	if((*env)->ExceptionCheck(env) != JNI_FALSE) { \
		_yankmsg; \
		return; \
	}
	switch(event) {
		case EVENT_OBJECT_CLOAKED:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowCloaked, winwrap, (jlong)idChild);
			break;
		case EVENT_OBJECT_CREATE:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowCreate, winwrap, (jlong)idChild);
			break;
		case EVENT_OBJECT_DESTROY:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowDestroy, winwrap, (jlong)idChild);
			break;
		case EVENT_OBJECT_FOCUS:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowFocus, winwrap, (jlong)idChild);
			break;
		case EVENT_OBJECT_NAMECHANGE:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowNameChange, winwrap, (jlong)idChild);
			break;
		case EVENT_OBJECT_REORDER:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowReorder, winwrap, (jlong)idChild);
			break;
		case EVENT_OBJECT_SHOW:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowShow, winwrap, (jlong)idChild);
			break;
		case EVENT_OBJECT_UNCLOAKED:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowUncloaked, winwrap, (jlong)idChild);
			break;
		case EVENT_SYSTEM_DESKTOPSWITCH:
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_desktopSwitch, (jlong)idChild);
			break;
		case EVENT_SYSTEM_FOREGROUND:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_foreground, winwrap);
			break;
		case EVENT_SYSTEM_MINIMIZEEND:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowMinimizeEnd, winwrap);
			break;
		case EVENT_SYSTEM_MINIMIZESTART:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowMinimizeStart, winwrap);
			break;
		case EVENT_SYSTEM_MOVESIZEEND:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowMoveSizeEnd, winwrap);
			break;
		case EVENT_SYSTEM_MOVESIZESTART:
			_wrapwin
			(*env)->CallVoidMethod(env, cbobj, mth_WinEventProc_windowMoveSizeStart, winwrap);
			break;
	}
	(*env)->PopLocalFrame(env, NULL);
	if((*env)->ExceptionCheck(env) != JNI_FALSE)
		_yankmsg
}

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_HWinEventHook_setWinEventHookImpl(JNIEnv *env, jclass clazz,
		jint eventMin, jint eventMax, jint flags) {
	DWORD wflags;
	HWINEVENTHOOK hook;
	wflags = WINEVENT_OUTOFCONTEXT;
	if(flags & org_unclesniper_winwin_HWinEventHook_WINEVENT_SKIPOWNPROCESS)
		wflags |= WINEVENT_SKIPOWNPROCESS;
	else if(flags & org_unclesniper_winwin_HWinEventHook_WINEVENT_SKIPOWNTHREAD)
		wflags |= WINEVENT_SKIPOWNTHREAD;
	SetLastError((DWORD)0u);
	hook = SetWinEventHook((DWORD)eventMin, (DWORD)eventMax, NULL, winEventProc, (DWORD)0u, (DWORD)0u, wflags);
	if(!hook)
		setRelayedLastError(env, 0);
	return (jlong)hook;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_HWinEventHook_unhookWinEventImpl(JNIEnv *env, jclass clazz,
		jlong handle) {
	SetLastError((DWORD)0u);
	if(UnhookWinEvent((HWINEVENTHOOK)handle))
		return JNI_TRUE;
	setRelayedLastError(env, 0);
	return JNI_FALSE;
}
