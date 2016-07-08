package agarte_lindblum.hal.candypanic;

import android.app.Activity;
import android.graphics.Point;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;

import java.lang.reflect.Method;
import java.util.List;

/**
 * Created by Toshiki Chizo on 2016/07/08.
 */
public class MainActivity extends Activity implements SensorEventListener {
	private Vec2 m_scale;                               // ディスプレイサイズに適用
	private MainSurfaceView m_sv;                       // サーフェイスビュー
	private GLSurfaceView m_glsv;                       // GLサーフェイスビュー
	private static final float APP_WIDTH = 1280.0f; // アプリケーション想定スクリーン幅
	private static final float APP_HEIGHT = 720.0f; // アプリケーション想定スクリーン高さ
	private float m_fRotate[];                        // 端末の傾き
	private float m_fMagnetic[];                     // 傾き算出用
	private float m_fAccelerometer[];               // 傾き算出用
	private float m_inR[];                            // 傾き算出用
	private float m_I[];                              // 傾き算出用
	private float m_outR[];                          // 傾き算出用
	private SensorManager m_SensorManager;           // センサー

	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		Vec2 size = GetDisplaySize();
		m_scale = new Vec2(APP_WIDTH / size.x, APP_HEIGHT / size.y);

		m_fRotate = new float[3];
		m_fMagnetic = new float[3];
		m_fAccelerometer = new float[3];
		m_inR = new float[16];
		m_I = new float[16];
		m_outR = new float[16];

		m_glsv = new GLSurfaceView(this);
		m_sv = new MainSurfaceView(this, size);
		m_glsv.setRenderer(m_sv);
		m_glsv.setSystemUiVisibility(
				View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
						View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
						View.SYSTEM_UI_FLAG_FULLSCREEN |
						View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN |
						View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY

		);

		setContentView(m_glsv);

		m_sv.Initialize((int)size.x, (int)size.y, getResources().getAssets(), System.currentTimeMillis());
		m_sv.Pause();       // GLの準備ができるまでポーズ状態
	}

	private Vec2 GetDisplaySize(){
		Display display = getWindowManager().getDefaultDisplay();
		Vec2 size = new Vec2(0.0f, 0.0f);

		if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1){
			Point point = new Point();
			display.getRealSize(point);
			size.x = point.x;
			size.y = point.y;

		} else if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2){
			try{
				Method getRawWidth = Display.class.getMethod("getRawWidth");
				Method getRawHeight = Display.class.getMethod("getRawHeight");
				size.x = (float)getRawWidth.invoke(display);
				size.y = (float)getRawHeight.invoke(display);

			} catch(Exception err){
				err.printStackTrace();
			}
		}

		m_SensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);

		return size;
	}

	@Override
	protected void onResume(){
		super.onResume();
		m_glsv.onResume();

		List<Sensor> sensors = m_SensorManager.getSensorList(Sensor.TYPE_ALL);
		for(Sensor sens : sensors){
			if(sens.getType() == Sensor.TYPE_MAGNETIC_FIELD){
				m_SensorManager.registerListener(this, sens, SensorManager.SENSOR_DELAY_GAME);
			}

			if(sens.getType() == Sensor.TYPE_ACCELEROMETER){
				m_SensorManager.registerListener(this, sens, SensorManager.SENSOR_DELAY_GAME);
			}
		}
	}

	@Override
	protected void onPause(){
		super.onPause();
		m_sv.Pause();
		m_glsv.onPause();
		m_SensorManager.unregisterListener(this);
	}

	@Override
	protected void onDestroy(){
		m_sv.Finalize();
		super.onDestroy();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event){
		if(m_sv == null){
			return true;
		}

		switch(event.getAction()){
			case MotionEvent.ACTION_DOWN:
				m_sv.SetTrigger((int)event.getX(), (int)event.getY());
				break;
		}

		return true;
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		/*** センサー値取得 ***/
		switch(event.sensor.getType()){
			case Sensor.TYPE_MAGNETIC_FIELD:
				m_fMagnetic = event.values.clone();
				break;

			case Sensor.TYPE_ACCELEROMETER:
				m_fAccelerometer = event.values.clone();
				break;
		}

		if((m_fAccelerometer != null) && (m_fMagnetic != null)){
			SensorManager.getRotationMatrix(m_inR, m_I, m_fAccelerometer, m_fMagnetic);
			SensorManager.remapCoordinateSystem(m_inR, SensorManager.AXIS_X, SensorManager.AXIS_Y,m_outR);
			SensorManager.getOrientation(m_outR, m_fRotate);
		}

		/*** 軸を横持ち状態に合わせて、右回転を＋符号に調整 ***/
		m_sv.SetSensor(m_fRotate[2], m_fRotate[0], -(m_fRotate[1]));
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {

	}
}
