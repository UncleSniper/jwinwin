package org.unclesniper.winwin;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public final class HWnd {

	static {
		WinAPI.init();
	}

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

	public native int closeWindow();

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

	public static void main(String[] args) {
		System.out.println("Hello, world!");
	}

}
