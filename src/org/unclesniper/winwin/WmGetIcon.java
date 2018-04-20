package org.unclesniper.winwin;

public interface WmGetIcon {

	public enum GetIconType {

		ICON_SMALL,
		ICON_BIG,
		ICON_SMALL2;

		private static final GetIconType[] VALUES = GetIconType.values();

		public static GetIconType byOrdinal(int ordinal) {
			return GetIconType.VALUES[ordinal];
		}

	}

	HIcon wmGetIcon(HWnd hwnd, GetIconType type, int dpi);

}
