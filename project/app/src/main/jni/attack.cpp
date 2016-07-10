/*
 *	File：attack.cpp
 *	Make：HALTokyo AT-14A-275 Toshiki Chizo
 *	Outline：攻撃エフェクト処理クラス実装
 */

/******************************************************************************/
/*                            インクルードファイル                            */
/******************************************************************************/
#include "attack.h"
#include "Framework/MyMath.h"
#include "enemy.h"


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
//					CAttack クラス
//*************************************************
/*
 *	コンストラクタ
 */
CAttack :: CAttack():
C2DAnimation(3, 6),
m_fRot(0.0f),
m_bUse(false){
	
}

/*
 * クラス名：CAttack
 * 関数名：Create()
 * 内容：インスタンス生成
 * 引数：pEnemy            ;敵
 */
CAttack *CAttack :: Create(CEnemy *pEnemy){
	CAttack *p = new CAttack();
	p->Init();
	p->m_pEnemy = pEnemy;
	return p;
}

/*
 * クラス名：CAttack
 * 関数名：Init()
 * 内容：初期化処理
 */
void CAttack :: Init(void){
	Vec2 size(64.0f, 64.0f);
	Vec2 scl(2.0f, 2.0f);
	C2DAnimation :: Init("game/attack_star.img", &size);
	SetChangeFrame(2);
	SetLoop(true);
	SetScaling(&scl);

	Vec2 pos(1135.0f, 120.0f);
	m_pHit = C2DAnimation :: Create("game/attack_effect.img", &size, 3, 8);
	m_pHit->SetPosition(&pos);
	m_pHit->SetChangeFrame(4);
	m_pHit->SetScaling(&scl);
}

/*
 * クラス名：CAttack
 * 関数名：Destroy()
 * 内容：インスタンス破棄
 */
void CAttack :: Destroy(void){
	C2DAnimation :: Destroy();
	m_pHit->Release();
}

/*
 * クラス名：CAttack
 * 関数名：Update()
 * 内容：更新処理
 */
void CAttack :: Update(void){
	if(!m_bUse){
		return;
	}
	
	if(m_bHit){
		if(m_pHit->IncrementFrame()){
			m_bUse = false;
		}
	}
			
	if(m_fTime < 1.0f){
		IncrementFrame();
		
		/*** 回転させる ***/
		m_fRot += 0.1f;
		SetRotation(m_fRot);
		
		/*** ベジェ曲線上を移動 ***/
		m_fTime += 0.016f;
		Vec2 pos;
		pos.x = CMath :: Bezier(m_start.x, 1135.0f, 145.0f, 640.0f, m_fTime);
		pos.y = CMath :: Bezier(m_start.y, 120.0f, 120.0f, 0.0f, m_fTime);
		SetPosition(&pos);
		
	} else if(!m_bHit){
		UnlinkList();
		m_pHit->Seek(0);
		m_pHit->LinkList(OBJECT_2D_ATTACK_EFFECT );
		m_pHit->Play();
		m_bHit = true;
		m_fTime = 0.0f;
		m_pEnemy->Damage(m_nDamage);
	}
}

/*
 * クラス名：CAttack
 * 関数名：Start()
 * 内容：エフェクトを開始
 * 引数：pDefaultPos		;初期位置
 *       damage             ;与えるダメージ
 */
void CAttack :: Start(const Vec2 *pDefaultPos, int damage){
	m_start = *pDefaultPos;
	LinkList(OBJECT_2D_ATTACK_EFFECT);
	m_fTime = 0.0f;
	m_fRot = 0.0f;
	m_bUse = true;
	m_bHit = false;
	m_nDamage = damage;
	Seek(0);
	C2DAnimation :: Play();
}