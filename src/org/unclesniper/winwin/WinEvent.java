package org.unclesniper.winwin;

import java.util.Map;
import java.util.HashMap;

public final class WinEvent {

	public static final long CHILDID_SELF = Long.MAX_VALUE;

	private static final Map<Integer, String> EVENTS_BY_CODE;

	static {
		EVENTS_BY_CODE = new HashMap<Integer, String>();
		EVENTS_BY_CODE.put(0x0000A000, "EVENT_AIA_START");
		EVENTS_BY_CODE.put(0x0000AFFF, "EVENT_AIA_END");
		EVENTS_BY_CODE.put(0x00008012, "EVENT_OBJECT_ACCELERATORCHANGE");
		EVENTS_BY_CODE.put(0x00008017, "EVENT_OBJECT_CLOAKED");
		EVENTS_BY_CODE.put(0x00008015, "EVENT_OBJECT_CONTENTSCROLLED");
		EVENTS_BY_CODE.put(0x00008000, "EVENT_OBJECT_CREATE");
		EVENTS_BY_CODE.put(0x00008011, "EVENT_OBJECT_DEFACTIONCHANGE");
		EVENTS_BY_CODE.put(0x0000800D, "EVENT_OBJECT_DESCRIPTIONCHANGE");
		EVENTS_BY_CODE.put(0x00008001, "EVENT_OBJECT_DESTROY");
		EVENTS_BY_CODE.put(0x00008021, "EVENT_OBJECT_DRAGSTART");
		EVENTS_BY_CODE.put(0x00008022, "EVENT_OBJECT_DRAGCANCEL");
		EVENTS_BY_CODE.put(0x00008023, "EVENT_OBJECT_DRAGCOMPLETE");
		EVENTS_BY_CODE.put(0x00008024, "EVENT_OBJECT_DRAGENTER");
		EVENTS_BY_CODE.put(0x00008025, "EVENT_OBJECT_DRAGLEAVE");
		EVENTS_BY_CODE.put(0x00008026, "EVENT_OBJECT_DRAGDROPPED");
		EVENTS_BY_CODE.put(0x000080FF, "EVENT_OBJECT_END");
		EVENTS_BY_CODE.put(0x00008005, "EVENT_OBJECT_FOCUS");
		EVENTS_BY_CODE.put(0x00008010, "EVENT_OBJECT_HELPCHANGE");
		EVENTS_BY_CODE.put(0x00008003, "EVENT_OBJECT_HIDE");
		EVENTS_BY_CODE.put(0x00008020, "EVENT_OBJECT_HOSTEDOBJECTSINVALIDATED");
		EVENTS_BY_CODE.put(0x00008028, "EVENT_OBJECT_IME_HIDE");
		EVENTS_BY_CODE.put(0x00008027, "EVENT_OBJECT_IME_SHOW");
		EVENTS_BY_CODE.put(0x00008029, "EVENT_OBJECT_IME_CHANGE");
		EVENTS_BY_CODE.put(0x00008013, "EVENT_OBJECT_INVOKED");
		EVENTS_BY_CODE.put(0x00008019, "EVENT_OBJECT_LIVEREGIONCHANGED");
		EVENTS_BY_CODE.put(0x0000800B, "EVENT_OBJECT_LOCATIONCHANGE");
		EVENTS_BY_CODE.put(0x0000800C, "EVENT_OBJECT_NAMECHANGE");
		EVENTS_BY_CODE.put(0x0000800F, "EVENT_OBJECT_PARENTCHANGE");
		EVENTS_BY_CODE.put(0x00008004, "EVENT_OBJECT_REORDER");
		EVENTS_BY_CODE.put(0x00008006, "EVENT_OBJECT_SELECTION");
		EVENTS_BY_CODE.put(0x00008007, "EVENT_OBJECT_SELECTIONADD");
		EVENTS_BY_CODE.put(0x00008008, "EVENT_OBJECT_SELECTIONREMOVE");
		EVENTS_BY_CODE.put(0x00008009, "EVENT_OBJECT_SELECTIONWITHIN");
		EVENTS_BY_CODE.put(0x00008002, "EVENT_OBJECT_SHOW");
		EVENTS_BY_CODE.put(0x0000800A, "EVENT_OBJECT_STATECHANGE");
		EVENTS_BY_CODE.put(0x00008030, "EVENT_OBJECT_TEXTEDIT_CONVERSIONTARGETCHANGED");
		EVENTS_BY_CODE.put(0x00008014, "EVENT_OBJECT_TEXTSELECTIONCHANGED");
		EVENTS_BY_CODE.put(0x00008018, "EVENT_OBJECT_UNCLOAKED");
		EVENTS_BY_CODE.put(0x0000800E, "EVENT_OBJECT_VALUECHANGE");
		EVENTS_BY_CODE.put(0x00000101, "EVENT_OEM_DEFINED_START");
		EVENTS_BY_CODE.put(0x000001FF, "EVENT_OEM_DEFINED_END");
		EVENTS_BY_CODE.put(0x00000002, "EVENT_SYSTEM_ALERT");
		EVENTS_BY_CODE.put(0x00008016, "EVENT_SYSTEM_ARRANGMENTPREVIEW");
		EVENTS_BY_CODE.put(0x00000009, "EVENT_SYSTEM_CAPTUREEND");
		EVENTS_BY_CODE.put(0x00000008, "EVENT_SYSTEM_CAPTURESTART");
		EVENTS_BY_CODE.put(0x0000000D, "EVENT_SYSTEM_CONTEXTHELPEND");
		EVENTS_BY_CODE.put(0x0000000C, "EVENT_SYSTEM_CONTEXTHELPSTART");
		EVENTS_BY_CODE.put(0x00000020, "EVENT_SYSTEM_DESKTOPSWITCH");
		EVENTS_BY_CODE.put(0x00000011, "EVENT_SYSTEM_DIALOGEND");
		EVENTS_BY_CODE.put(0x00000010, "EVENT_SYSTEM_DIALOGSTART");
		EVENTS_BY_CODE.put(0x0000000F, "EVENT_SYSTEM_DRAGDROPEND");
		EVENTS_BY_CODE.put(0x0000000E, "EVENT_SYSTEM_DRAGDROPSTART");
		EVENTS_BY_CODE.put(0x000000FF, "EVENT_SYSTEM_END");
		EVENTS_BY_CODE.put(0x00000003, "EVENT_SYSTEM_FOREGROUND");
		EVENTS_BY_CODE.put(0x00000007, "EVENT_SYSTEM_MENUPOPUPEND");
		EVENTS_BY_CODE.put(0x00000006, "EVENT_SYSTEM_MENUPOPUPSTART");
		EVENTS_BY_CODE.put(0x00000005, "EVENT_SYSTEM_MENUEND");
		EVENTS_BY_CODE.put(0x00000004, "EVENT_SYSTEM_MENUSTART");
		EVENTS_BY_CODE.put(0x00000017, "EVENT_SYSTEM_MINIMIZEEND");
		EVENTS_BY_CODE.put(0x00000016, "EVENT_SYSTEM_MINIMIZESTART");
		EVENTS_BY_CODE.put(0x0000000B, "EVENT_SYSTEM_MOVESIZEEND");
		EVENTS_BY_CODE.put(0x0000000A, "EVENT_SYSTEM_MOVESIZESTART");
		EVENTS_BY_CODE.put(0x00000013, "EVENT_SYSTEM_SCROLLINGEND");
		EVENTS_BY_CODE.put(0x00000012, "EVENT_SYSTEM_SCROLLINGSTART");
		EVENTS_BY_CODE.put(0x00000001, "EVENT_SYSTEM_SOUND");
		EVENTS_BY_CODE.put(0x00000015, "EVENT_SYSTEM_SWITCHEND");
		EVENTS_BY_CODE.put(0x00000014, "EVENT_SYSTEM_SWITCHSTART");
		EVENTS_BY_CODE.put(0x00004E00, "EVENT_UIA_EVENTID_START");
		EVENTS_BY_CODE.put(0x00004EFF, "EVENT_UIA_EVENTID_END");
		EVENTS_BY_CODE.put(0x00007500, "EVENT_UIA_PROPID_START");
		EVENTS_BY_CODE.put(0x000075FF, "EVENT_UIA_PROPID_END");
	}

