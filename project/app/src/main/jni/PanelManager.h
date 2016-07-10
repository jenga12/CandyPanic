/*
 *	File：PanelManager.h
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：パネル管理クラス定義
 */

#pragma once
#ifndef _PANEL_MANAGER_H_
#define _PANEL_MANAGER_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "Framework/Vector2D.h"
#include "gyro.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/
static const unsigned char FIELD_ROW = 14;		// フィールドの列数
static const unsigned char FIELD_LINE = 14;		// フィールドの行数
static const float PANEL_INTERVAL = 50.0f;		// 敷き詰めるパネル同士の間隔

static const Vec2 PanelSize(64.0f, 64.0f);		// パネルの大きさ(ポリゴンサイズ)
static const Vec2 FieldPos(290.0f, 10.0f);		// フィールドの位置(パネルの配置位置)
static const Vec2 LeftTopPanelPos(PANEL_INTERVAL * 0.5f + FieldPos.x, PANEL_INTERVAL * 0.5f + FieldPos.y);	// 左上のパネルの座標

static const float PANEL_MOVE_SPEED = 36.0f;

/*** パネル種別の定数 ***/
typedef char PANEL_COLOR;
static const PANEL_COLOR PANEL_NONE = -1;		// パネルがない
static const PANEL_COLOR PANEL_PINK = 0;		// 桃色パネル
static const PANEL_COLOR PANEL_CYAN = 1;		// 水色パネル
static const PANEL_COLOR PANEL_GREEN = 2;		// 緑色パネル
static const PANEL_COLOR PANEL_ORANGE = 3;		// 橙色パネル
static const PANEL_COLOR PANEL_BLUE = 4;		// 青色パネル
static const PANEL_COLOR PANEL_COLOR_NUM = 4;	// パネルの色数
static const PANEL_COLOR PANEL_GRAY = 125;		// おじゃまパネル
static const PANEL_COLOR PANEL_BLOCK = 127;		// ブロック

static const char PANEL_ERASE_TERM = 5;			// いくつ以上繋がればパネルを消すか


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class CPanel;
class CTextureManager;
class C2DAnimation;
class CScore;
class CPlayer;

class CPanelManager {
	public:
		static CPanelManager *Create(CPlayer *pPlayer);			// インスタンス生成
		void Release(void);			// インスタンス破棄
		float Update(void);			// 更新処理
		void PaddingGray(int num);     // おじゃまを発生させる
		void ClearPanel(void);		// パネル消去
		
	private:
		CPanelManager();			// コンストラクタ
		~CPanelManager(){};			// デストラクタ
		int Init(void);				// 初期化処理
		int PanelCount(int x, int y, PANEL_COLOR color, int count);	// つながっているパネルの数を数える
		void PanelErase(int x, int y, PANEL_COLOR color);			// つながっているパネルを消す

		/*** パネル操作系 ***/
		void PaddingLeft(void);		// 左方向にパネルを敷き詰める
		void PaddingRight(void);	// 右方向にパネルを敷き詰める
		void PaddingDown(void);		// 下方向にパネルを敷き詰める
		void PaddingUp(void);		// 上方向にパネルを敷き詰める
		void SlideLeft(void);		// 左方向にパネルをスライドさせる
		void SlideRight(void);		// 右方向にパネルをスライドさせる
		void SlideDown(void);		// 下方向にパネルをスライドさせる
		void SlideUp(void);			// 上方向にパネルをスライドさせる
		void PaddingGrayLeft(int num);	// 左方向におじゃまパネルを敷き詰める
		void PaddingGrayRight(int num);	// 右方向におじゃまパネルを敷き詰める
		void PaddingGrayDown(int num);	// 下方向におじゃまパネルを敷き詰める
		void PaddingGrayUp(int num);	// 上方向におじゃまパネルを敷き詰める

		void ClearCheckFlag(void);									// チェックフラグをリセットする
		void CreatePanel(int x, int y);								// 指定位置にパネルを生成

		PANEL_COLOR m_aField[FIELD_ROW][FIELD_LINE];				// フィールドデータ
		bool m_bCheckFlag[FIELD_ROW][FIELD_LINE];					// チェックフラグ
		CPanel *m_apPanel[FIELD_ROW][FIELD_LINE];					// パネルデータ
	
		/*** パネルテクスチャ ***/
		CTextureManager *m_apTexPanel[PANEL_COLOR_NUM];				// パネル
		CTextureManager *m_pTexGray;								// おじゃまパネル

		/*** エフェクトテクスチャ ***/
		CTextureManager *m_apTexEffect[PANEL_COLOR_NUM];			// エフェクト
		CTextureManager *m_pTexGrayEffect;							// おじゃまパネルのエフェクト
		CGyro *m_pGyro;                                             // ジャイロ
		CScore *m_pScore;

		CPlayer *m_pPlayer;                                         // プレイヤー
		unsigned int m_nSlideCount;                               // スライド回数
		unsigned int m_nCombo;                                    // コンボ数
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif