package org.unclesniper.winwin;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public final class HWinEventHook {

	static {
		WinAPI.init();
	}

	public enum ObjID {

		OBJID_ALERT,
		OBJID_CARET,
		OBJID_CLIENT,
		OBJID_CURSOR,
		OBJID_HSCROLL,
		OBJID_NATIVEOM,
		OBJID_MENU,
		OBJID_QUERYCLASSNAMEIDX,
		OBJID_SIZEGRIP,
		OBJID_SOUND,
		OBJID_SYSMENU,
		OBJID_TITLEBAR,
		OBJID_VSCROLL,
		OBJID_WINDOW;

		private static final ObjID[] VALUES = ObjID.values();

		public static ObjID byOrdinal(int ordinal) {
			return ObjID.VALUES[ordinal];
		}

	}

	public static final int WINEVENT_SKIPOWNPROCESS = 0001;
	public static final int WINEVENT_SKIPOWNTHREAD  = 0002;

	public static final int EVENT_AIA_START                               = 0x0000A000;
	public static final int EVENT_AIA_END                                 = 0x0000AFFF;
	public static final int EVENT_MIN                                     = 0x00000001;
	public static final int EVENT_MAX                                     = 0x7FFFFFFF;
	public static final int EVENT_OBJECT_ACCELERATORCHANGE                = 0x00008012;
	public static final int EVENT_OBJECT_CLOAKED                          = 0x00008017;
	public static final int EVENT_OBJECT_CONTENTSCROLLED                  = 0x00008015;
	public static final int EVENT_OBJECT_CREATE                           = 0x00008000;
	public static final int EVENT_OBJECT_DEFACTIONCHANGE                  = 0x00008011;
	public static final int EVENT_OBJECT_DESCRIPTIONCHANGE                = 0x0000800D;
	public static final int EVENT_OBJECT_DESTROY                          = 0x00008001;
	public static final int EVENT_OBJECT_DRAGSTART                        = 0x00008021;
	public static final int EVENT_OBJECT_DRAGCANCEL                       = 0x00008022;
	public static final int EVENT_OBJECT_DRAGCOMPLETE                     = 0x00008023;
	public static final int EVENT_OBJECT_DRAGENTER                        = 0x00008024;
	public static final int EVENT_OBJECT_DRAGLEAVE                        = 0x00008025;
	public static final int EVENT_OBJECT_DRAGDROPPED                      = 0x00008026;
	public static final int EVENT_OBJECT_END                              = 0x000080FF;
	public static final int EVENT_OBJECT_FOCUS                            = 0x00008005;
	public static final int EVENT_OBJECT_HELPCHANGE                       = 0x00008010;
	public static final int EVENT_OBJECT_HIDE                             = 0x00008003;
	public static final int EVENT_OBJECT_HOSTEDOBJECTSINVALIDATED         = 0x00008020;
	public static final int EVENT_OBJECT_IME_HIDE                         = 0x00008028;
	public static final int EVENT_OBJECT_IME_SHOW                         = 0x00008027;
	public static final int EVENT_OBJECT_IME_CHANGE                       = 0x00008029;
	public static final int EVENT_OBJECT_INVOKED                          = 0x00008013;
	public static final int EVENT_OBJECT_LIVEREGIONCHANGED                = 0x00008019;
	public static final int EVENT_OBJECT_LOCATIONCHANGE                   = 0x0000800B;
	public static final int EVENT_OBJECT_NAMECHANGE                       = 0x0000800C;
	public static final int EVENT_OBJECT_PARENTCHANGE                     = 0x0000800F;
	public static final int EVENT_OBJECT_REORDER                          = 0x00008004;
	public static final int EVENT_OBJECT_SELECTION                        = 0x00008006;
	public static final int EVENT_OBJECT_SELECTIONADD                     = 0x00008007;
	public static final int EVENT_OBJECT_SELECTIONREMOVE                  = 0x00008008;
	public static final int EVENT_OBJECT_SELECTIONWITHIN                  = 0x00008009;
	public static final int EVENT_OBJECT_SHOW                             = 0x00008002;
	public static final int EVENT_OBJECT_STATECHANGE                      = 0x0000800A;
	public static final int EVENT_OBJECT_TEXTEDIT_CONVERSIONTARGETCHANGED = 0x00008030;
	public static final int EVENT_OBJECT_TEXTSELECTIONCHANGED             = 0x00008014;
	public static final int EVENT_OBJECT_UNCLOAKED                        = 0x00008018;
	public static final int EVENT_OBJECT_VALUECHANGE                      = 0x0000800E;
	public static final int EVENT_OEM_DEFINED_START                       = 0x00000101;
	public static final int EVENT_OEM_DEFINED_END                         = 0x000001FF;
	public static final int EVENT_SYSTEM_ALERT                            = 0x00000002;
	public static final int EVENT_SYSTEM_ARRANGMENTPREVIEW                = 0x00008016;
	public static final int EVENT_SYSTEM_CAPTUREEND                       = 0x00000009;
	public static final int EVENT_SYSTEM_CAPTURESTART                     = 0x00000008;
	public static final int EVENT_SYSTEM_CONTEXTHELPEND                   = 0x0000000D;
	public static final int EVENT_SYSTEM_CONTEXTHELPSTART                 = 0x0000000C;
	public static final int EVENT_SYSTEM_DESKTOPSWITCH                    = 0x00000020;
	public static final int EVENT_SYSTEM_DIALOGEND                        = 0x00000011;
	public static final int EVENT_SYSTEM_DIALOGSTART                      = 0x00000010;
	public static final int EVENT_SYSTEM_DRAGDROPEND                      = 0x0000000F;
	public static final int EVENT_SYSTEM_DRAGDROPSTART                    = 0x0000000E;
	public static final int EVENT_SYSTEM_END                              = 0x000000FF;
	public static final int EVENT_SYSTEM_FOREGROUND                       = 0x00000003;
	public static final int EVENT_SYSTEM_MENUPOPUPEND                     = 0x00000007;
	public static final int EVENT_SYSTEM_MENUPOPUPSTART                   = 0x00000006;
	public static final int EVENT_SYSTEM_MENUEND                          = 0x00000005;
	public static final int EVENT_SYSTEM_MENUSTART                        = 0x00000004;
	public static final int EVENT_SYSTEM_MINIMIZEEND                      = 0x00000017;
	public static final int EVENT_SYSTEM_MINIMIZESTART                    = 0x00000016;
	public static final int EVENT_SYSTEM_MOVESIZEEND                      = 0x0000000B;
	public static final int EVENT_SYSTEM_MOVESIZESTART                    = 0x0000000A;
	public static final int EVENT_SYSTEM_SCROLLINGEND                     = 0x00000013;
	public static final int EVENT_SYSTEM_SCROLLINGSTART                   = 0x00000012;
	public static final int EVENT_SYSTEM_SOUND                            = 0x00000001;
	public static final int EVENT_SYSTEM_SWITCHEND                        = 0x00000015;
	public static final int EVENT_SYSTEM_SWITCHSTART                      = 0x00000014;
	public static final int EVENT_UIA_EVENTID_START                       = 0x00004E00;
	public static final int EVENT_UIA_EVENTID_END                         = 0x00004EFF;
	public static final int EVENT_UIA_PROPID_START                        = 0x00007500;
	public static final int EVENT_UIA_PROPID_END                          = 0x000075FF;

	private static final Map<Long, WinEventProc> KNOWN_WINEVTPROCS = new ConcurrentHashMap<Long, WinEventProc>();

	private final long handle;

	HWinEventHook(long handle) {
		this.handle = handle;
	}

	long getHandle() {
		return handle;
	}

	@Override
	public boolean equals(Object other) {
		if(!(other instanceof HWinEventHook))
			return false;
		return handle == ((HWinEventHook)other).handle;
	}

	@Override
	public int hashCode() {
		int hi = (int)(handle >> 32), lo = (int)handle;
		return ((hi << 13) | (hi >> 19)) ^ lo;
	}

	public void unhookWinEvent() {
		if(!HWinEventHook.unhookWinEventImpl(handle))
			throw new WindowsException("Failed to unhook WinEvent");
		HWinEventHook.KNOWN_WINEVTPROCS.remove(handle);
	}

	private static native boolean unhookWinEventImpl(long handle);

	private static WinEventProc getWinEventProcByHandle(long handle) {
		return HWinEventHook.KNOWN_WINEVTPROCS.get(handle);
	}

	public static HWinEventHook setWinEventHook(int eventMin, int eventMax, int flags, WinEventProc callback) {
		if(eventMin < HWinEventHook.EVENT_MIN || eventMin > HWinEventHook.EVENT_MAX)
			throw new IllegalArgumentException("Minimal event out of bounds: " + eventMin);
		if(eventMax < HWinEventHook.EVENT_MIN || eventMax > HWinEventHook.EVENT_MAX)
			throw new IllegalArgumentException("Maximal event out of bounds: " + eventMin);
		if(eventMax <= eventMin)
			throw new IllegalArgumentException("Event range is empty: " + eventMin + " >= " + eventMax);
		if(callback == null)
			throw new IllegalArgumentException("WinEventProc must not be null");
		long hook = HWinEventHook.setWinEventHookImpl(eventMin, eventMax, flags);
		if(hook == 0l)
			throw new WindowsException("Failed to set WinEvent hook");
		HWinEventHook.KNOWN_WINEVTPROCS.put(hook, callback);
		return new HWinEventHook(hook);
	}

	private static native long setWinEventHookImpl(int eventMin, int eventMax, int flags);

}
