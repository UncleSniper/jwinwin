package org.unclesniper.winwin;

public interface WmSize {

	public enum SizeType {

		SIZE_RESTORED,
		SIZE_MINIMIZED,
		SIZE_MAXIMIZED,
		SIZE_MAXSHOW,
		SIZE_MAXHIDE;

		private static final SizeType[] VALUES = SizeType.values();

		public static SizeType byOrdinal(int ordinal) {
			return SizeType.VALUES[ordinal];
		}

	}

	void wmSize(HWnd hwnd, SizeType type, int width, int height);

}
