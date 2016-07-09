/*
 *	File：2DSprite.h
 *	Make：HALTokyo AT-13A-272 16 Toshiki Chizo
 *	Outline：2Dテクスチャつきポリゴン処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "2DSprite.h"
#include "TextureManager.h"


/******************************************************************************/
/*                               静的変数初期化                               */
/******************************************************************************/


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
//				   C2DSprite クラス
//*************************************************
/*
 *	コンストラクタ
 */
C2DSprite :: C2DSprite(unsigned int nPriority):
		m_pos(Vec2(0.0f, 0.0f)),
		m_fRot(0.0f),
		m_scl(Vec2(1.0f, 1.0f)),
		C2DObject(nPriority){

	m_VtxData.pClr = new Color_32[4];
	m_VtxData.pPos = new Vec2[4];
	m_VtxData.pTex = new Vec2[4];

	m_VtxData.pClr[0] = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
	m_VtxData.pClr[1] = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
	m_VtxData.pClr[2] = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
	m_VtxData.pClr[3] = Color_32(1.0f, 1.0f, 1.0f, 1.0f);
};

/*
 * クラス名：C2DSprite
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTexFileName		;テクスチャファイル名
 *		 pSize				;ポリゴンのサイズ
 *		 nPriority			;描画優先度
 */
C2DSprite *C2DSprite :: Create(const char *pTexFileName, const Vec2 *pSize, unsigned int nPriority){
	C2DSprite *p = new C2DSprite(nPriority);
	p->m_pTextureManager = CTextureManager :: Create(pTexFileName);

	p->m_VtxData.pPos[0] = Vec2(pSize->x * -0.5f, pSize->y * 0.5f);
	p->m_VtxData.pPos[1] = Vec2(pSize->x * -0.5f, pSize->y * -0.5f);
	p->m_VtxData.pPos[2] = Vec2(pSize->x * 0.5f, pSize->y * 0.5f);
	p->m_VtxData.pPos[3] = Vec2(pSize->x * 0.5f, pSize->y * -0.5f);
	p->m_VtxData.pTex[0] = Vec2(0.0f, 1.0f);
	p->m_VtxData.pTex[1] = Vec2(0.0f, 0.0f);
	p->m_VtxData.pTex[2] = Vec2(1.0f, 1.0f);
	p->m_VtxData.pTex[3] = Vec2(1.0f, 0.0f);

	return p;
}

/*
 * クラス名：C2DSprite
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pTextureManager		;テクスチャ管理クラス
 *		 pSize					;ポリゴンのサイズ
 *		 nPriority				;描画優先度
 */
C2DSprite *C2DSprite :: Create(CTextureManager *pTextureManager, const Vec2 *pSize, unsigned int nPriority){
	C2DSprite *p = new C2DSprite(nPriority);
	p->m_pTextureManager = pTextureManager;

	p->m_VtxData.pPos[0] = Vec2(pSize->x * -0.5f, pSize->y * 0.5f);
	p->m_VtxData.pPos[1] = Vec2(pSize->x * -0.5f, pSize->y * -0.5f);
	p->m_VtxData.pPos[2] = Vec2(pSize->x * 0.5f, pSize->y * 0.5f);
	p->m_VtxData.pPos[3] = Vec2(pSize->x * 0.5f, pSize->y * -0.5f);
	p->m_VtxData.pTex[0] = Vec2(0.0f, 1.0f);
	p->m_VtxData.pTex[1] = Vec2(0.0f, 0.0f);
	p->m_VtxData.pTex[2] = Vec2(1.0f, 1.0f);
	p->m_VtxData.pTex[3] = Vec2(1.0f, 0.0f);

	return p;
}

/*
 * クラス名：C2DSprite
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pTexFileName			;テクスチャ管理クラス
 *		 pSize					;ポリゴンのサイズ
 * 返却値：	処理成功 -> 0
 *			処理失敗 -> -1
 */
int C2DSprite :: Init(const char *pTexFileName, const Vec2 *pSize){
	m_pTextureManager = CTextureManager :: Create(pTexFileName);
	m_VtxData.pPos[0] = Vec2(pSize->x * -0.5f, pSize->y * 0.5f);
	m_VtxData.pPos[1] = Vec2(pSize->x * -0.5f, pSize->y * -0.5f);
	m_VtxData.pPos[2] = Vec2(pSize->x * 0.5f, pSize->y * 0.5f);
	m_VtxData.pPos[3] = Vec2(pSize->x * 0.5f, pSize->y * -0.5f);
	m_VtxData.pTex[0] = Vec2(0.0f, 1.0f);
	m_VtxData.pTex[1] = Vec2(0.0f, 0.0f);
	m_VtxData.pTex[2] = Vec2(1.0f, 1.0f);
	m_VtxData.pTex[3] = Vec2(1.0f, 0.0f);
	return 0;
}

/*
 * クラス名：C2DSprite
 * 関数名：Init()
 * 内容：初期化処理
 * 引数：pTextureManager		;テクスチャ管理クラス
 * 		 pSize				;ポリゴンのサイズ
 * 返却値：	処理成功 -> 0
 *			処理失敗 -> -1
 */
int C2DSprite :: Init(CTextureManager *pTextureManager, const Vec2 *pSize){
	m_pTextureManager = pTextureManager;
	m_VtxData.pPos[0] = Vec2(pSize->x * -0.5f, pSize->y * 0.5f);
	m_VtxData.pPos[1] = Vec2(pSize->x * -0.5f, pSize->y * -0.5f);
	m_VtxData.pPos[2] = Vec2(pSize->x * 0.5f, pSize->y * 0.5f);
	m_VtxData.pPos[3] = Vec2(pSize->x * 0.5f, pSize->y * -0.5f);
	m_VtxData.pTex[0] = Vec2(0.0f, 1.0f);
	m_VtxData.pTex[1] = Vec2(0.0f, 0.0f);
	m_VtxData.pTex[2] = Vec2(1.0f, 1.0f);
	m_VtxData.pTex[3] = Vec2(1.0f, 0.0f);
	return 0;
}


/*
 * クラス名：C2DSprite
 * 関数名：Destroy()
 * 内容：インスタンス破棄
 */
void C2DSprite :: Destroy(void){
	m_pTextureManager->Release();
	delete[] m_VtxData.pPos;
	delete[] m_VtxData.pClr;
	delete[] m_VtxData.pTex;
	delete this;
}

/*
 * クラス名：C2DSprite
 * 関数名：Draw()
 * 内容：描画処理
 */
void C2DSprite :: Draw(void){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(m_pos.x, m_pos.y, 0.0f);
	glRotatef((m_fRot * 180.0f) / PI, 0.0f, 0.0f, 1.0f);
	glScalef(m_scl.x, m_scl.y, 1.0f);

	m_pTextureManager->SetTexture();

	glVertexPointer(2, GL_FLOAT, 0, m_VtxData.pPos);
	glColorPointer(4, GL_FLOAT, 0, m_VtxData.pClr);
	glTexCoordPointer(2, GL_FLOAT, 0, m_VtxData.pTex);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glPopMatrix();
}