	public int event;

	public HWnd hwnd;

	public HWinEventHook.ObjID idObject;

	public long idObjectCustom;

	public long idChild;

	public WinEvent(int event, HWnd hwnd, HWinEventHook.ObjID idObject, long idObjectCustom, long idChild) {
		this.event = event;
		this.hwnd = hwnd;
		this.idObject = idObject;
		this.idObjectCustom = idObjectCustom;
		this.idChild = idChild;
	}

	public boolean dispatch(WinEventProc proc) {
		switch(event) {
			case HWinEventHook.EVENT_OBJECT_CLOAKED:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowCloaked(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_OBJECT_CREATE:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowCreate(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_OBJECT_DESTROY:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowDestroy(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_OBJECT_FOCUS:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowFocus(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_OBJECT_NAMECHANGE:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowNameChange(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_OBJECT_REORDER:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowReorder(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_OBJECT_SHOW:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowShow(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_OBJECT_UNCLOAKED:
				if(idObject != HWinEventHook.ObjID.OBJID_WINDOW)
					return false;
				proc.windowUncloaked(hwnd, idChild);
				return true;
			case HWinEventHook.EVENT_SYSTEM_DESKTOPSWITCH:
				proc.desktopSwitch(idChild);
				return true;
			case HWinEventHook.EVENT_SYSTEM_FOREGROUND:
				proc.foreground(hwnd);
				return true;
			case HWinEventHook.EVENT_SYSTEM_MINIMIZEEND:
				proc.windowMinimizeEnd(hwnd);
				return true;
			case HWinEventHook.EVENT_SYSTEM_MINIMIZESTART:
				proc.windowMinimizeStart(hwnd);
				return true;
			case HWinEventHook.EVENT_SYSTEM_MOVESIZEEND:
				proc.windowMoveSizeEnd(hwnd);
				return true;
			case HWinEventHook.EVENT_SYSTEM_MOVESIZESTART:
				proc.windowMoveSizeStart(hwnd);
				return true;
			default:
				return false;
		}
	}

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder("WinEvent { event = ");
		String e = WinEvent.EVENTS_BY_CODE.get(event);
		if(e == null) {
			builder.append("0x");
			long le = (long)event;
			if(le < 0l)
				le += 0xFFFFFFFFl;
			builder.append(Long.toHexString(le | 0x100000000l).substring(1));
		}
		else
			builder.append(e);
		builder.append(", hwnd = ");
		builder.append(hwnd == null ? "NULL" : "0x" + Long.toHexString(hwnd.getHandle()));
		builder.append(", idObject = ");
		builder.append(idObject == null ? "<null>" : idObject.name());
		builder.append(", idObjectCustom = ");
		builder.append(String.valueOf(idObjectCustom));
		builder.append(", idChild = ");
		builder.append(String.valueOf(idChild));
		builder.append(" }");
		return builder.toString();
	}

}
