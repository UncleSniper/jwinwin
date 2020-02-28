package org.unclesniper.winwin;

public final class Msg {

	private static final int NATIVE_WM_USER = 0x0400;

	private static final int WM_UNBLOCK_GETMESSAGE = NATIVE_WM_USER;

	public static final int WM_USER = WM_UNBLOCK_GETMESSAGE;

	private Msg() {}

	public static native boolean pumpOne();

	public static native void pumpAll();

	public static native void postQuitMessage(int status);

}
