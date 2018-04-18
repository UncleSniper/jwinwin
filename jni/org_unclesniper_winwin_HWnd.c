#include "global.h"

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_HWnd_closeWindow(JNIEnv *env, jobject winwrap) {
	HWND hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return (jint)0;
	return CloseWindow(hwnd) ? (jint)0 : (jint)GetLastError();
}
