package org.unclesniper.winwin;

public interface WmGetMinMaxInfo {

	public class MinMaxInfo {

		public MinMaxInfo() {}

		public int maxSizeX;

		public int maxSizeY;

		public int maxPositionX;

		public int maxPositionY;

		public int minTrackSizeX;

		public int minTrackSizeY;

		public int maxTrackSizeX;

		public int maxTrackSizeY;

	}

	void wmGetMinMaxInfo(HWnd hwnd, MinMaxInfo info);

}
