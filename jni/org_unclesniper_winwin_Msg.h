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
#undef org_unclesniper_winwin_Msg_WM_STOP_HOOKING
#define org_unclesniper_winwin_Msg_WM_STOP_HOOKING 1025L
#undef org_unclesniper_winwin_Msg_WM_KEY_HOOK_EVENT
#define org_unclesniper_winwin_Msg_WM_KEY_HOOK_EVENT 1026L
#undef org_unclesniper_winwin_Msg_CWPR_SHOWWINDOW_EVENT
#define org_unclesniper_winwin_Msg_CWPR_SHOWWINDOW_EVENT 1027L
#undef org_unclesniper_winwin_Msg_WM_USER
#define org_unclesniper_winwin_Msg_WM_USER 1028L
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

/*
 * Class:     org_unclesniper_winwin_Msg
 * Method:    postQuitMessageToThreadImpl
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_Msg_postQuitMessageToThreadImpl
  (JNIEnv *, jclass, jlong, jint);

#ifdef __cplusplus
}
#endif
#endif
