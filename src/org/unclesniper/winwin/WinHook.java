package org.unclesniper.winwin;

public final class WinHook {

	public static final class LowLevelHotkey {

		private final HWnd window;

		private final int id;

		private final int modifiers;

		private final VirtualKey key;

		private final HotkeyHandler handler;

		LowLevelHotkey(HWnd window, int id, int modifiers, VirtualKey key, HotkeyHandler handler) {
			this.window = window;
			this.id = id;
			this.modifiers = modifiers;
			this.key = key;
			this.handler = handler;
		}

		public HWnd getWindow() {
			return window;
		}

		public int getID() {
			return id;
		}

		public int getModifiers() {
			return modifiers;
		}

		public VirtualKey getKey() {
			return key;
		}

		public HotkeyHandler getHandler() {
			return handler;
		}

		public void unregisterLowLevelHotKey() {
			synchronized(Hotkey.WINDOW_HANDLERS) {
				if(!WinHook.unregisterLowLevelHotKeyImpl(modifiers, key.getCode()))
					throw new WindowsException("Failed to unregister hotkey", WinAPI.ERROR_HOTKEY_NOT_REGISTERED);
				if(handler != null) {
					long win = window == null ? 0l : window.getHandle();
					if(win == 0l)
						Hotkey.THREAD_HANDLERS.remove(new Hotkey.KeyKey(Thread.currentThread().getId(), id));
					else
						Hotkey.WINDOW_HANDLERS.remove(new Hotkey.KeyKey(win, id));
				}
			}
		}

	}

	private static final class HookThread extends Thread {

		public HookThread() {
			start();
		}

		@Override
		public void run() {
			if(!WinHook.doYaThang(WinHook.hookTypes))
				throw new WindowsException("Failed to use hooks");
		}

	}

	static {
		WinAPI.init();
	}

	public static final int WH_KEYBOARD_LL    = 01;
	public static final int WH_CALLWNDPROCRET = 02;
	public static final int WH_ALL            = 03;

	private static final Object THREAD_LOCK = new Object();

	private static volatile HookThread hookThread;

	private static volatile int hookTypes;

	private static volatile int startCount;

	private static CallWndRetProc callWndRetProc;

	private WinHook() {}

	public static void startHooks(int types) {
		types &= WinHook.WH_ALL;
		if(types == 0)
			throw new IllegalArgumentException("Must start hook thread with at least one hook type");
		if(WinHook.hookThread == null) {
			synchronized(WinHook.THREAD_LOCK) {
				if(WinHook.hookThread == null) {
					WinHook.hookTypes = types;
					WinHook.hookThread = new HookThread();
					WinHook.startCount = 1;
					return;
				}
			}
		}
		if((types & WinHook.hookTypes) != types)
			throw new IllegalStateException("Incompatible hook type mask: Requested " + types
					+ ", but was already started with " + WinHook.hookTypes);
		synchronized(WinHook.THREAD_LOCK) {
			++WinHook.startCount;
		}
	}

	public static void stopHooks() {
		synchronized(WinHook.THREAD_LOCK) {
			if(WinHook.startCount == 0)
				throw new IllegalStateException("Called stopHooks() with no corresponding startHooks()");
			if(--WinHook.startCount == 0) {
				if(!WinHook.sendStopMessage())
					throw new WindowsException("Failed to stop hook thread");
				for(;;) {
					try {
						WinHook.hookThread.join();
						break;
					}
					catch(InterruptedException ie) {}
				}
				WinHook.hookThread = null;
			}
		}
	}

	private static native boolean doYaThang(int types);

	private static native boolean sendStopMessage();

	public static LowLevelHotkey registerLowLevelHotKey(HWnd hwnd, int id, HotkeySpec key, HotkeyHandler handler) {
		if(key == null)
			throw new IllegalArgumentException("Key cannot be null");
		return WinHook.registerLowLevelHotKey(hwnd, id, key.getModifiers(), key.getKey(), handler);
	}

	public static LowLevelHotkey registerLowLevelHotKey(HWnd hwnd, int id, int modifiers, VirtualKey key,
			HotkeyHandler handler) {
		long win = hwnd == null ? 0l : hwnd.getHandle();
		if(win == 0l && handler == null)
			throw new IllegalArgumentException("Cannot have both hwnd == null and handler == null");
		if(key == null)
			throw new IllegalArgumentException("Virtual key cannot be null");
		Hotkey.KeyKey keykey;
		synchronized(Hotkey.WINDOW_HANDLERS) {
			if(handler == null)
				keykey = null;
			else if(win == 0l) {
				keykey = new Hotkey.KeyKey(Thread.currentThread().getId(), id);
				if(Hotkey.THREAD_HANDLERS.containsKey(keykey))
					throw new IllegalStateException("Hotkey handler already registered");
			}
			else {
				keykey = new Hotkey.KeyKey(win, id);
				if(Hotkey.WINDOW_HANDLERS.containsKey(keykey))
					throw new IllegalStateException("Hotkey handler already registered");
			}
			if(!WinHook.registerLowLevelHotKeyImpl(win, id, modifiers, key.getCode()))
				throw new WindowsException("Failed to register hotkey", WinAPI.ERROR_HOTKEY_ALREADY_REGISTERED);
			if(handler != null) {
				if(win == 0l)
					Hotkey.THREAD_HANDLERS.put(keykey, handler);
				else
					Hotkey.WINDOW_HANDLERS.put(keykey, handler);
			}
		}
		return new LowLevelHotkey(hwnd, id, modifiers, key, handler);
	}

	private static native boolean registerLowLevelHotKeyImpl(long hwnd, int id, int modifiers, short key);

	private static native boolean unregisterLowLevelHotKeyImpl(int modifiers, short key);

	public static CallWndRetProc getCallWndRetProc() {
		return WinHook.callWndRetProc;
	}

	public static void setCallWndRetProc(CallWndRetProc callWndRetProc) {
		WinHook.callWndRetProc = callWndRetProc;
	}

	private static void dispatchCallWndRetProcShowWindow(long hwnd, int details) {
		CallWndRetProc proc = WinHook.callWndRetProc;
		if(proc != null)
			proc.wmShowWindow(hwnd == 0l ? null : new HWnd(hwnd), (details & 010) != 0,
					WmShowWindow.ShowWindow.byOrdinal(details & 07));
	}

}
