package org.unclesniper.winwin;

public final class Msg {

	private static final int NATIVE_WM_USER = 0x0400;

	public static final int WM_WINEVENT_RECEIVED = NATIVE_WM_USER;

	public static final int WM_USER = WM_WINEVENT_RECEIVED + 1;

	private Msg() {}

	public static native boolean pumpOne();

	public static native void pumpAll();

	public static native void postQuitMessage(int status);

}
