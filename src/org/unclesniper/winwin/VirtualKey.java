package org.unclesniper.winwin;

import java.util.Map;
import java.util.HashMap;

public enum VirtualKey {

	VK_LBUTTON(0x01),
	VK_RBUTTON(0x02),
	VK_CANCEL(0x03),
	VK_MBUTTON(0x04),
	VK_XBUTTON1(0x05),
	VK_XBUTTON2(0x06),
	VK_BACK(0x08, '\b'),
	VK_TAB(0x09, '\t'),
	VK_CLEAR(0x0C),
	VK_RETURN(0x0D, '\n'),
	VK_SHIFT(0x10),
	VK_CONTROL(0x11),
	VK_MENU(0x12),
	VK_PAUSE(0x13),
	VK_CAPITAL(0x14),
	VK_KANA(0x15),
	VK_HANGUEL(0x15),
	VK_HANGUL(0x15),
	VK_IME_ON(0x16),
	VK_JUNJA(0x17),
	VK_FINAL(0x18),
	VK_HANJA(0x19),
	VK_KANJI(0x19),
	VK_IME_OFF(0x1A),
	VK_ESCAPE(0x1B, '\u001B'),
	VK_CONVERT(0x1C),
	VK_NONCONVERT(0x1D),
	VK_ACCEPT(0x1E),
	VK_MODECHANGE(0x1F),
	VK_SPACE(0x20, ' '),
	VK_PRIOR(0x21),
	VK_NEXT(0x22),
	VK_END(0x23),
	VK_HOME(0x24),
	VK_LEFT(0x25),
	VK_UP(0x26),
	VK_RIGHT(0x27),
	VK_DOWN(0x28),
	VK_SELECT(0x29),
	VK_PRINT(0x2A),
	VK_EXECUTE(0x2B),
	VK_SNAPSHOT(0x2C),
	VK_INSERT(0x2D),
	VK_DELETE(0x2E),
	VK_HELP(0x2F),
	VK_0(0x30, '0'),
	VK_1(0x31, '1'),
	VK_2(0x32, '2'),
	VK_3(0x33, '3'),
	VK_4(0x34, '4'),
	VK_5(0x35, '5'),
	VK_6(0x36, '6'),
	VK_7(0x37, '7'),
	VK_8(0x38, '8'),
	VK_9(0x39, '9'),
	VK_A(0x41, 'A'),
	VK_B(0x42, 'B'),
	VK_C(0x43, 'C'),
	VK_D(0x44, 'D'),
	VK_E(0x45, 'E'),
	VK_F(0x46, 'F'),
	VK_G(0x47, 'G'),
	VK_H(0x48, 'H'),
	VK_I(0x49, 'I'),
	VK_J(0x4A, 'J'),
	VK_K(0x4B, 'K'),
	VK_L(0x4C, 'L'),
	VK_M(0x4D, 'M'),
	VK_N(0x4E, 'N'),
	VK_O(0x4F, 'O'),
	VK_P(0x50, 'P'),
	VK_Q(0x51, 'Q'),
	VK_R(0x52, 'R'),
	VK_S(0x53, 'S'),
	VK_T(0x54, 'T'),
	VK_U(0x55, 'U'),
	VK_V(0x56, 'V'),
	VK_W(0x57, 'W'),
	VK_X(0x58, 'X'),
	VK_Y(0x59, 'Y'),
	VK_Z(0x5A, 'Z'),
	VK_LWIN(0x5B),
	VK_RWIN(0x5C),
	VK_APPS(0x5D),
	VK_SLEEP(0x5F),
	VK_NUMPAD0(0x60),
	VK_NUMPAD1(0x61),
	VK_NUMPAD2(0x62),
	VK_NUMPAD3(0x63),
	VK_NUMPAD4(0x64),
	VK_NUMPAD5(0x65),
	VK_NUMPAD6(0x66),
	VK_NUMPAD7(0x67),
	VK_NUMPAD8(0x68),
	VK_NUMPAD9(0x69),
	VK_MULTIPLY(0x6A),
	VK_ADD(0x6B),
	VK_SEPARATOR(0x6C),
	VK_SUBTRACT(0x6D),
	VK_DECIMAL(0x6E),
	VK_DIVIDE(0x6F),
	VK_F1(0x70),
	VK_F2(0x71),
	VK_F3(0x72),
	VK_F4(0x73),
	VK_F5(0x74),
	VK_F6(0x75),
	VK_F7(0x76),
	VK_F8(0x77),
	VK_F9(0x78),
	VK_F10(0x79),
	VK_F11(0x7A),
	VK_F12(0x7B),
	VK_F13(0x7C),
	VK_F14(0x7D),
	VK_F15(0x7E),
	VK_F16(0x7F),
	VK_F17(0x80),
	VK_F18(0x81),
	VK_F19(0x82),
	VK_F20(0x83),
	VK_F21(0x84),
	VK_F22(0x85),
	VK_F23(0x86),
	VK_F24(0x87),
	VK_NUMLOCK(0x90),
	VK_SCROLL(0x91),
	VK_LSHIFT(0xA0),
	VK_RSHIFT(0xA1),
	VK_LCONTROL(0xA2),
	VK_RCONTROL(0xA3),
	VK_LMENU(0xA4),
	VK_RMENU(0xA5),
	VK_BROWSER_BACK(0xA6),
	VK_BROWSER_FORWARD(0xA7),
	VK_BROWSER_REFRESH(0xA8),
	VK_BROWSER_STOP(0xA9),
	VK_BROWSER_SEARCH(0xAA),
	VK_BROWSER_FAVORITES(0xAB),
	VK_BROWSER_HOME(0xAC),
	VK_VOLUME_MUTE(0xAD),
	VK_VOLUME_DOWN(0xAE),
	VK_VOLUME_UP(0xAF),
	VK_MEDIA_NEXT_TRACK(0xB0),
	VK_MEDIA_PREV_TRACK(0xB1),
	VK_MEDIA_STOP(0xB2),
	VK_MEDIA_PLAY_PAUSE(0xB3),
	VK_LAUNCH_MAIL(0xB4),
	VK_LAUNCH_MEDIA_SELECT(0xB5),
	VK_LAUNCH_APP1(0xB6),
	VK_LAUNCH_APP2(0xB7),
	VK_OEM_1(0xBA),
	VK_OEM_PLUS(0xBB, '+'),
	VK_OEM_COMMA(0xBC, ','),
	VK_OEM_MINUS(0xBD, '-'),
	VK_OEM_PERIOD(0xBE, '.'),
	VK_OEM_2(0xBF),
	VK_OEM_3(0xC0),
	VK_OEM_4(0xDB),
	VK_OEM_5(0xDC),
	VK_OEM_6(0xDD),
	VK_OEM_7(0xDE),
	VK_OEM_8(0xDF),
	VK_OEM_102(0xE2),
	VK_PROCESSKEY(0xE5),
	VK_PACKET(0xE7),
	VK_ATTN(0xF6),
	VK_CRSEL(0xF7),
	VK_EXSEL(0xF8),
	VK_EREOF(0xF9),
	VK_PLAY(0xFA),
	VK_ZOOM(0xFB),
	VK_NONAME(0xFC),
	VK_PA1(0xFD),
	VK_OEM_CLEAR(0xFE),
	// Names like 'VK_OEM_1' are not really helpful,
	// so let's give them proper names...
	VK_US_SEMICOLON(0xBA),
	VK_US_SLASH(0xBF),
	VK_US_BACKQUOTE(0xC0),
	VK_US_LBRACE(0xDB),
	VK_US_BACKSLASH(0xDC),
	VK_US_RBRACE(0xDD),
	VK_US_QUOTE(0xDE);

	public static final int MOD_ALT = 0x0001;
	public static final int MOD_CONTROL = 0x0002;
	public static final int MOD_NOREPEAT = 0x4000;
	public static final int MOD_SHIFT = 0x0004;
	public static final int MOD_WIN = 0x0008;

	public static final int MODMASK_IN  = 0x400F;
	public static final int MODMASK_OUT = 0x000F;

	private static final Map<Character, VirtualKey> BY_CHAR;
	private static final Map<Short, VirtualKey> BY_CODE;

	static {
		BY_CHAR = new HashMap<Character, VirtualKey>();
		BY_CODE = new HashMap<Short, VirtualKey>();
		for(VirtualKey key : VirtualKey.values()) {
			if(key.character != '\u0000') {
				BY_CHAR.put(key.character, key);
				if(key.character >= 'A' && key.character <= 'Z') {
					char lo = (char)(key.character + ('a' - 'A'));
					BY_CHAR.put(lo, key);
				}
			}
			BY_CODE.put(key.code, key);
		}
		BY_CHAR.put('\r', VK_RETURN);
	}

	private static final VirtualKey[] VALUES = VirtualKey.values();

	private static final int F_KEY_BASE = VirtualKey.VK_F1.ordinal() - 1;

	private final short code;

	private final char character;

	private VirtualKey(int code, char character) {
		this.code = (short)code;
		this.character = character;
	}

	private VirtualKey(int code) {
		this(code, '\u0000');
	}

	public short getCode() {
		return code;
	}

	public char getCharacter() {
		return character;
	}

	public static VirtualKey byChar(char c) {
		return VirtualKey.BY_CHAR.get(c);
	}

	public static VirtualKey F(int index) {
		if(index < 1 || index > 24)
			return null;
		return VirtualKey.VALUES[VirtualKey.F_KEY_BASE + index];
	}

	public static VirtualKey byCode(short code) {
		return VirtualKey.BY_CODE.get(code);
	}

}
