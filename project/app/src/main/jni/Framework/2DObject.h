/*
 *	File：2DObject.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dオブジェクト処理クラス定義
 */

#pragma once
#ifndef _2D_OBJECT_H_
#define _2D_OBJECT_H_

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "define.h"


/******************************************************************************/
/*                              ライブラリリンク                              */
/******************************************************************************/


/******************************************************************************/
/*                              マクロ＆定数定義                              */
/******************************************************************************/


/******************************************************************************/
/*                                 構造体定義                                 */
/******************************************************************************/
enum _2D_OBJECT {
	OBJECT_2D_UNKNOWN = 0,		// よくわからないオブジェクト(テスト等に使用)
	OBJECT_2D_FADE,				// フェードオブジェクト
	OBJECT_2D_TEST_POLYGON,		// テスト用ポリゴン
	OBJECT_2D_TITLE_BACKGROUND, // タイトル背景
	OBJECT_2D_PAD,                // パッド画像
	OBJECT_2D_UI_ICON,           // UIアイコン画像
	OBJECT_2D_CLEAR_BACKGROUND,	// リザルト背景
	OBJECT_2D_MESSAGE,           // デンタル大佐のお言葉
	OBJECT_2D_NUMBER,
	MAX_2D_OBJECT
};


/******************************************************************************/
/*                                 クラス定義                                 */
/******************************************************************************/
class C2DObject {
	public:
		static void ReleaseCheckAll(void);		// 全オブジェクトの破棄フラグチェック
		static void DrawAll(void);				// 全オブジェクトの描画
		static void ReleaseAll(void);			    // 全オブジェクトの破棄

		void Release(void){m_bErase = true;};	    // 削除フラグを立てる
		virtual void Destroy(void) = 0;			// オブジェクト破棄処理

		void LinkList(_2D_OBJECT objType);		    // リストにオブジェクトを追加する
		void UnlinkList(void);					    // リストからオブジェクトを除去する

		static C2DObject *GetFirst(_2D_OBJECT objType){	// リストの先頭取得
			return m_apFirst[objType];
		}

		C2DObject *GetNext(void){					// リストの次の要素取得
			return m_pNext;
		}

		void SetPriority(unsigned int nPriority){	// 描画優先度設定
			m_nPriority = nPriority;
		};

	protected:
		C2DObject(unsigned int nPriority);		    // コンストラクタ
		~C2DObject();							    // デストラクタ

	private:
		static void QuickSort(	unsigned int Lnum, unsigned int Rnum,
		                          C2DObject **pObjectListTop);	// 描画優先度ソート

		virtual void Draw(void) = 0;					// 描画処理


		static unsigned int m_nObjects;				// リストに登録されているオブジェクトの数
		static C2DObject *m_apFirst[MAX_2D_OBJECT];	// 先頭の要素
		static C2DObject *m_apLast[MAX_2D_OBJECT];	// 末尾の要素
		C2DObject *m_pPrev;								// 前の要素
		C2DObject *m_pNext;								// 次の要素
		unsigned int m_nPriority;						// 描画優先度
		bool m_bList;									// リストに追加されたオブジェクトかどうか
		bool m_bErase;									// 削除フラグ
		_2D_OBJECT m_objType;							// オブジェクト種別
};


/******************************************************************************/
/*                              プロトタイプ宣言                              */
/******************************************************************************/


/******************************************************************************/

#endif