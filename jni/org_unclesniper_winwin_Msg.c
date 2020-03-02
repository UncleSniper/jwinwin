#include "global.h"

static int doHotkey(JNIEnv *env, const MSG *msg) {
	(*env)->CallStaticVoidMethod(env, cls_Hotkey, mth_Hotkey_dispatchHandler,
			(jlong)msg->hwnd, (jint)msg->wParam, (jint)msg->lParam);
	return (*env)->ExceptionCheck(env) == JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Msg_pumpOne(JNIEnv *env, jclass clazz) {
	MSG msg;
	if(!GetMessage(&msg, NULL, (UINT)0u, (UINT)0u))
		return JNI_FALSE;
	if(msg.message == WM_HOTKEY) {
		if(!doHotkey(env, &msg))
			return JNI_FALSE;
		if(!msg.hwnd)
			return JNI_TRUE;
	}
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return JNI_TRUE;
}

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_Msg_pumpAll(JNIEnv *env, jclass clazz) {
	MSG msg;
	while(GetMessage(&msg, NULL, (UINT)0u, (UINT)0u)) {
		if(msg.message == WM_HOTKEY) {
			if(!doHotkey(env, &msg))
				return;
			if(!msg.hwnd)
				continue;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if((*env)->ExceptionCheck(env) != JNI_FALSE)
			return;
	}
}

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_Msg_postQuitMessage(JNIEnv *env, jclass clazz, jint status) {
	PostQuitMessage((int)status);
}
