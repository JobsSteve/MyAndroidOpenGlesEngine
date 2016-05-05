/*
 * Copyright (C) 2009 The Android Open Source Project
 * Copyright (C) 2014 Dennis Sheil
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
package com.unwrappedapps.android.demo;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;

public class GL1DemoActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLView = new DemoGLSurfaceView(this);
        setContentView(mGLView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    private GLSurfaceView mGLView;

    static {
        System.loadLibrary("gl1");
    }
}

class DemoGLSurfaceView extends GLSurfaceView {

    int flip;

    public DemoGLSurfaceView(Context context) {
        super(context);
        mRenderer = new DemoRenderer();
        flip = 1;
        setRenderer(mRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            if (flip == 1) {
                flip = 0;
            }
            else {
                flip = 1;
            }
            nativeTogglePauseResume(flip);
        }
        return true;
    }

   @Override
    public void onPause() {
        super.onPause();
        //nativePause();
    }

   @Override
    public void onResume() {
        super.onResume();
        //nativeResume();
    }


    DemoRenderer mRenderer;

    //private static native void nativePause();
    //private static native void nativeResume();
    private static native void nativeTogglePauseResume(int flip);
}

class DemoRenderer implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeInit();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    private static native void nativeInit();
    private static native void nativeResize(int w, int h);
    private static native void nativeRender();
    //private static native void nativeDone();
}
