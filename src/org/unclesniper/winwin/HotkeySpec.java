package org.unclesniper.winwin;

public final class HotkeySpec {

	private final VirtualKey key;

	private final int modifiers;

	public HotkeySpec(VirtualKey key, int modifiers) {
		if(key == null)
			throw new IllegalArgumentException("Virtual key cannot be null");
		this.key = key;
		this.modifiers = modifiers & VirtualKey.MODMASK_IN;
	}

	public VirtualKey getKey() {
		return key;
	}

	public int getModifiers() {
		return modifiers;
	}

	@Override
	public boolean equals(Object other) {
		if(!(other instanceof HotkeySpec))
			return false;
		HotkeySpec spec = (HotkeySpec)other;
		return key == spec.key && (modifiers & VirtualKey.MODMASK_OUT) == (spec.modifiers & VirtualKey.MODMASK_OUT);
	}

	@Override
	public int hashCode() {
		return key.getCode() * 0x0010 + (modifiers & VirtualKey.MODMASK_OUT);
	}

}
