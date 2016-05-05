package cn.tg.earth.view;


import android.app.Activity;
import android.os.Bundle;
import android.view.Window;

public class EarthGameActivity extends Activity {
	
	private Earth3DView view;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
    	requestWindowFeature(Window.FEATURE_NO_TITLE);
        super.onCreate(savedInstanceState);
   
        view = new Earth3DView(this);
        setContentView(view);
    }
}