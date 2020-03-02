#include "global.h"

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Hotkey_registerHotKeyImpl(JNIEnv *env, jclass clazz,
		jlong win, jint id, jint modifiers, jshort key) {
	if(RegisterHotKey((HWND)win, (int)id, (UINT)modifiers, (UINT)key))
		return JNI_TRUE;
	setRelayedLastError(env, 0);
	return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Hotkey_unregisterHotKeyImpl(JNIEnv *env, jclass clazz,
		jlong win, jint id) {
	if(UnregisterHotKey((HWND)win, (int)id))
		return JNI_TRUE;
	setRelayedLastError(env, 0);
	return JNI_FALSE;
}
