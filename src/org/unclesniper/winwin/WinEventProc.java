package org.unclesniper.winwin;

public interface WinEventProc {

	void windowCloaked(HWnd hwnd, long idChild);

	void windowCreate(HWnd hwnd, long idChild);

	void windowDestroy(HWnd hwnd, long idChild);

	void windowFocus(HWnd hwnd, long idChild);

	void windowNameChange(HWnd hwnd, long idChild);

	void windowReorder(HWnd hwnd, long idChild);

	void windowShow(HWnd hwnd, long idChild);

	void windowUncloaked(HWnd hwnd, long idChild);

	void desktopSwitch(long idChild);

	void foreground(HWnd hwnd);

	void windowMinimizeEnd(HWnd hwnd);

	void windowMinimizeStart(HWnd hwnd);

	void windowMoveSizeEnd(HWnd hwnd);

	void windowMoveSizeStart(HWnd hwnd);

}
