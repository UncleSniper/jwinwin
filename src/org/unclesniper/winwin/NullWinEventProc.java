package org.unclesniper.winwin;

public class NullWinEventProc implements WinEventProc {

	public NullWinEventProc() {}

	@Override
	public void windowCloaked(HWnd hwnd, long idChild) {}

	@Override
	public void windowCreate(HWnd hwnd, long idChild) {}

	@Override
	public void windowDestroy(HWnd hwnd, long idChild) {}

	@Override
	public void windowFocus(HWnd hwnd, long idChild) {}

	@Override
	public void windowNameChange(HWnd hwnd, long idChild) {}

	@Override
	public void windowReorder(HWnd hwnd, long idChild) {}

	@Override
	public void windowShow(HWnd hwnd, long idChild) {}

	@Override
	public void windowUncloaked(HWnd hwnd, long idChild) {}

	@Override
	public void desktopSwitch(long idChild) {}

	@Override
	public void foreground(HWnd hwnd) {}

	@Override
	public void windowMinimizeEnd(HWnd hwnd) {}

	@Override
	public void windowMinimizeStart(HWnd hwnd) {}

	@Override
	public void windowMoveSizeEnd(HWnd hwnd) {}

	@Override
	public void windowMoveSizeStart(HWnd hwnd) {}

}
