#include <string.h>

#include "global.h"

WCHAR *jstringToLPWSTR(JNIEnv *env, jstring str) {
	jsize length;
	const jchar *chars;
	WCHAR *buffer;
	length = (*env)->GetStringLength(env, str);
	chars = (*env)->GetStringChars(env, str, NULL);
	if(!chars)
		return NULL;
	buffer = (WCHAR*)HeapAlloc(theHeap, (DWORD)0, ((SIZE_T)length + (SIZE_T)1u) * (SIZE_T)2u);
	if(!buffer) {
		(*env)->ReleaseStringChars(env, str, chars);
		return NULL;
	}
	memcpy(buffer, chars, (size_t)length * (size_t)2u);
	(*env)->ReleaseStringChars(env, str, chars);
	buffer[length] = (WCHAR)0;
	return buffer;
}
