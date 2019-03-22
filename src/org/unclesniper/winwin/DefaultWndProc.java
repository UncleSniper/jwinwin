package org.unclesniper.winwin;

public class DefaultWndProc implements WndProc {

	public static final DefaultWndProc instance = new DefaultWndProc();

	public DefaultWndProc() {}

	public void wmDestroy(HWnd hwnd) {
		DefWindowProc.wmDestroy(hwnd);
	}

	public void wmClose(HWnd hwnd) {
		DefWindowProc.wmClose(hwnd);
	}

	public void wmActivateApp(HWnd hwnd, boolean activated) {
		DefWindowProc.wmActivateApp(hwnd, activated);
	}

	public void wmCancelMode(HWnd hwnd) {
		DefWindowProc.wmCancelMode(hwnd);
	}

	public void wmChildActivate(HWnd hwnd) {
		DefWindowProc.wmChildActivate(hwnd);
	}

	public void wmEnable(HWnd hwnd, boolean enabled) {
		DefWindowProc.wmEnable(hwnd, enabled);
	}

	public void wmEnterSizeMove(HWnd hwnd) {
		DefWindowProc.wmEnterSizeMove(hwnd);
	}

	public void wmExitSizeMove(HWnd hwnd) {
		DefWindowProc.wmExitSizeMove(hwnd);
	}

	public HIcon wmGetIcon(HWnd hwnd, GetIconType type, int dpi) {
		return DefWindowProc.wmGetIcon(hwnd, type, dpi);
	}

	public void wmMove(HWnd hwnd, int x, int y) {
		DefWindowProc.wmMove(hwnd, x, y);
	}

	public void wmSize(HWnd hwnd, SizeType type, int width, int height) {
		DefWindowProc.wmSize(hwnd, type, width, height);
	}

	public void wmActivate(HWnd hwnd, HWnd other, ActivateType type, boolean minimized) {
		DefWindowProc.wmActivate(hwnd, other, type, minimized);
	}

}
