package cn.tg.earth.view;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;

import com.objLoader.AppLib;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.graphics.PointF;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.util.Log;

public class Earth3DRender implements GLSurfaceView.Renderer {
	private Context context;

	public float width = 1, height = 1;

	public float fixed_zoom;
	float density;
	float mAngleX;
	float zoom;

	int viewport[] = new int[4];
	float projectionMatrix[] = new float[16];
	float modelViewMatrix[] = new float[16];
	boolean updateModelViewMatrix = true;

	private float outputfar[] = new float[4];
	private float outputnear[] = new float[4];

	public Earth3DRender(Context _context) {
		super();
		this.context = _context;
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		Log.d("Render Thread", "RenderThread==" + Thread.currentThread().getId());

		String apkFilePath = null;
		ApplicationInfo appInfo = null;
		PackageManager packMgmr = context.getPackageManager();

		try {
			appInfo = packMgmr.getApplicationInfo(context.getPackageName(), 0);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			throw new RuntimeException("Unable to locate assets, aborting...");
		}
		apkFilePath = appInfo.sourceDir;

		AppLib.onSurfaceCreated(apkFilePath);

		updateModelViewMatrix = true;

	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		GL11 gl11 = (GL11) gl;

		viewport[0] = 0;
		viewport[1] = 0;
		viewport[2] = width;
		viewport[3] = height;

		this.width = (float) width;
		this.height = (float) height;

		fixed_zoom = 55.0f;

		AppLib.resize(width, height);

		synchronized (outputfar) {
			gl11.glGetFloatv(GL11.GL_PROJECTION_MATRIX, projectionMatrix, 0);
		}
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		AppLib.renderFrame();
//			AppLib.loadAssetsObj("assets/table.obj", "assets/table.png");
		if (updateModelViewMatrix)
			synchronized (outputfar) {
				GL11 gl11 = (GL11) gl;
				gl11.glGetFloatv(GL11.GL_MODELVIEW_MATRIX, modelViewMatrix, 0);

				updateModelViewMatrix = false;
			}
	}

	public PointF windowToModel(PointF point) {
		float x1, y1, z1, x2, y2, z2, u;

		synchronized (outputfar) {
			GLU.gluUnProject(point.x, viewport[3] - point.y, 0.0f, modelViewMatrix, 0, projectionMatrix, 0, viewport, 0, outputnear, 0);
			GLU.gluUnProject(point.x, viewport[3] - point.y, 1.0f, modelViewMatrix, 0, projectionMatrix, 0, viewport, 0, outputfar, 0);
		}
		x1 = (outputfar[0] / outputfar[3]);
		y1 = (outputfar[1] / outputfar[3]);
		z1 = (outputfar[2] / outputfar[3]);
		x2 = (outputnear[0] / outputnear[3]);
		y2 = (outputnear[1] / outputnear[3]);
		z2 = (outputnear[2] / outputnear[3]);
		u = (0.0f - z1) / (z2 - z1);

		point.x = x1 + u * (x2 - x1); //x
		point.y = y1 + u * (y2 - y1); //y
		float zz = z1 + ((0.0f - y1) / (y2 - y1)) * (z2 - z1); //z
		
		Log.d("", "TouchUp----("+point.x+", "+point.y+", "+ zz +")");
		return point;
	}

}
