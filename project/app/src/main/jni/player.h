/*
 *	File：player.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：プレイヤー処理クラス定義
 */

#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "face.h"


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
class C2DSprite;
class C2DPolygon;
class CSound;

class CPlayer{
	public:
		static CPlayer *Create(void);	// インスタンス生成
		void Release(void);				// インスタンス破棄
		int Update(float fDensity, bool bErase);		// 更新処理
	
		void SetPlayerFace(FACE_TYPE face, int frame);		// プレイヤーの表情を設定

		bool IsLife0(void){
			return (m_nLife == 0);
		}
		
	private:
		void Init(void);				// 初期化処理
		CPlayer();						// コンストラクタ
		~CPlayer(){};					// デストラクタ
	
		C2DSprite *m_pIcon;				// プレイヤーアイコン
		C2DPolygon *m_pLife;			// ライフゲージ
		C2DPolygon *m_pDensity;			// 密度ゲージ
	
		FACE_TYPE m_nCurrentFace;		// 現在の表情
		unsigned int m_nFrameCount;		// フレームカウンタ
		unsigned int m_nFrame;			// フレームカウンタ
		unsigned short m_nLife;			// ライフ

		CSound *m_pAlarm;               // アラーム
		bool m_bAlarm;                  // アラーム再生フラグ
		static const unsigned short LIFE_SCALE = 4;
};

/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif