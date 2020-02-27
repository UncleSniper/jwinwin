package org.unclesniper.winwin;

public class DebugWinEventProc implements WinEventProc {

	private WinEventProc slave;

	public DebugWinEventProc(WinEventProc slave) {
		this.slave = slave;
	}

	public WinEventProc getSlave() {
		return slave;
	}

	public void setSlave(WinEventProc slave) {
		this.slave = slave;
	}

	private static String hwndMsg(HWnd hwnd) {
		return hwnd == null ? "hwnd = NULL" : "hwnd = 0x" + Long.toHexString(hwnd.getHandle());
	}

	@Override
	public void windowCloaked(HWnd hwnd, long idChild) {
		System.err.println("windowCloaked: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowCloaked(hwnd, idChild);
	}

	@Override
	public void windowCreate(HWnd hwnd, long idChild) {
		System.err.println("windowCreate: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowCreate(hwnd, idChild);
	}

	@Override
	public void windowDestroy(HWnd hwnd, long idChild) {
		System.err.println("windowDestroy: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowDestroy(hwnd, idChild);
	}

	@Override
	public void windowFocus(HWnd hwnd, long idChild) {
		System.err.println("windowFocus: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowFocus(hwnd, idChild);
	}

	@Override
	public void windowNameChange(HWnd hwnd, long idChild) {
		System.err.println("windowNameChange: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowNameChange(hwnd, idChild);
	}

	@Override
	public void windowReorder(HWnd hwnd, long idChild) {
		System.err.println("windowReorder: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowReorder(hwnd, idChild);
	}

	@Override
	public void windowShow(HWnd hwnd, long idChild) {
		System.err.println("windowShow: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowShow(hwnd, idChild);
	}

	@Override
	public void windowUncloaked(HWnd hwnd, long idChild) {
		System.err.println("windowUncloaked: " + DebugWinEventProc.hwndMsg(hwnd) + ", idChild = " + idChild);
		if(slave != null)
			slave.windowUncloaked(hwnd, idChild);
	}

	@Override
	public void desktopSwitch(long idChild) {
		System.err.println("desktopSwitch: idChild = " + idChild);
		if(slave != null)
			slave.desktopSwitch(idChild);
	}

	@Override
	public void foreground(HWnd hwnd) {
		System.err.println("foreground: " + DebugWinEventProc.hwndMsg(hwnd));
		if(slave != null)
			slave.foreground(hwnd);
	}

	@Override
	public void windowMinimizeEnd(HWnd hwnd) {
		System.err.println("windowMinimizeEnd: " + DebugWinEventProc.hwndMsg(hwnd));
		if(slave != null)
			slave.windowMinimizeEnd(hwnd);
	}

	@Override
	public void windowMinimizeStart(HWnd hwnd) {
		System.err.println("windowMinimizeStart: " + DebugWinEventProc.hwndMsg(hwnd));
		if(slave != null)
			slave.windowMinimizeStart(hwnd);
	}

	@Override
	public void windowMoveSizeEnd(HWnd hwnd) {
		System.err.println("windowMoveSizeEnd: " + DebugWinEventProc.hwndMsg(hwnd));
		if(slave != null)
			slave.windowMoveSizeEnd(hwnd);
	}

	@Override
	public void windowMoveSizeStart(HWnd hwnd) {
		System.err.println("windowMoveSizeStart: " + DebugWinEventProc.hwndMsg(hwnd));
		if(slave != null)
			slave.windowMoveSizeStart(hwnd);
	}

}
