#include "global.h"

#define BEGIN_VMESSAGE(mname) \
	JNIEXPORT void JNICALL Java_org_unclesniper_winwin_DefWindowProc_ ## mname(JNIEnv *env, \
			jclass clazz, jobject winwrap) { \
		HWND hwnd = getWndHandle(env, winwrap); \
		if(!hwnd) \
			return;

#define END_MESSAGE }

BEGIN_VMESSAGE(wmDestroy)
	DefWindowProc(hwnd, WM_DESTROY, (WPARAM)0, (LPARAM)0);
END_MESSAGE

BEGIN_VMESSAGE(wmClose)
	DefWindowProc(hwnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
END_MESSAGE
