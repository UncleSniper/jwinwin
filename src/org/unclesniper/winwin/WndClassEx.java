package org.unclesniper.winwin;

public final class WndClassEx {

	static {
		WinAPI.init();
	}

	public static final int CS_BYTEALIGNCLIENT = 0x1000;
	public static final int CS_BYTEALIGNWINDOW = 0x2000;
	public static final int CS_CLASSDC = 0x0040;
	public static final int CS_DBLCLKS = 0x0008;
	public static final int CS_DROPSHADOW = 0x00020000;
	public static final int CS_GLOBALCLASS = 0x4000;
	public static final int CS_HREDRAW = 0x0002;
	public static final int CS_NOCLOSE = 0x0200;
	public static final int CS_OWNDC = 0x0020;
	public static final int CS_PARENTDC = 0x0080;
	public static final int CS_SAVEBITS = 0x0800;
	public static final int CS_VREDRAW = 0x0001;

	public int style;

	public WndProc lpfnWndProc;

	public HIcon hIcon;

	public HCursor hCursor;

	public HBrush hbrBackground;

	public String lpszClassName;

	public HIcon hIconSm;

	public WndClassEx() {}

	public ClassAtom registerClassEx() {
		int atom = registerClassExImpl();
		if(atom == 0)
			throw new WindowsException("Failed to register window class");
		return new ClassAtom(atom, lpfnWndProc);
	}

	private native int registerClassExImpl();

}
