package org.unclesniper.winwin;

public class DebugWndProc implements WndProc {

	private WndProc slave;

	public DebugWndProc(WndProc slave) {
		this.slave = slave;
	}

	public WndProc getSlave() {
		return slave;
	}

	public void setSlave(WndProc slave) {
		this.slave = slave;
	}

	private static String hwndMsg(HWnd hwnd) {
		return hwnd == null ? "hwnd = NULL" : "hwnd = 0x" + Long.toHexString(hwnd.getHandle());
	}

	public void wmDestroy(HWnd hwnd) {
		System.err.println("WM_DESTROY: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmDestroy(hwnd);
	}

	public void wmClose(HWnd hwnd) {
		System.err.println("WM_CLOSE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmDestroy(hwnd);
	}

	public void wmActivateApp(HWnd hwnd, boolean activated) {
		System.err.println("WM_ACTIVATEAPP: " + DebugWndProc.hwndMsg(hwnd) + ", activated = " + activated);
		if(slave != null)
			slave.wmActivateApp(hwnd, activated);
	}

	public void wmCancelMode(HWnd hwnd) {
		System.err.println("WM_CANCELMODE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmCancelMode(hwnd);
	}

	public void wmChildActivate(HWnd hwnd) {
		System.err.println("WM_CHILDACTIVATE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmChildActivate(hwnd);
	}

	public void wmEnable(HWnd hwnd, boolean enabled) {
		System.err.println("WM_ENABLE: " + DebugWndProc.hwndMsg(hwnd) + ", enabled = " + enabled);
		if(slave != null)
			slave.wmEnable(hwnd, enabled);
	}

	public void wmEnterSizeMove(HWnd hwnd) {
		System.err.println("WM_ENTERSIZEMOVE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmEnterSizeMove(hwnd);
	}

	public void wmExitSizeMove(HWnd hwnd) {
		System.err.println("WM_EXITSIZEMOVE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmExitSizeMove(hwnd);
	}

	public HIcon wmGetIcon(HWnd hwnd, GetIconType type, int dpi) {
		String prefix = "WM_GETICON: " + DebugWndProc.hwndMsg(hwnd) + ", type = " + type.name() + ", dpi = " + dpi;
		if(slave != null) {
			HIcon icon = slave.wmGetIcon(hwnd, type, dpi);
			System.err.print(prefix + " => ");
			System.err.println(icon == null ? "NULL" : "0x" + Long.toHexString(icon.getHandle()));
			return icon;
		}
		else {
			System.err.println(prefix);
			return null;
		}
	}

	public void wmMove(HWnd hwnd, int x, int y) {
		System.err.println("WM_MOVE: " + DebugWndProc.hwndMsg(hwnd) + ", x = " + x + ", y = " + y);
		if(slave != null)
			slave.wmMove(hwnd, x, y);
	}

	public void wmSize(HWnd hwnd, SizeType type, int width, int height) {
		System.err.println("WM_SIZE: " + DebugWndProc.hwndMsg(hwnd) + ", type = " + type.name()
				+ ", width = " + width + ", height = " + height);
		if(slave != null)
			slave.wmSize(hwnd, type, width, height);
	}

}
