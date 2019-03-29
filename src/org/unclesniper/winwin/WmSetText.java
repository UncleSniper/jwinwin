package org.unclesniper.winwin;

public interface WmSetText {

	public enum SetTextResult {

		FALSE,
		TRUE,
		LB_ERRSPACE,
		CB_ERRSPACE,
		CB_ERR;

		private static final SetTextResult[] VALUES = SetTextResult.values();

		public static SetTextResult byOrdinal(int ordinal) {
			return SetTextResult.VALUES[ordinal];
		}

	}

	SetTextResult wmSetText(HWnd hwnd, String text);

}
