package org.unclesniper.winwin;

public final class HMenu {

	private final long handle;

	HMenu(long handle) {
		this.handle = handle;
	}

	long getHandle() {
		return handle;
	}

}
