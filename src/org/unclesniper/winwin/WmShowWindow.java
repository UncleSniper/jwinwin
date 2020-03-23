package org.unclesniper.winwin;

public interface WmShowWindow {

	public enum ShowWindow {

		BY_SHOWWINDOW,
		SW_PARENTCLOSING,
		SW_OTHERZOOM,
		SW_PARENTOPENING,
		SW_OTHERUNZOOM;

		private static final ShowWindow[] VALUES = ShowWindow.values();

		public static ShowWindow byOrdinal(int ordinal) {
			return ShowWindow.VALUES[ordinal];
		}

	}

	void wmShowWindow(HWnd hwnd, boolean shown, ShowWindow reason);

}
