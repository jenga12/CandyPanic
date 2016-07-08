/*
 *	File：2DObject.cpp
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dオブジェクト処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DObject.h"
#include <stddef.h>
#include <malloc.h>


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/
C2DObject *C2DObject :: m_apFirst[MAX_2D_OBJECT] = {NULL};
C2DObject *C2DObject :: m_apLast[MAX_2D_OBJECT] = {NULL};
unsigned int C2DObject :: m_nObjects = 0;



/******************************************************************************/
/*                                  定数定義                                  */
/******************************************************************************/


/******************************************************************************/
/*                               グローバル変数                               */
/******************************************************************************/


/******************************************************************************/
/*                                 クラス実装                                 */
/******************************************************************************/
//*************************************************
//				  C2DObject クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DObject :: C2DObject(unsigned int nPriority):
		m_nPriority(nPriority),
		m_bList(false),
		m_bErase(false),
		m_objType(OBJECT_2D_UNKNOWN),
		m_pPrev(NULL),
		m_pNext(NULL){

}

/*
 *	デストラクタ
 */
C2DObject :: ~C2DObject(){
	UnlinkList();
}

/*
 * クラス名：C2DObject
 * 関数名：LinkList()
 * 内容：リストにオブジェクトを追加する
 */
void C2DObject :: LinkList(_2D_OBJECT objType){
	if(!m_bList){
		++m_nObjects;
		m_pNext = NULL;

		if(m_apFirst[objType] == NULL){
			m_apFirst[objType] = this;
			m_apLast[objType] = this;
		} else {
			m_apLast[objType]->m_pNext = this;
			m_pPrev = m_apLast[objType];
			m_apLast[objType] = this;
		}

		m_objType = objType;
		m_bList = true;
	}
}

/*
 * クラス名：C2DObject
 * 関数名：UnlinkList()
 * 内容：リストからオブジェクトを除去する
 */
void C2DObject :: UnlinkList(void){
	if(m_bList){
		--m_nObjects;

		if(m_apFirst[m_objType] == this){
			m_apFirst[m_objType] = m_pNext;

			if(m_apFirst[m_objType] == NULL){
				m_apLast[m_objType] = NULL;
			} else {
				m_apFirst[m_objType]->m_pPrev = NULL;
			}

		} else if(m_apLast[m_objType] == this){
			m_apLast[m_objType] = m_pPrev;
			m_apLast[m_objType]->m_pNext = NULL;

		} else {
			m_pPrev->m_pNext = m_pNext;
			m_pNext->m_pPrev = m_pPrev;
		}

		m_bList = false;
	}
}

/*
 * クラス名：C2DObject
 * 関数名：ReleaseCheckAll()
 * 内容：全オブジェクトの破棄フラグチェック
 */
void C2DObject :: ReleaseCheckAll(void){
	C2DObject *pNext, *p;

	for(int i = 0; i < MAX_2D_OBJECT; ++i){
		for(p = m_apFirst[i]; p != NULL; p = pNext){
			pNext = p->m_pNext;
			if(p->m_bErase){
				p->Destroy();
			}
		}
	}
}

/*
 * クラス名：C2DObject
 * 関数名：DrawAll()
 * 内容：全オブジェクトの描画
 */
void C2DObject :: DrawAll(void){
	if(m_nObjects){
		C2DObject **ppObjectListTop = (C2DObject**)malloc(sizeof(int) * m_nObjects);
		C2DObject **ppObjectList = ppObjectListTop;
		C2DObject *p;

		/*** 全要素を配列につめる ***/
		for(unsigned int i = 0; i < MAX_2D_OBJECT; ++i){
			for(p = m_apFirst[i]; p != NULL; p = p->m_pNext){
				*ppObjectList = p;
				++ppObjectList;
			}
		}

		/*** 全要素を描画優先度順にソート ***/
		QuickSort(0, m_nObjects - 1, ppObjectListTop);

		/*** 全要素の描画 ***/
		ppObjectList = ppObjectListTop;
		for(unsigned int i = 0; i < m_nObjects; ++i, ++ppObjectList){
			(*ppObjectList)->Draw();
		}

		free(ppObjectListTop);
	}
}

/*
 * クラス名：C2DObject
 * 関数名：ReleaseAll()
 * 内容：全オブジェクト破棄
 */
void C2DObject :: ReleaseAll(void){
	C2DObject *p, *pNext;
	for(int i = 0; i < MAX_2D_OBJECT; ++i){
		for(p = m_apFirst[i]; p != NULL; p = pNext){
			pNext = p->m_pNext;
			p->Destroy();
		}
	}
}

/*
 * クラス名：C2DObject
 * 関数名：QuickSort()
 * 内容：オブジェクトを描画優先度順にソート (降順)
 * 引数：Lnum			;整列対象グループの左端の要素番号
 *		 Rnum			;整列対象グループの右端の要素番号
 *		 pObjectListTop	;整列対象
 */
void C2DObject :: QuickSort(unsigned int Lnum, unsigned int Rnum, C2DObject **pObjectListTop){
	unsigned int Base = (Lnum + Rnum) >> 1;		// 基準値の要素番号
	C2DObject *pSwapWork;						// データ入れ替え時の作業用
	long long i, j;								// カウンタ変数

	i = Lnum;
	j = Rnum;

	while(1){
		/*** 基準値より小さい値をみつける ***/
		while(pObjectListTop[i]->m_nPriority > pObjectListTop[Base]->m_nPriority){
			++i;
		}

		/*** 基準値より大きい値を見つける ***/
		while(pObjectListTop[j]->m_nPriority < pObjectListTop[Base]->m_nPriority){
			--j;
		}

		/*** 衝突したら終了 ***/
		if(i >= j){
			break;
		}

		/*** 要素の入れ替え ***/
		pSwapWork = pObjectListTop[i];
		pObjectListTop[i] = pObjectListTop[j];
		pObjectListTop[j] = pSwapWork;

		++i;
		--j;
	}

	/*** 再帰呼び出し ***/
	if(Lnum < i - 1){
		QuickSort(Lnum, (unsigned int)(i - 1), pObjectListTop);
	}

	/*** 再帰呼び出し ***/
	if(j + 1 < Rnum){
		QuickSort((unsigned int)(j + 1), Rnum, pObjectListTop);
	}
}