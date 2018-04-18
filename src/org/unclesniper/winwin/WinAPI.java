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

	private static final String DLL_NAME = "jwinwin";

	private static final char[] HEX_DIGITS = "0123456789ABCDEF".toCharArray();

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

	public static native String rawErrorMessageFromCode(int errorCode);

	public static String errorMessageFromCode(int errorCode) {
		String message = WinAPI.rawErrorMessageFromCode(errorCode);
		return message == null ? "Unknown error" : message;
	}

}
