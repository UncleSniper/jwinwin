package org.unclesniper.winwin;

public interface WmActivate {

	public enum ActivateType {

		WA_INACTIVE,
		WA_ACTIVE,
		WA_CLICKACTIVE;

		private static final ActivateType[] VALUES = ActivateType.values();

		public static ActivateType byOrdinal(int ordinal) {
			return ActivateType.VALUES[ordinal];
		}

	}

	void wmActivate(HWnd hwnd, HWnd other, ActivateType type, boolean minimized);

}
