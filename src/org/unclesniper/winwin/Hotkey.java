package org.unclesniper.winwin;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public final class Hotkey {

	static {
		WinAPI.init();
	}

	private static final class KeyKey {

		final long windowOrThread;

		final int id;

		public KeyKey(long windowOrThread, int id) {
			this.windowOrThread = windowOrThread;
			this.id = id;
		}

		@Override
		public boolean equals(Object other) {
			if(!(other instanceof KeyKey))
				return false;
			KeyKey key = (KeyKey)other;
			return windowOrThread == key.windowOrThread && id == key.id;
		}

		@Override
		public int hashCode() {
			int hi = (int)(windowOrThread >>> 32), lo = (int)(windowOrThread & 0xFFFFFFFFl);
			int code = (hi << 13) | (hi >>> 19);
			code ^= lo;
			code = (code << 13) | (code >>> 19);
			return code ^ id;
		}

	}

	private static final Map<KeyKey, HotkeyHandler> WINDOW_HANDLERS = new ConcurrentHashMap<KeyKey, HotkeyHandler>();
	private static final Map<KeyKey, HotkeyHandler> THREAD_HANDLERS = new ConcurrentHashMap<KeyKey, HotkeyHandler>();

	private final HWnd window;

	private final int id;

	private final HotkeyHandler handler;

	private Hotkey(HWnd window, int id, HotkeyHandler handler) {
		this.window = window;
		this.id = id;
		this.handler = handler;
	}

	public HWnd getWindow() {
		return window;
	}

	public int getID() {
		return id;
	}

	public HotkeyHandler getHandler() {
		return handler;
	}

	public void unregisterHotKey() {
		if(!Hotkey.unregisterHotKeyImpl(window == null ? 0l : window.getHandle(), id))
			throw new WindowsException("Failed to unregister hotkey");
		if(handler != null) {
			long win = window == null ? 0l : window.getHandle();
			if(win == 0l)
				Hotkey.THREAD_HANDLERS.remove(new KeyKey(Thread.currentThread().getId(), id));
			else
				Hotkey.WINDOW_HANDLERS.remove(new KeyKey(win, id));
		}
	}

	private static native boolean unregisterHotKeyImpl(long hwnd, int id);

	public static Hotkey registerHotKey(HWnd hwnd, int id, HotkeySpec key, HotkeyHandler handler) {
		if(key == null)
			throw new IllegalArgumentException("Key cannot be null");
		return Hotkey.registerHotKey(hwnd, id, key.getModifiers(), key.getKey(), handler);
	}

	public static Hotkey registerHotKey(HWnd hwnd, int id, int modifiers, VirtualKey key, HotkeyHandler handler) {
		long win = hwnd == null ? 0l : hwnd.getHandle();
		if(win == 0l && handler == null)
			throw new IllegalArgumentException("Cannot have both hwnd == null and handler == null");
		if(key == null)
			throw new IllegalArgumentException("Virtual key cannot be null");
		if(id < 0x0000 || id > 0xBFFF)
			throw new IllegalArgumentException("Hotkey ID out of range: " + id);
		if(!Hotkey.registerHotKeyImpl(win, id, modifiers, key.getCode()))
			throw new WindowsException("Failed to register hotkey");
		if(handler != null) {
			if(win == 0l)
				Hotkey.THREAD_HANDLERS.put(new KeyKey(Thread.currentThread().getId(), id), handler);
			else
				Hotkey.WINDOW_HANDLERS.put(new KeyKey(win, id), handler);
		}
		return new Hotkey(hwnd, id, handler);
	}

	private static native boolean registerHotKeyImpl(long hwnd, int id, int modifiers, short key);

	private static void dispatchHandler(long hwnd, int id, int modifiers) {
		HotkeyHandler handler;
		if(hwnd == 0l)
			handler = Hotkey.THREAD_HANDLERS.get(new KeyKey(Thread.currentThread().getId(), id));
		else
			handler = Hotkey.WINDOW_HANDLERS.get(new KeyKey(hwnd, id));
		if(handler != null)
			handler.hotkeyPressed(id, modifiers);
	}

}
