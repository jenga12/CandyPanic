package agarte_lindblum.hal.candypanic;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by Toshiki Chizo on 2016/07/08.
 */
public class MainSurfaceView implements GLSurfaceView.Renderer {
	private int position[];             // タッチ座標
	private float sensor[];             // センサー
	private MainActivity m_activity;    // アクティビティ
	private Vec2 m_DisplaySize;         // ディスプレイサイズ
	private boolean m_bFrameUpdate;

	static {
		System.loadLibrary("main");
	}

	public static native void Initialize(int width, int height, AssetManager asset, long time);
	public static native void Finalize();
	public static native void Pause();
	public static native void Resume();
	private static native int Frame(int position[], float sensor[]);
	private boolean m_bInitialize;

	public MainSurfaceView(Context context, Vec2 DisplaySize){
		m_bInitialize = false;
		position = new int[3];
		sensor = new float[3];
		position[0] = 0;
		position[1] = 0;
		position[2] = 0;
		sensor[0] = 0;
		sensor[1] = 0;
		sensor[2] = 0;
		m_activity = (MainActivity)context;
		m_DisplaySize = DisplaySize;
		m_bFrameUpdate = false;
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {

	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		//Initialize(width, height, m_activity.getResources().getAssets(), System.currentTimeMillis());
		Resume();
		m_bInitialize = true;
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		if(m_bInitialize) {
			m_bFrameUpdate = true;
			Frame(position, sensor);
			m_bFrameUpdate = false;
			position[2] = 0;
		}
	}

	public void SetTrigger(int x, int y){
		/*** フレーム更新が終わるのを待つ ***/
		while(m_bFrameUpdate){}

		position[0] = x;
		position[1] = y;
		position[2] = 1;
	}

	public void SetSensor(float x, float y, float z){
		sensor[0] = x;
		sensor[1] = y;
		sensor[2] = z;
	}
}
