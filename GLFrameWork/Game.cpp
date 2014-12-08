#include "main.h"
#include "Game.h"
#include "ManagerGL.h"
#include "Keyboard.h"
#include "Billboard.h"
#include "Effect3D.h"
#include "Polygon3D.h"
#include "Texture.h"
#include "MeshGround.h"
#include "MeshSphere.h"
#include "Model.h"
#include "Camera.h"
#include "PlayerCamera.h"

// 静的メンバ変数
const float CGame::RADIUS_SKY = 500.0f;   // 空の半径
#include "CPlayer.h"

CPlayer* g_player;
CModel* g_model;


CGame::CGame()
{

}
CGame::~CGame()
{

}

void CGame::Init(void)
{

  // 地形生成
  Ground = nullptr;
  Ground = CMeshGround::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2(50.0f, 50.0f), VECTOR2(20.0f, 20.0f));
  Ground->SetTex(CTexture::Texture(TEX_FIELD));

  // 空生成
  Sky = nullptr;
  Sky = CMeshSphere::Create(VECTOR3(0.0f, 0.0f, 0.0f), VECTOR2(16.0f, 8.0f), RADIUS_SKY);
  Sky->SetTex(CTexture::Texture(TEX_MIKU));

  // プレイヤー生成
  Player = CModel::Create(CModel::MIKU, VECTOR3(0.0f, 0.0f, 0.0f));
  Player->SetTex(CTexture::Texture(TEX_MIKU));
  Player->SetScl(20.0f, 20.0f, 20.0f);

  
	
	//CPolygon3D* polygon = CPolygon3D::Create(VECTOR3(-200.0f,0,0),VECTOR2(250.0f,250.0f),VECTOR3(0,0,90.0f));
	//polygon->SetTex(CTexture::Texture(TEX_LIGHT));
	//polygon->SetColor(GREEN(1.0f));
	CPolygon3D::Create(VECTOR3(0,-100.0f,0),VECTOR2(500.0f,500.0f),VECTOR3(0.0f,0,0));

	// 2014-12-01
	// 宗像：テスト
	g_player = CPlayer::Create(CModel::MIKU, VECTOR3(0.0f, 0.0f, 0.0f));
	g_player->SetTex(CTexture::Texture(TEX_MIKU));
	g_player->SetScl(VECTOR3(60.0f, 60.0f, 60.0f));

	CPlayerCamera* camera = CPlayerCamera::Create(g_player,400.0f);
	
	//g_player->SetRotY(180.0f);
	
	/*
	g_model = CModel::Create(CModel::MIKU, VECTOR3(0.0f, 0.0f, 0.0f));
	//g_model->SetTex(CTexture::Texture(TEX_MIKU));
	g_model->SetScl(VECTOR3(60.0f, 60.0f, 60.0f));
	g_model->SetRotY(180.0f);
	*/

}

void CGame::Uninit(void)
{
  // プレイヤー破棄
  if (Player != nullptr)
  {
    Player->Release();
    Player = nullptr;
  }

  // 空破棄
  if (Sky != nullptr)
  {
    Sky->Release();
    Sky = nullptr;
  }

  // 地形破棄
  if (Ground != nullptr)
  {
    Ground->Release();
    Ground = nullptr;
  }
  CCamera::Release();
	CObject::ReleaseAll();
}

void CGame::Update(void)
{
  // プレイヤー移動
  if (CKeyboard::GetPress(DIK_W))
  {
    Player->AddPosZ(1.0f);
  }
  else if (CKeyboard::GetPress(DIK_S))
  {
    Player->AddPosZ(-1.0f);
  }
  if (CKeyboard::GetPress(DIK_A))
  {
    Player->AddPosX(1.0f);
  }
  else if (CKeyboard::GetPress(DIK_D))
  {
    Player->AddPosX(-1.0f);
  }

  // 地形とのあたり判定
  VECTOR3 NormalGround;   // 地形の法線
  float   HeightGround;   // 地形の高さ
  HeightGround = Ground->GetHeight(Player->Pos(), &NormalGround);
  NormalGround.Normalize();

  // 回転を求める
  VECTOR3 VectorUpPlayer; // 上方向ベクトル
  VECTOR3 VectorNormalYZ; // YZ平面上の法線ベクトル
  VECTOR3 VectorNormalXY; // XY平面上の法線ベクトル
  float   AnglePlayerX;   // プレイヤー回転X軸
  float   AnglePlayerZ;   // プレイヤー回転Z軸
  VectorUpPlayer.x = VectorUpPlayer.z = 0.0f;
  VectorUpPlayer.y = 1.0f;
  VectorNormalYZ.x = 0.0f;
  VectorNormalYZ.y = NormalGround.y;
  VectorNormalYZ.z = NormalGround.z;
  VectorNormalYZ.Normalize();
  AnglePlayerX = VECTOR3::Dot(VectorNormalYZ, VectorUpPlayer);
  VectorNormalXY.x = NormalGround.x;
  VectorNormalXY.y = NormalGround.y;
  VectorNormalXY.z = 0.0f;
  VectorNormalXY.Normalize();
  AnglePlayerZ = VECTOR3::Dot(VectorNormalXY, VectorUpPlayer);

  // プレイヤーに設定する
  Player->SetPosY(HeightGround);
  Player->SetRot(180.0f / PI * AnglePlayerX, 0.0f, 180.0f / PI * AnglePlayerZ);

	if (CKeyboard::GetTrigger(DIK_RETURN))
	{
		CManager::ChangeScene(SCENE_RESULT);
	}
}