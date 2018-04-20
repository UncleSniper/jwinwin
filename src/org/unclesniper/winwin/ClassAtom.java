package org.unclesniper.winwin;

public final class ClassAtom {

	private final int atom;

	private final WndProc wndproc;

	ClassAtom(int atom, WndProc wndproc) {
		this.atom = atom;
		this.wndproc = wndproc;
	}

	int getAtom() {
		return atom;
	}

	public WndProc getWndProc() {
		return wndproc;
	}

	public HWnd createWindowEx(int dwExStyle, String lpWindowName,
			int dwStyle, int x, int y, int nWidth, int nHeight, HWnd hWndParent, HMenu hMenu) {
		return HWnd.createWindowEx(dwExStyle, this, lpWindowName, dwStyle,
				x, y, nWidth, nHeight, hWndParent, hMenu);
	}

}
