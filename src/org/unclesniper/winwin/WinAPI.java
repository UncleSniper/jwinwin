package org.unclesniper.winwin;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.security.MessageDigest;
import java.io.FileNotFoundException;
import javax.xml.bind.DatatypeConverter;
import java.security.NoSuchAlgorithmException;
import org.unclesniper.winwin.resource.Resources;

public class WinAPI {

	static {
		try {
			WinAPI.bindNative();
		}
		catch(Exception e) {
			throw new UnsatisfiedLinkError(e.toString());
		}
	}

	public static final int COLOR_3DDKSHADOW = 21;
	public static final int COLOR_3DFACE = 15;
	public static final int COLOR_3DHIGHLIGHT = 20;
	public static final int COLOR_3DHILIGHT = 20;
	public static final int COLOR_3DLIGHT = 22;
	public static final int COLOR_3DSHADOW = 16;
	public static final int COLOR_ACTIVEBORDER = 10;
	public static final int COLOR_ACTIVECAPTION = 2;
	public static final int COLOR_APPWORKSPACE = 12;
	public static final int COLOR_BACKGROUND = 1;
	public static final int COLOR_BTNFACE = 15;
	public static final int COLOR_BTNHIGHLIGHT = 20;
	public static final int COLOR_BTNHILIGHT = 20;
	public static final int COLOR_BTNSHADOW = 16;
	public static final int COLOR_BTNTEXT = 18;
	public static final int COLOR_CAPTIONTEXT = 9;
	public static final int COLOR_DESKTOP = 1;
	public static final int COLOR_GRADIENTACTIVECAPTION = 27;
	public static final int COLOR_GRADIENTINACTIVECAPTION = 28;
	public static final int COLOR_GRAYTEXT = 17;
	public static final int COLOR_HIGHLIGHT = 13;
	public static final int COLOR_HIGHLIGHTTEXT = 14;
	public static final int COLOR_HOTLIGHT = 26;
	public static final int COLOR_INACTIVEBORDER = 11;
	public static final int COLOR_INACTIVECAPTION = 3;
	public static final int COLOR_INACTIVECAPTIONTEXT = 19;
	public static final int COLOR_INFOBK = 24;
	public static final int COLOR_INFOTEXT = 23;
	public static final int COLOR_MENU = 4;
	public static final int COLOR_MENUHILIGHT = 29;
	public static final int COLOR_MENUBAR = 30;
	public static final int COLOR_MENUTEXT = 7;
	public static final int COLOR_SCROLLBAR = 0;
	public static final int COLOR_WINDOW = 5;
	public static final int COLOR_WINDOWFRAME = 6;
	public static final int COLOR_WINDOWTEXT = 8;

	public static final int ERROR_HOTKEY_ALREADY_REGISTERED = 0x581;
	public static final int ERROR_HOTKEY_NOT_REGISTERED = 0x58B;

	private static final String DLL_NAME = "jwinwin";

	private static final char[] HEX_DIGITS = "0123456789ABCDEF".toCharArray();

	private static final ThreadLocal<Integer> LAST_ERROR = new ThreadLocal<Integer>();

	private static void bindNative() throws IOException {
		File userHome = new File(System.getProperty("user.home"));
		File dotJNI = new File(userHome, ".jni");
		if(!dotJNI.isDirectory() && !dotJNI.mkdir())
			throw new IOException("Failed to create directory: " + dotJNI.getAbsolutePath());
		File privDir = new File(dotJNI, WinAPI.class.getName());
		if(!privDir.isDirectory() && !privDir.mkdir())
			throw new IOException("Failed to create directory: " + privDir.getAbsolutePath());
		String resName = WinAPI.DLL_NAME + ".dll";
		MessageDigest digest;
		try {
			digest = MessageDigest.getInstance("SHA-256");
		}
		catch(NoSuchAlgorithmException nsae) {
			throw new Error("SHA-256 not supported");
		}
		byte[] buffer = new byte[1024];
		try(InputStream is = Resources.class.getResourceAsStream(resName)) {
			if(is == null)
				throw new FileNotFoundException("JWinWin was not packaged with a " + resName);
			for(;;) {
				int count = is.read(buffer);
				if(count <= 0)
					break;
				digest.update(buffer, 0, count);
			}
		}
		String hexName = DatatypeConverter.printHexBinary(digest.digest()) + ".dll";
		File hexFile = new File(privDir, hexName);
		if(!hexFile.exists()) {
			boolean done = false;
			try(
				InputStream is = Resources.class.getResourceAsStream(resName);
				FileOutputStream os = new FileOutputStream(hexFile);
			) {
				for(;;) {
					int count = is.read(buffer);
					if(count <= 0)
						break;
					os.write(buffer, 0, count);
				}
				done = true;
			}
			finally {
				if(!done)
					hexFile.delete();
			}
		}
		System.load(hexFile.getAbsolutePath());
		WinAPI.initNative();
	}

	public static void init() {}

	private static native void initNative();

	public static native int getLastError();

	private static void setRelayedLastError(int error) {
		if(error == 0)
			WinAPI.LAST_ERROR.remove();
		else
			WinAPI.LAST_ERROR.set(error);
	}

	public static int getRelayedLastError(boolean clear) {
		Integer error = WinAPI.LAST_ERROR.get();
		int code = error == null ? 0 : error.intValue();
		if(code == 0)
			return WinAPI.getLastError();
		if(clear)
			WinAPI.LAST_ERROR.remove();
		return code;
	}

	public static native String rawErrorMessageFromCode(int errorCode);

	public static String errorMessageFromCode(int errorCode) {
		String message = WinAPI.rawErrorMessageFromCode(errorCode);
		return message == null ? "Unknown error" : message;
	}

}
