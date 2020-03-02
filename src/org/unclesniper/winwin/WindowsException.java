package org.unclesniper.winwin;

public class WindowsException extends RuntimeException {

	private final int errorCode;

	public WindowsException(String message) {
		this(message, WinAPI.getRelayedLastError(true));
	}

	public WindowsException(String message, int errorCode) {
		super((message == null || message.length() == 0 ? "" : message + ": ")
				+ WinAPI.errorMessageFromCode(errorCode));
		this.errorCode = errorCode;
	}

	public int getErrorCode() {
		return errorCode;
	}

}
