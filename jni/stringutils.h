#ifndef JWINWIN_JNI_STRINGUTILS_H
#define JWINWIN_JNI_STRINGUTILS_H

#include "global.h"

WCHAR *jstringToLPWSTR(JNIEnv *env, jstring str);

jstring lpcwstrToJString(JNIEnv *env, LPCWSTR chars);

#endif /* JWINWIN_JNI_STRINGUTILS_H */
