//------------------------------------------------------------------------------
//
// プレイヤー [CPlayer.h]
// Author : AT-13A-273 Shinnosuke Munakata
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------------------------
#define PLAYER_MOVE_SPEED (0.5f)
#define PLAYER_RELOAD_TIME (300)

//------------------------------------------------------------------------------
// ヘッダインクルード
//------------------------------------------------------------------------------
#include "Model.h"

//------------------------------------------------------------------------------
// 前方宣言
//------------------------------------------------------------------------------
class CBullet;

//------------------------------------------------------------------------------
// クラス宣言
//------------------------------------------------------------------------------
class CPlayer:public CModel
{
public:
	CPlayer(void);
	~CPlayer(void);

	void Init(void);
	void Update(void);

	// 現在の装填時間ゲッター
	int ReloadTimer(void){return _ReloadTimer;}

	static CPlayer* Create(int id, const VECTOR3& pos);

private:
CModel* Barrel;
	CBullet* Bullet;	// 弾
	VECTOR3 Movement;	// 移動量
	float Speed;		// 移動速度
	bool LaunchFlag;	// 弾発射フラグ（true / 使用：false / 不使用）
	int _ReloadTimer;	// 現在の装填時間
	float BarrelRotX;	// 砲身のX軸回転量
};

//------------------------------------------------------------------------------
// EOF