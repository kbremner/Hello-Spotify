package com.deftech.spotify;

import android.content.Context;

public class HelloSpotify {
	private final String cacheDir;
	static {
		System.loadLibrary("hello_spotify");
	}
	
	public HelloSpotify(Context context){
		cacheDir = context.getCacheDir().getAbsolutePath();
	}

	public int login(String username, String password){
		return login(username, password, cacheDir);
	}
	
	public native String getBuildID();
	private native int login(String username, String password, String cacheDir);
}
