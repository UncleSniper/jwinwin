package org.unclesniper.winwin;

public final class DefWindowProc {

	private DefWindowProc() {}

	public static native void wmDestroy(HWnd hwnd);

	public static native void wmClose(HWnd hwnd);

}
