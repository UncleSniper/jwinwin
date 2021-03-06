package org.unclesniper.winwin;

public final class Msg {

	private static final int NATIVE_WM_USER = 0x0400;

	private static final int WM_UNBLOCK_GETMESSAGE = NATIVE_WM_USER;

	private static final int WM_STOP_HOOKING = WM_UNBLOCK_GETMESSAGE + 1;

	private static final int WM_KEY_HOOK_EVENT = WM_STOP_HOOKING + 1;

	private static final int CWPR_SHOWWINDOW_EVENT = WM_KEY_HOOK_EVENT + 1;

	public static final int WM_USER = CWPR_SHOWWINDOW_EVENT + 1;

	private Msg() {}

	public static native boolean pumpOne();

	public static native void pumpAll();

	public static native void postQuitMessage(int status);

	public static void postQuitMessageToThread(long threadId, int status) {
		if(!Msg.postQuitMessageToThreadImpl(threadId, status))
			throw new WindowsException("Failed to post quit message to thread");
	}

	private static native boolean postQuitMessageToThreadImpl(long threadId, int status);

}
