#ifndef JWINWIN_JNI_STRINGUTILS_H
#define JWINWIN_JNI_STRINGUTILS_H

#include "global.h"

WCHAR *jstringToLPWSTR(JNIEnv *env, jstring str);

jstring lpcwstrToJString(JNIEnv *env, LPCWSTR chars);

jstring lpcwstrToJStringByLength(JNIEnv *env, LPCWSTR chars, jsize length);

#endif /* JWINWIN_JNI_STRINGUTILS_H */
