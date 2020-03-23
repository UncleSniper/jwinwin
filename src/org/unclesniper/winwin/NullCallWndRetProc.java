package org.unclesniper.winwin;

public class NullCallWndRetProc implements CallWndRetProc {

	public NullCallWndRetProc() {}

	@Override
	public void wmShowWindow(HWnd hwnd, boolean shown, ShowWindow reason) {}

}
