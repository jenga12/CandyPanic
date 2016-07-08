/*
 *	File：MainManager.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：メイン管理クラス定義
 */

#pragma once
#ifndef _MAIN_MANAGER_H_
#define _MAIN_MANAGER_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "Vector2D.h"
#include "Vector3D.h"
#include "StateManager.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/
struct INPUT{
	Vec2 pos;       // 現在の指の座標
	int flag;      // 指を置いた瞬間→1
};


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class CRenderer;

class CMainManager{
	public:
		static CMainManager *Create(unsigned short ScreenWidth, unsigned short ScreenHeight, JNIEnv *env, jobject AssetObject);
		virtual void Release(void);
		virtual int Update(int *position, float *sensor);
		virtual void Draw(void);
	
		virtual void Pause(void){
			m_pStateManager->Pause();
		}
	
		virtual void Resume(void){
			m_pStateManager->Resume();
		}

		static unsigned short GetScreenWidth(void){
			return SCREEN_WIDTH;
		}

		static unsigned short GetScreenHeight(void){
			return SCREEN_HEIGHT;
		}

		static const INPUT *GetInput(void){
			return &m_aInput[0];
		}

		static const Vec3 *GetSensor(void){
			return &m_sensor;
		}

		static AAssetManager* GetAssetManager(void){
			return m_AssetManager;
		}

		static CRenderer *GetRenderer(void){
			return m_pRenderer;
		}

	protected:
		CMainManager();
		~CMainManager(){};

	private:
		static unsigned short SCREEN_WIDTH;       // スクリーン幅
		static unsigned short SCREEN_HEIGHT;      // スクリーン高さ
		static INPUT m_aInput[1];                   // タッチ情報
		static Vec3 m_sensor;                       // センサー値
		static AAssetManager* m_AssetManager;       // アセットマネージャ

		static CRenderer *m_pRenderer;              // レンダラー
		static CStateManager *m_pStateManager;      // ステート管理クラス
};

class CNullMainManager : public CMainManager{
	public:
		CNullMainManager(){};
		~CNullMainManager(){};
		virtual void Release(void){delete this;}
		virtual int Update(int *position, float *sensor){return 1;}
		virtual void Draw(void){}
		virtual void Resume(void){}
		virtual void Pause(void){}
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif