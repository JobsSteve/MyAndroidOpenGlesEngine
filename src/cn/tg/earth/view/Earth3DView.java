package cn.tg.earth.view;

import com.objLoader.AppLib;

import android.content.Context;
import android.graphics.PointF;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class Earth3DView extends GLSurfaceView
{

	private Earth3DRender renderer;
	PointF touchPoint = new PointF();	// current position in field coordinates
	
	public Earth3DView(Context context) 
	{
		super(context);
		this.renderer = new Earth3DRender(context);
		this.setRenderer(this.renderer);
		
	}

	@Override
	public boolean onTouchEvent(final MotionEvent event) {
		touchPoint.x = event.getX();
		touchPoint.y = event.getY();

		renderer.windowToModel(touchPoint);

		switch (event.getActionMasked()) {
		case MotionEvent.ACTION_DOWN:
			AppLib.touchDown(touchPoint.x, touchPoint.y);
			requestRender();
			break;

		case MotionEvent.ACTION_MOVE:
			AppLib.touchMove(touchPoint.x, touchPoint.y);
	    	renderer.updateModelViewMatrix = true;
			requestRender();
			break;

		case MotionEvent.ACTION_UP:
			AppLib.touchUp(touchPoint.x, touchPoint.y);
			requestRender();
			break;

		default:
			break;
		}

		return true;
	}

	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh) {
		renderer.updateModelViewMatrix = true;
		super.onSizeChanged(w, h, oldw, oldh);
	}

}
