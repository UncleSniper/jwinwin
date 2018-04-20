#include "stringutils.h"

#define SYMBOLIC_CW_USEDEFAULT INT32_MIN
#define SYMBOLIC_HWND_MESSAGE INT64_MIN

JNIEXPORT jint JNICALL Java_org_unclesniper_winwin_HWnd_closeWindow(JNIEnv *env, jobject winwrap) {
	HWND hwnd = getWndHandle(env, winwrap);
	if(!hwnd)
		return (jint)0;
	return CloseWindow(hwnd) ? (jint)0 : (jint)GetLastError();
}

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_HWnd_showWindowImpl(JNIEnv *env,
		jobject winwrap, jint nCmdShow) {
	HWND hwnd = getWndHandle(env, winwrap);
	return hwnd && ShowWindow(hwnd, (int)nCmdShow) ? JNI_TRUE : JNI_FALSE;
}

static jlong createWindowExCommon(JNIEnv *env,
		jint dwExStyle, LPCWSTR lpClassName, jstring lpWindowName, jint dwStyle, jint x, jint y,
		jint nWidth, jint nHeight, jlong hWndParent, jlong hMenu) {
	HWND parent, hwnd;
	WCHAR *titleChars;
	int wax, wawidth;
	if(lpWindowName) {
		titleChars = jstringToLPWSTR(env, lpWindowName);
		if(!titleChars)
			return (jlong)0;
	}
	else
		titleChars = NULL;
	wax = x == SYMBOLIC_CW_USEDEFAULT ? CW_USEDEFAULT : (int)x;
	wawidth = nWidth == SYMBOLIC_CW_USEDEFAULT ? CW_USEDEFAULT : (int)nWidth;
	parent = hWndParent == SYMBOLIC_HWND_MESSAGE ? HWND_MESSAGE : (HWND)hWndParent;
	if((*env)->ExceptionCheck(env) != JNI_FALSE)
		return (jlong)0;
	hwnd = CreateWindowEx((DWORD)dwExStyle, lpClassName, titleChars, (DWORD)dwStyle,
			wax, (int)y, wawidth, (int)nHeight, parent, (HMENU)hMenu, NULL, NULL);
	if(titleChars)
		HeapFree(theHeap, (DWORD)0u, titleChars);
	return (jlong)hwnd;
}

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_HWnd_createWindowExByClassAtom(JNIEnv *env, jclass clazz,
		jint dwExStyle, jint lpClassName, jstring lpWindowName, jint dwStyle, jint x, jint y,
		jint nWidth, jint nHeight, jlong hWndParent, jlong hMenu) {
	return createWindowExCommon(env, dwExStyle, (LPCWSTR)(intptr_t)lpClassName, lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu);
}

JNIEXPORT jlong JNICALL Java_org_unclesniper_winwin_HWnd_createWindowExByClassName(JNIEnv *env, jclass clazz,
		jint dwExStyle, jstring lpClassName, jstring lpWindowName, jint dwStyle, jint x, jint y,
		jint nWidth, jint nHeight, jlong hWndParent, jlong hMenu) {
	WCHAR *classChars;
	LPCWSTR className;
	jlong hwnd;
	if(lpClassName) {
		classChars = jstringToLPWSTR(env, lpClassName);
		if(!classChars)
			return (jlong)0;
		className = classChars;
	}
	else {
		classChars = NULL;
		className = L"jwinwinStubClass";
	}
	hwnd = createWindowExCommon(env, dwExStyle, className, lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu);
	if(classChars)
		HeapFree(theHeap, (DWORD)0u, classChars);
	return hwnd;
}
