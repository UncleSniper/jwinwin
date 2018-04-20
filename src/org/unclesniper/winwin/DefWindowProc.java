package org.unclesniper.winwin;

public final class DefWindowProc {

	private DefWindowProc() {}

	public static native void wmDestroy(HWnd hwnd);

	public static native void wmClose(HWnd hwnd);

	public static native void wmActivateApp(HWnd hwnd, boolean activated);

	public static native void wmCancelMode(HWnd hwnd);

	public static native void wmChildActivate(HWnd hwnd);

	public static native void wmEnable(HWnd hwnd, boolean enabled);

	public static native void wmEnterSizeMove(HWnd hwnd);

	public static native void wmExitSizeMove(HWnd hwnd);

	public static HIcon wmGetIcon(HWnd hwnd, WmGetIcon.GetIconType type, int dpi) {
		if(hwnd == null || type == null)
			return null;
		long handle = DefWindowProc.wmGetIconImpl(hwnd.getHandle(), type.ordinal(), dpi);
		return handle == 0l ? null : new HIcon(handle);
	}

	public static native long wmGetIconImpl(long hwnd, int type, int dpi);

}