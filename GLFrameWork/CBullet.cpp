//------------------------------------------------------------------------------
//
// 弾 [CBullet.cpp]
// Author : AT-13A-273 Shinnosuke Munakata
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ヘッダインクルード
//------------------------------------------------------------------------------
#include <math.h>

#include "CBullet.h"
#include "CPlayer.h"

//------------------------------------------------------------------------------
// コンストラクタ
//------------------------------------------------------------------------------
// 引数
//  なし
//------------------------------------------------------------------------------
CBullet::CBullet():CBillboard()
{
	// 速度
	Movement = VECTOR3(0.0f, 0.0f, 0.0f);

	// テクスチャ
	Texture = CTexture::Texture(TEX_BULLET);
	SetUV(0,0,1.0f,1.0f);
}

//------------------------------------------------------------------------------
// デストラクタ
//------------------------------------------------------------------------------
// 引数
//  なし
//------------------------------------------------------------------------------
CBullet::~CBullet()
{

}

//------------------------------------------------------------------------------
// 初期化
//------------------------------------------------------------------------------
// 引数
//  なし
// 戻り値
//  なし
//------------------------------------------------------------------------------
void CBullet::Init(void)
{
	VECTOR3 rot;
	rot.x = DEG2RAD(_Rot.x);
	rot.y = DEG2RAD(_Rot.y);
	rot.z = 0;

	REVISE_PI(rot.x);
	REVISE_PI(rot.y);
	Movement.x = sinf(rot.y) * (cosf(rot.x)*BULLET_SPEED);
	Movement.y = -sinf(rot.x) * BULLET_SPEED;
	Movement.z = cosf(rot.y) * (cosf(rot.x)*BULLET_SPEED);

	CBillboard::Init();
}

//------------------------------------------------------------------------------
// 更新
//------------------------------------------------------------------------------
// 引数
//  なし
// 戻り値
//  なし
//------------------------------------------------------------------------------
void CBullet::Update(void)
{
	// 移動
	AddPos(Movement);

	// 当たり判定

	// 速度の減退
	Movement.y -= 0.25f;

	// 消滅処理
	if(_Pos.y <= -100.0f)
	{
		Release();
	}
}

//------------------------------------------------------------------------------
// 生成
//------------------------------------------------------------------------------
// 引数
//  pos : 位置
//  size : サイズ
//  rot : 回転
//  color : 色
// 戻り値
//  CBullet : 生成した弾のポインタ
//------------------------------------------------------------------------------
CBullet* CBullet::Create(const VECTOR3& pos,const VECTOR2& size,const VECTOR3& rot,const COLOR& color)
{
	CBullet* Scene = new CBullet;
	Scene->_Pos = pos;
	Scene->_Rot = rot;
	Scene->_Size = size;
	Scene->_Color = color;

	Scene->Init();

	return Scene;
}

//------------------------------------------------------------------------------
// EOF