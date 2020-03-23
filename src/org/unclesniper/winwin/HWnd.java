package org.unclesniper.winwin;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public final class HWnd {

	static {
		WinAPI.init();
	}

	public enum ShowWindow {

		SW_HIDE(0),
		SW_SHOWNORMAL(1),
		SW_SHOWMINIMIZED(2),
		SW_MAXIMIZE(3),
		SW_SHOWNOACTIVATE(4),
		SW_SHOW(5),
		SW_MINIMIZE(6),
		SW_SHOWMINNOACTIVE(7),
		SW_SHOWNA(8),
		SW_RESTORE(9),
		SW_SHOWDEFAULT(10),
		SW_FORCEMINIMIZE(11),
		// And now... the reason getNumeric() is not ordinal()...
		// *drumroll*
		SW_SHOWMAXIMIZED(3);

		private final int numeric;

		private ShowWindow(int numeric) {
			this.numeric = numeric;
		}

		public int getNumeric() {
			return numeric;
		}

	}

	public static final int CW_USEDEFAULT = Integer.MIN_VALUE;

	private static final long SYMBOLIC_HWND_MESSAGE = Long.MIN_VALUE;

	public static final HWnd HWND_MESSAGE = new HWnd(HWnd.SYMBOLIC_HWND_MESSAGE);

	public static final int WS_EX_ACCEPTFILES = 0x00000010;
	public static final int WS_EX_APPWINDOW = 0x00040000;
	public static final int WS_EX_CLIENTEDGE = 0x00000200;
	public static final int WS_EX_COMPOSITED = 0x02000000;
	public static final int WS_EX_CONTEXTHELP = 0x00000400;
	public static final int WS_EX_CONTROLPARENT = 0x00010000;
	public static final int WS_EX_DLGMODALFRAME = 0x00000001;
	public static final int WS_EX_LAYERED = 0x00080000;
	public static final int WS_EX_LAYOUTRTL = 0x00400000;
	public static final int WS_EX_LEFT = 0x00000000;
	public static final int WS_EX_LEFTSCROLLBAR = 0x00004000;
	public static final int WS_EX_LTRREADING = 0x00000000;
	public static final int WS_EX_MDICHILD = 0x00000040;
	public static final int WS_EX_NOACTIVATE = 0x08000000;
	public static final int WS_EX_NOINHERITLAYOUT = 0x00100000;
	public static final int WS_EX_NOPARENTNOTIFY = 0x00000004;
	public static final int WS_EX_NOREDIRECTIONBITMAP = 0x00200000;
	public static final int WS_EX_RIGHT = 0x00001000;
	public static final int WS_EX_RIGHTSCROLLBAR = 0x00000000;
	public static final int WS_EX_RTLREADING = 0x00002000;
	public static final int WS_EX_STATICEDGE = 0x00020000;
	public static final int WS_EX_TOOLWINDOW = 0x00000080;
	public static final int WS_EX_TOPMOST = 0x00000008;
	public static final int WS_EX_TRANSPARENT = 0x00000020;
	public static final int WS_EX_WINDOWEDGE = 0x00000100;
	public static final int WS_EX_OVERLAPPEDWINDOW = WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE;
	public static final int WS_EX_PALETTEWINDOW = WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST;

	public static final int WS_BORDER = 0x00800000;
	public static final int WS_CAPTION = 0x00C00000;
	public static final int WS_CHILD = 0x40000000;
	public static final int WS_CHILDWINDOW = 0x40000000;
	public static final int WS_CLIPCHILDREN = 0x02000000;
	public static final int WS_CLIPSIBLINGS = 0x04000000;
	public static final int WS_DISABLED = 0x08000000;
	public static final int WS_DLGFRAME = 0x00400000;
	public static final int WS_GROUP = 0x00020000;
	public static final int WS_HSCROLL = 0x00100000;
	public static final int WS_ICONIC = 0x20000000;
	public static final int WS_MAXIMIZE = 0x01000000;
	public static final int WS_MAXIMIZEBOX = 0x00010000;
	public static final int WS_MINIMIZE = 0x20000000;
	public static final int WS_MINIMIZEBOX = 0x00020000;
	public static final int WS_OVERLAPPED = 0x00000000;
	public static final int WS_POPUP = 0x80000000;
	public static final int WS_SIZEBOX = 0x00040000;
	public static final int WS_SYSMENU = 0x00080000;
	public static final int WS_TABSTOP = 0x00010000;
	public static final int WS_THICKFRAME = 0x00040000;
	public static final int WS_TILED = 0x00000000;
	public static final int WS_VISIBLE = 0x10000000;
	public static final int WS_VSCROLL = 0x00200000;
	public static final int WS_OVERLAPPEDWINDOW = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
			| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	public static final int WS_POPUPWINDOW = WS_POPUP | WS_BORDER | WS_SYSMENU;
	public static final int WS_TILEDWINDOW = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
			| WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	private static final Map<Long, WndProc> KNOWN_WNDPROCS = new ConcurrentHashMap<Long, WndProc>();

	private final long handle;

	HWnd(long handle) {
		this.handle = handle;
	}

	HWnd(long handle, WndProc wndproc) {
		this.handle = handle;
		if(handle != 0l && wndproc != null)
			HWnd.registerWndProc(handle, wndproc);
	}

	long getHandle() {
		return handle;
	}

	@Override
	public boolean equals(Object other) {
		if(!(other instanceof HWnd))
			return false;
		return handle == ((HWnd)other).handle;
	}

	@Override
	public int hashCode() {
		int hi = (int)(handle >> 32), lo = (int)handle;
		return ((hi << 13) | (hi >> 19)) ^ lo;
	}

	public native int closeWindow();

	public boolean showWindow(ShowWindow nCmdShow) {
		return showWindowImpl(nCmdShow == null ? 0 : nCmdShow.getNumeric());
	}

	private native boolean showWindowImpl(int nCmdShow);

	public String getWindowText() {
		String text = getWindowTextImpl();
		if(text != null)
			return text;
		int error = WinAPI.getRelayedLastError(true);
		if(error != 0)
			throw new WindowsException("Failed to retrieve window text", error);
		return "";
	}

	private native String getWindowTextImpl();

	public String getClassName() {
		String name = getClassNameImpl();
		if(name != null)
			return name;
		int error = WinAPI.getRelayedLastError(true);
		if(error != 0)
			throw new WindowsException("Failed to retrieve window class name", error);
		return "";
	}

	private native String getClassNameImpl();

	public native boolean isWindowVisible();

	public native boolean isIconic();

	public native boolean isZoomed();

	public static HWnd createWindowEx(int dwExStyle, ClassAtom lpClassName, String lpWindowName,
			int dwStyle, int x, int y, int nWidth, int nHeight, HWnd hWndParent, HMenu hMenu) {
		long handle = HWnd.createWindowExByClassAtom(dwExStyle, lpClassName.getAtom(), lpWindowName,
				dwStyle, x, y, nWidth, nHeight, hWndParent == null ? 0l : hWndParent.handle,
				hMenu == null ? 0l : hMenu.getHandle());
		if(handle == 0l)
			throw new WindowsException("Failed to create window");
		return new HWnd(handle, lpClassName.getWndProc());
	}

	private static native long createWindowExByClassAtom(int dwExStyle, int lpClassName, String lpWindowName,
			int dwStyle, int x, int y, int nWidth, int nHeight, long hWndParent, long hMenu);

	public static HWnd createWindowEx(int dwExStyle, String lpClassName, String lpWindowName,
			int dwStyle, int x, int y, int nWidth, int nHeight, HWnd hWndParent, HMenu hMenu) {
		long handle = HWnd.createWindowExByClassName(dwExStyle, lpClassName, lpWindowName,
				dwStyle, x, y, nWidth, nHeight, hWndParent == null ? 0l : hWndParent.handle,
				hMenu == null ? 0l : hMenu.getHandle());
		if(handle == 0l)
			throw new WindowsException("Failed to create window");
		return new HWnd(handle);
	}

	private static native long createWindowExByClassName(int dwExStyle, String lpClassName, String lpWindowName,
			int dwStyle, int x, int y, int nWidth, int nHeight, long hWndParent, long hMenu);

	private static WndProc getWndProcByHandle(long handle) {
		return HWnd.KNOWN_WNDPROCS.get(handle);
	}

	private static void registerWndProc(long handle, WndProc wndproc) {
		if(wndproc != null && handle != 0l)
			HWnd.KNOWN_WNDPROCS.put(handle, wndproc);
	}

	private static void unregisterWndProc(long handle) {
		HWnd.KNOWN_WNDPROCS.remove(handle);
	}

	public boolean wasCreatedByMe() {
		return HWnd.KNOWN_WNDPROCS.containsKey(handle);
	}

	public static boolean enumWindows(WndEnumProc callback) {
		if(callback == null)
			throw new IllegalArgumentException("Callback cannot be null");
		boolean result = HWnd.enumWindowsImpl(callback);
		if(result)
			return true;
		int error = WinAPI.getRelayedLastError(true);
		if(error == 0)
			return false;
		throw new WindowsException("Failed to enumerate windows", error);
	}

	private static native boolean enumWindowsImpl(WndEnumProc callback);

	public static HWnd getForegroundWindow() {
		long win = HWnd.getForegroundWindowImpl();
		return win == 0l ? null : new HWnd(win);
	}

	private static native long getForegroundWindowImpl();

	public static boolean setForegroundWindow(HWnd hwnd, boolean force) {
		return HWnd.setForegroundWindowImpl(hwnd == null ? 0l : hwnd.handle, force);
	}

	private static native boolean setForegroundWindowImpl(long handle, boolean force);

	public static HWnd findWindow(String className, String windowName) {
		long hwnd = HWnd.findWindowImpl(className, windowName);
		if(hwnd != 0l)
			return new HWnd(hwnd);
		int code = WinAPI.getRelayedLastError(true);
		if(code == 0)
			return null;
		throw new WindowsException("Failed to find window", code);
	}

	private static native long findWindowImpl(String className, String windowName);

	@Override
	public String toString() {
		return "0x" + Long.toHexString(handle);
	}

	public static void main(String[] args) {
		new WndClassEx(new DebugWndProc(new DefaultWndProc())).withBackground(WinAPI.COLOR_WINDOW)
				.registerClassEx()
				.createWindowEx(0, "Hello, world!", HWnd.WS_OVERLAPPEDWINDOW | HWnd.WS_VISIBLE,
						HWnd.CW_USEDEFAULT, 0, 800, 600, null, null)
				.showWindow(ShowWindow.SW_SHOW);
		Msg.pumpAll();
	}

}
