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

	private static String hwndMsg(HWnd hwnd, String name) {
		return name + (hwnd == null ? " = NULL" : " = 0x" + Long.toHexString(hwnd.getHandle()));
	}

	@Override
	public void wmDestroy(HWnd hwnd) {
		System.err.println("WM_DESTROY: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmDestroy(hwnd);
	}

	@Override
	public void wmClose(HWnd hwnd) {
		System.err.println("WM_CLOSE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmDestroy(hwnd);
	}

	@Override
	public void wmActivateApp(HWnd hwnd, boolean activated) {
		System.err.println("WM_ACTIVATEAPP: " + DebugWndProc.hwndMsg(hwnd) + ", activated = " + activated);
		if(slave != null)
			slave.wmActivateApp(hwnd, activated);
	}

	@Override
	public void wmCancelMode(HWnd hwnd) {
		System.err.println("WM_CANCELMODE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmCancelMode(hwnd);
	}

	@Override
	public void wmChildActivate(HWnd hwnd) {
		System.err.println("WM_CHILDACTIVATE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmChildActivate(hwnd);
	}

	@Override
	public void wmEnable(HWnd hwnd, boolean enabled) {
		System.err.println("WM_ENABLE: " + DebugWndProc.hwndMsg(hwnd) + ", enabled = " + enabled);
		if(slave != null)
			slave.wmEnable(hwnd, enabled);
	}

	@Override
	public void wmEnterSizeMove(HWnd hwnd) {
		System.err.println("WM_ENTERSIZEMOVE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmEnterSizeMove(hwnd);
	}

	@Override
	public void wmExitSizeMove(HWnd hwnd) {
		System.err.println("WM_EXITSIZEMOVE: " + DebugWndProc.hwndMsg(hwnd));
		if(slave != null)
			slave.wmExitSizeMove(hwnd);
	}

	@Override
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

	@Override
	public void wmMove(HWnd hwnd, int x, int y) {
		System.err.println("WM_MOVE: " + DebugWndProc.hwndMsg(hwnd) + ", x = " + x + ", y = " + y);
		if(slave != null)
			slave.wmMove(hwnd, x, y);
	}

	@Override
	public void wmSize(HWnd hwnd, SizeType type, int width, int height) {
		System.err.println("WM_SIZE: " + DebugWndProc.hwndMsg(hwnd) + ", type = " + type.name()
				+ ", width = " + width + ", height = " + height);
		if(slave != null)
			slave.wmSize(hwnd, type, width, height);
	}

	@Override
	public void wmActivate(HWnd hwnd, HWnd other, ActivateType type, boolean minimized) {
		System.err.println("WM_ACTIVATE: " + DebugWndProc.hwndMsg(hwnd) + ", "
				+ DebugWndProc.hwndMsg(other, "other") + ", type = " + type.name() + ", minimized = " + minimized);
		if(slave != null)
			slave.wmActivate(hwnd, other, type, minimized);
	}

	@Override
	public void wmSetFocus(HWnd hwnd, HWnd other) {
		System.err.println("WM_SETFOCUS: " + DebugWndProc.hwndMsg(hwnd) + ", "
				+ DebugWndProc.hwndMsg(other, "other"));
		if(slave != null)
			slave.wmSetFocus(hwnd, other);
	}

	@Override
	public void wmKillFocus(HWnd hwnd, HWnd other) {
		System.err.println("WM_KILLFOCUS: " + DebugWndProc.hwndMsg(hwnd) + ", "
				+ DebugWndProc.hwndMsg(other, "other"));
		if(slave != null)
			slave.wmKillFocus(hwnd, other);
	}

	@Override
	public SetTextResult wmSetText(HWnd hwnd, String text) {
		String prefix = "WM_SETTEXT: " + DebugWndProc.hwndMsg(hwnd) + ", text = \"" + text + '"';
		if(slave != null) {
			SetTextResult result = slave.wmSetText(hwnd, text);
			System.err.print(prefix + " => ");
			System.err.println((result == null ? SetTextResult.FALSE : result).name());
			return result;
		}
		else {
			System.err.println(prefix);
			return SetTextResult.FALSE;
		}
	}

	@Override
	public String wmGetText(HWnd hwnd) {
		String prefix = "WM_GETTEXT: " + DebugWndProc.hwndMsg(hwnd);
		if(slave != null) {
			String text = slave.wmGetText(hwnd);
			System.err.print(prefix + " => ");
			System.err.println(text == null ? "NULL" : '"' + text + '"');
			return text;
		}
		else {
			System.err.println(prefix);
			return null;
		}
	}

	@Override
	public int wmGetTextLength(HWnd hwnd) {
		String prefix = "WM_GETTEXTLENGTH: " + DebugWndProc.hwndMsg(hwnd);
		if(slave != null) {
			int length = slave.wmGetTextLength(hwnd);
			System.err.println(prefix + " => " + length);
			return length;
		}
		else {
			System.err.println(prefix);
			return 0;
		}
	}

	@Override
	public boolean wmQueryEndSession(HWnd hwnd, int reason) {
		StringBuilder builder = new StringBuilder("WM_QUERYENDSESSION: ");
		builder.append(DebugWndProc.hwndMsg(hwnd));
		builder.append(", reason = ");
		boolean first = true;
		if((reason & WmQueryEndSession.ENDSESSION_CLOSEAPP) != 0) {
			builder.append("ENDSESSION_CLOSEAPP");
			first = false;
		}
		if((reason & WmQueryEndSession.ENDSESSION_CRITICAL) != 0) {
			if(first)
				first = false;
			else
				builder.append(" | ");
			builder.append("ENDSESSION_CRITICAL");
		}
		if((reason & WmQueryEndSession.ENDSESSION_LOGOFF) != 0) {
			if(first)
				first = false;
			else
				builder.append(" | ");
			builder.append("ENDSESSION_LOGOFF");
		}
		boolean allow;
		if(slave != null) {
			allow = slave.wmQueryEndSession(hwnd, reason);
			builder.append(" => ");
			builder.append(allow);
		}
		else
			allow = true;
		System.err.println(builder);
		return allow;
	}

}
