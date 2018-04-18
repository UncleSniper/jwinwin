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

}
