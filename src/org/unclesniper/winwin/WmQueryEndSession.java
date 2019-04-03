package org.unclesniper.winwin;

public interface WmQueryEndSession {

	public static final int ENDSESSION_CLOSEAPP = 0x00000001;
	public static final int ENDSESSION_CRITICAL = 0x40000000;
	public static final int ENDSESSION_LOGOFF   = 0x80000000;

	boolean wmQueryEndSession(HWnd hwnd, int reason);

}
