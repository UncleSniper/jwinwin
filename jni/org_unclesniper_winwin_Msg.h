/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_unclesniper_winwin_Msg */

#ifndef _Included_org_unclesniper_winwin_Msg
#define _Included_org_unclesniper_winwin_Msg
#ifdef __cplusplus
extern "C" {
#endif
#undef org_unclesniper_winwin_Msg_NATIVE_WM_USER
#define org_unclesniper_winwin_Msg_NATIVE_WM_USER 1024L
#undef org_unclesniper_winwin_Msg_WM_UNBLOCK_GETMESSAGE
#define org_unclesniper_winwin_Msg_WM_UNBLOCK_GETMESSAGE 1024L
#undef org_unclesniper_winwin_Msg_WM_USER
#define org_unclesniper_winwin_Msg_WM_USER 1024L
/*
 * Class:     org_unclesniper_winwin_Msg
 * Method:    pumpOne
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Msg_pumpOne
  (JNIEnv *, jclass);

/*
 * Class:     org_unclesniper_winwin_Msg
 * Method:    pumpAll
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_unclesniper_winwin_Msg_pumpAll
  (JNIEnv *, jclass);

/*
 * Class:     org_unclesniper_winwin_Msg
 * Method:    postQuitMessage
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_unclesniper_winwin_Msg_postQuitMessage
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif
