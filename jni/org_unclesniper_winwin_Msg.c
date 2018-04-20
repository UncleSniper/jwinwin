#include "global.h"

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Msg_pumpOne(JNIEnv *env, jclass clazz) {
	MSG msg;
	if(!GetMessage(&msg, NULL, (UINT)0u, (UINT)0u))
		return JNI_FALSE;
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return JNI_TRUE;
}

JNIEXPORT void JNICALL Java_org_unclesniper_winwin_Msg_pumpAll(JNIEnv *env, jclass clazz) {
	MSG msg;
	while(GetMessage(&msg, NULL, (UINT)0u, (UINT)0u)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}