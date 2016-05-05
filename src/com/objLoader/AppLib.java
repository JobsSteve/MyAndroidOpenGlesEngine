package com.objLoader;



public class AppLib 
{

	static {
        System.loadLibrary("app");
    }
	public static native void touchDown(float x, float y);
	public static native void touchMove(float x, float y);
	public static native void touchUp(float x, float y);
	public static native void loadAssetsObj(String obj, String texture);
	public static native void renderFrame();
	public static native void resize(int width, int height);
	public static native void onSurfaceCreated(String apkPath);
}
