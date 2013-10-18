package com.deftech.wrapify;

import android.content.Context;

public class Wrapify {
	private final String cacheDir;
	static {
		System.loadLibrary("Wrapify");
	}
	
	public Wrapify(Context context){
		cacheDir = context.getCacheDir().getAbsolutePath();
	}

	public int login(String username, String password){
		return login(username, password, cacheDir);
	}
	
	public native String getBuildID();
	private native int login(String username, String password, String cacheDir);
}
