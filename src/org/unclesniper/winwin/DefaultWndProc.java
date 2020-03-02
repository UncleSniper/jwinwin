package org.unclesniper.winwin;

public class DefaultWndProc implements WndProc {

	public static final DefaultWndProc instance = new DefaultWndProc();

	public DefaultWndProc() {}

	@Override
	public void wmDestroy(HWnd hwnd) {
		DefWindowProc.wmDestroy(hwnd);
	}

	@Override
	public void wmClose(HWnd hwnd) {
		DefWindowProc.wmClose(hwnd);
	}

	@Override
	public void wmActivateApp(HWnd hwnd, boolean activated) {
		DefWindowProc.wmActivateApp(hwnd, activated);
	}

	@Override
	public void wmCancelMode(HWnd hwnd) {
		DefWindowProc.wmCancelMode(hwnd);
	}

	@Override
	public void wmChildActivate(HWnd hwnd) {
		DefWindowProc.wmChildActivate(hwnd);
	}

	@Override
	public void wmEnable(HWnd hwnd, boolean enabled) {
		DefWindowProc.wmEnable(hwnd, enabled);
	}

	@Override
	public void wmEnterSizeMove(HWnd hwnd) {
		DefWindowProc.wmEnterSizeMove(hwnd);
	}

	@Override
	public void wmExitSizeMove(HWnd hwnd) {
		DefWindowProc.wmExitSizeMove(hwnd);
	}

	@Override
	public HIcon wmGetIcon(HWnd hwnd, GetIconType type, int dpi) {
		return DefWindowProc.wmGetIcon(hwnd, type, dpi);
	}

	@Override
	public void wmMove(HWnd hwnd, int x, int y) {
		DefWindowProc.wmMove(hwnd, x, y);
	}

	@Override
	public void wmSize(HWnd hwnd, SizeType type, int width, int height) {
		DefWindowProc.wmSize(hwnd, type, width, height);
	}

	@Override
	public void wmActivate(HWnd hwnd, HWnd other, ActivateType type, boolean minimized) {
		DefWindowProc.wmActivate(hwnd, other, type, minimized);
	}

	@Override
	public void wmSetFocus(HWnd hwnd, HWnd other) {
		DefWindowProc.wmSetFocus(hwnd, other);
	}

	@Override
	public void wmKillFocus(HWnd hwnd, HWnd other) {
		DefWindowProc.wmKillFocus(hwnd, other);
	}

	@Override
	public SetTextResult wmSetText(HWnd hwnd, String text) {
		return DefWindowProc.wmSetText(hwnd, text);
	}

	@Override
	public String wmGetText(HWnd hwnd) {
		return DefWindowProc.wmGetText(hwnd);
	}

	@Override
	public int wmGetTextLength(HWnd hwnd) {
		return DefWindowProc.wmGetTextLength(hwnd);
	}

	@Override
	public boolean wmQueryEndSession(HWnd hwnd, int reason) {
		return DefWindowProc.wmQueryEndSession(hwnd, reason);
	}

	@Override
	public void wmEndSession(HWnd hwnd, boolean ending, int reason) {
		DefWindowProc.wmEndSession(hwnd, ending, reason);
	}

	@Override
	public void wmHotkey(HWnd hwnd, int id, int modifiers) {
		DefWindowProc.wmHotkey(hwnd, id, modifiers);
	}

}
