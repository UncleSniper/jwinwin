#include "global.h"

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Hotkey_registerHotKeyImpl(JNIEnv *env, jclass clazz,
		jlong win, jint id, jint modifiers, jshort key) {
	return RegisterHotKey((HWND)win, (int)id, (UINT)modifiers, (UINT)key) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Hotkey_unregisterHotKeyImpl(JNIEnv *env, jclass clazz,
		jlong win, jint id) {
	return UnregisterHotKey((HWND)win, (int)id) ? JNI_TRUE : JNI_FALSE;
}
