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

	private static native long wmGetIconImpl(long hwnd, int type, int dpi);

	public static native void wmMove(HWnd hwnd, int x, int y);

	public static void wmSize(HWnd hwnd, WmSize.SizeType type, int width, int height) {
		if(hwnd != null && type != null)
			DefWindowProc.wmSizeImpl(hwnd.getHandle(), type.ordinal(), width, height);
	}

	private static native void wmSizeImpl(long hwnd, int type, int width, int height);

	public static void wmActivate(HWnd hwnd, HWnd other, WmActivate.ActivateType type, boolean minimized) {
		if(hwnd != null)
			DefWindowProc.wmActivateImpl(hwnd.getHandle(), other == null ? 0l : other.getHandle(),
					type.ordinal(), minimized);
	}

	private static native void wmActivateImpl(long hwnd, long other, int type, boolean minimized);

	public static native void wmSetFocus(HWnd hwnd, HWnd other);

}
