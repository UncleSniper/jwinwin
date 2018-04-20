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

	public WndClassEx(String lpszClassName, WndProc lpfnWndProc) {
		this.lpszClassName = lpszClassName;
		this.lpfnWndProc = lpfnWndProc;
	}

	public WndClassEx(String lpszClassName) {
		this(lpszClassName, null);
	}

	public WndClassEx(WndProc lpfnWndProc) {
		this(null ,lpfnWndProc);
	}

	public WndClassEx withStyle(int style) {
		this.style = style;
		return this;
	}

	public WndClassEx withWndProc(WndProc lpfnWndProc) {
		this.lpfnWndProc = lpfnWndProc;
		return this;
	}

	public WndClassEx withIcon(HIcon hIcon) {
		this.hIcon = hIcon;
		return this;
	}

	public WndClassEx withCursor(HCursor hCursor) {
		this.hCursor = hCursor;
		return this;
	}

	public WndClassEx withBackground(HBrush hbrBackground) {
		this.hbrBackground = hbrBackground;
		return this;
	}

	public WndClassEx withBackground(int sysColor) {
		this.hbrBackground = new HBrush((long)sysColor + 1l);
		return this;
	}

	public WndClassEx withName(String lpszClassName) {
		this.lpszClassName = lpszClassName;
		return this;
	}

	public WndClassEx withIconSmall(HIcon hIconSm) {
		this.hIconSm = hIconSm;
		return this;
	}

	public ClassAtom registerClassEx() {
		int atom = registerClassExImpl();
		if(atom == 0)
			throw new WindowsException("Failed to register window class");
		return new ClassAtom(atom, lpfnWndProc);
	}

	private native int registerClassExImpl();

}
