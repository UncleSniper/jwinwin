package org.unclesniper.winwin;

public interface WmHotkey {

	public static final int IDHOT_SNAPDESKTOP = -2;
	public static final int IDHOT_SNAPWINDOW  = -1;

	void wmHotkey(HWnd hwnd, int id, int modifiers);

}
