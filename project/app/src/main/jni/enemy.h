/*
 *	File：enemy.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：敵処理クラス定義
 */

#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "face.h"
#include "PanelManager.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class CPanelManager;
class C2DPolygon;
class C2DSprite;

class CEnemy {
	public:
		static CEnemy *Create(void);	// インスタンス生成
		void Release(void);				// インスタンス破棄
		void Update(void);				// 更新処理
		int Damage(int num);			// ダメージを与える

		void SetPanelManager(CPanelManager *pPM){
			m_pPM = pPM;
		}

		bool IsLife0(void){
			return (m_nLife > (250*LIFE_SCALE));
		}

		void SetEnemyFace(FACE_TYPE noFace);

	private:
		CEnemy();						// コンストラクタ
		~CEnemy(){};					// デストラクタ
		void Init(void);				// 初期化処理
	
		C2DPolygon *m_pAttack;			// アタックゲージ
		C2DPolygon *m_pLife;			// ライフゲージ
		C2DSprite *m_pIcon;				// アイコン
		CPanelManager *m_pPM;			// パネル管理クラス
		unsigned int m_nFrameCount;		// フレームカウンタ
		unsigned int m_nAttackInterval;	// 攻撃間隔	
		unsigned char m_nCombo;			// 残りコンボ数
		unsigned int m_nFaceFrameCount;	// 表情変化用フレームカウンタ
		FACE_TYPE m_nCurrentFace;		// 現在の表情
		
		unsigned short m_nLife;			// ライフ
	
		static const unsigned short LIFE_SCALE = 4;
		static const unsigned short ATTACK_INTERVAL_AVERAGE = 390;	// 平均攻撃間隔
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif