/*
 *	File：main.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：Javaとの連携処理 (エントリーポイント)
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "main.h"
#include <jni.h>
#include "Framework/TextureManager.h"
#include "Framework/MainManager.h"
#include "Framework/2DObject.h"
#include "Framework/MyRand.h"
#include "Framework/sound.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/


/******************************************************************************/
/*                                  定数定義                                  */
/******************************************************************************/


/******************************************************************************/
/*                               グローバル変数                               */
/******************************************************************************/
static CMainManager *g_pMainManager = new CNullMainManager();
static bool g_bPause = false;


/******************************************************************************/
/*                                サブルーチン                                */
/******************************************************************************/
/*
 *  初期化処理
 */
extern "C"
void Java_agarte_1lindblum_hal_candypanic_MainSurfaceView_Initialize(JNIEnv *env, jobject clazz, jint width, jint height, jobject AssetObject, jlong time){
    /*** サウンドの全体初期化 ***/
    CSound :: Initialize();

    g_pMainManager->Release();      // NULLクラス破棄
    g_pMainManager = CMainManager :: Create(width, height, env, AssetObject);

    /*** 乱数の全体初期化 ***/
    init_genrand(time);
}

/*
 *  終了処理
 */
extern "C"
void Java_agarte_1lindblum_hal_candypanic_MainSurfaceView_Finalize(JNIEnv *env, jobject clazz){
    /*** NULLクラスに入れ替える ***/
    g_pMainManager->Release();
    g_pMainManager = new CNullMainManager();

    /*** 全てのオブジェクトを片付ける ***/
    C2DObject::ReleaseAll();
    C2DObject::ReleaseCheckAll();

    /*** サウンド全体終了 ***/
    CSound :: Finalize();
}

/*
 *  中断処理
 */
extern "C"
void Java_agarte_1lindblum_hal_candypanic_MainSurfaceView_Pause(JNIEnv *env, jobject clazz){
    g_pMainManager->Pause();
    g_bPause = true;
    CTextureManager :: UnregistAll();
}

/*
 *  再開処理
 */
extern "C"
void Java_agarte_1lindblum_hal_candypanic_MainSurfaceView_Resume(JNIEnv *env, jobject clazz){
    CTextureManager :: RegistAll();
    g_pMainManager->Resume();
    g_bPause = false;
}

/*
 *  フレーム更新
 */
extern "C"
int Java_agarte_1lindblum_hal_candypanic_MainSurfaceView_Frame(JNIEnv *env, jobject clazz, jintArray pos, jfloatArray sens){
    if(g_bPause){
        return 0;
    }

    int result = 0;
    jboolean b;

    /*** Javaから配列をうけとる ***/
    int *position = env->GetIntArrayElements(pos, &b);
    float *sensor = env->GetFloatArrayElements(sens, &b);

    /*** メイン更新 ***/
    result = g_pMainManager->Update(position, sensor);

    /*** メイン描画 ***/
    g_pMainManager->Draw();

    /*** Javaへ戻る前に片づける ***/
    env->ReleaseIntArrayElements(pos, position, 0);
    env->ReleaseFloatArrayElements(sens, sensor, 0);

    return result;
}
