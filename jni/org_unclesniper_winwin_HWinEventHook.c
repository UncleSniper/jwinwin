#include "global.h"
#include "hashtable.h"

JNIEXPORT jboolean JNICALL Java_org_unclesniper_winwin_HWinEventHook_unhookWinEventImpl(JNIEnv *env, jclass clazz,
		jlong handle) {
	SetLastError((DWORD)0u);
	if(!UnhookWinEvent((HWINEVENTHOOK)handle))
		return JNI_FALSE;
	/* In theory, there is a race condition here: If the
	 * hashnode_t is removed from the hashtable_t as
	 * the WINEVENTPROC gets the last event and finds the
	 * hashnode_t, it might end up accessing a node that
	 * has already been freed. This is why we have
	 * erase_hashtable() not free the node directly, but
	 * stuff it into hashtable_t::pending_deletion to be
	 * freed by the next call to erase_hashtable().
	 * Nonetheless, if two hooks are unregistered in
	 * succession so rapid that they outrace the kernel's
	 * "now stop calling the hook" logic, the problem
	 * may still occur. This is so vanishingly unlikely
	 * that it shouldn't be a real issue, but better safe
	 * than sorry, so wait a bit for all calls to the
	 * hook to settle.
	 */
	Sleep((DWORD)200u);
	erase_hashtable(&winevent_hashtable, handle);
	return JNI_TRUE;
}
