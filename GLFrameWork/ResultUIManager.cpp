//=============================================================================
//
// リザルトのUIを管理するよ [ResultUIManager.h]
//
// Auther : masato masuda
//
//=============================================================================

//=============================================================================
// include
//=============================================================================
#include "ResultUIManager.h"
#include "Texture.h"
#include "ResultSheet.h"
#include "ResultNumberManager.h"
#include "ManagerGL.h"

namespace{
	// sheet
	const float   RESULT_SHEET_SCALE = 1.0f;
	const VECTOR2 RESULT_SHEET_SIZE = VECTOR2(SCREEN_WIDTH * RESULT_SHEET_SCALE,256.0f * RESULT_SHEET_SCALE);
	const VECTOR2 RESULT_SHEET_BASE_SIZE = VECTOR2(RESULT_SHEET_SIZE.x * 0.95f,RESULT_SHEET_SIZE.y * 1.1f);
	const VECTOR3 RESULT_SHEET_POS = VECTOR3(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f + 200.0f,0);

	// name
	const float   NAME_SCALE = 1.3f;
	const VECTOR2 NAME_SIZE = VECTOR2(193 * NAME_SCALE,32 * NAME_SCALE);
	const float   NAME_POS_X_SUB = 170.0f;

	// texture
	const int NAME_TEX[CResultNumberManager::NUMBER_MAX] = {
		TEX_PLAYER_YOUJO_RED,TEX_PLAYER_YOUJO_BLUE,TEX_PLAYER_YOUJO_WATER,
		TEX_PLAYER_YOUJO_ORANGE,TEX_PLAYER_YOUJO_WHITE,TEX_PLAYER_YOUJO_YELLOW
	};
}

//=============================================================================
// constructor
//=============================================================================
CResultUIManager::CResultUIManager() :CObject(LAYER_NUM - 2)
{
	Logo = nullptr;
	ResultSheet = nullptr;
	ResultSheetBase = nullptr;
	ResultNumber = nullptr;
	memset(PlayerName,NULL,sizeof(PlayerName));
}

//=============================================================================
// create
//=============================================================================
CResultUIManager* CResultUIManager::Create(void)
{
	CResultUIManager* Scene = new CResultUIManager;
	Scene->Init();

	return Scene;
}

//=============================================================================
// init
//=============================================================================
void CResultUIManager::Init(void)
{
	// logo
	Logo = CPolygon2D::Create(VECTOR3(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f - 300.0f,0),VECTOR2(512.0f,128.0f));
	Logo->SetTex(CTexture::Texture(TEX_RESULT_LOGO));

	// 成績表の背景
	ResultSheetBase = CResultSheet::Create(RESULT_SHEET_POS,RESULT_SHEET_BASE_SIZE);
	ResultSheetBase->SetColor(COLOR(0.0f,0.0f,0.0f,0.3f));
	ResultSheetBase->SetAlphaMax(0.4f);

	// 成績表
	ResultSheet = CResultSheet::Create(RESULT_SHEET_POS,RESULT_SHEET_SIZE);
	ResultSheet->SetTex(CTexture::Texture(TEX_RESULT_TEXT));
	ResultSheet->SetAlpha(0.0f);

	// 成績表の番号
	ResultNumber = CResultNumberManager::Create();

	int* ranking = CManager::getRanking();

	// プレイヤー名
	for (int player = 0; player < PLAYER_MAX; player++)
	{
		VECTOR3 pos = ResultNumber->GetNumPosition((CResultNumberManager::TYPE)player);
		pos.x -= NAME_POS_X_SUB;
		PlayerName[player] = CResultSheet::Create(pos,NAME_SIZE);

		if (PlayerName[player] != nullptr)
		{
			PlayerName[player]->SetTex(CTexture::Texture(NAME_TEX[ranking[player]]));

			ResultNumber->SetNumber((CResultNumberManager::TYPE)player,
				CManager::userInfo[ranking[player]].kill,
				CManager::userInfo[ranking[player]].death);
		}
	}
}

//=============================================================================
// uninit
//=============================================================================
void CResultUIManager::Uninit(void)
{
	delete this;
}

//=============================================================================
// update
//=============================================================================
void CResultUIManager::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void CResultUIManager::Draw(void)
{
}

//=============================================================================
// SetResultSheetDisable
//-----------------------------------------------------------------------------
// 成績表を良い感じに消す
//=============================================================================
void CResultUIManager::SetResultSheetDisable(void)
{
	ResultSheet->DrawDisable();
	ResultSheetBase->DrawDisable();
}

//=============================================================================
// SetResultNumberDisable
//-----------------------------------------------------------------------------
// キルデスを良い感じに消す
//=============================================================================
void CResultUIManager::SetResultNumberDisable(void)
{
	ResultNumber->DrawDisable();
}

//=============================================================================
// SetResultPlayerNameDisable
//-----------------------------------------------------------------------------
// プレイヤー名を良い感じに消す
//=============================================================================
void CResultUIManager::SetResultPlayerNameDisable(void)
{
	for (int player = 0; player < PLAYER_MAX; ++player){
		PlayerName[player]->DrawDisable();
	}
}

//=============================================================================
// SetNumber
//-----------------------------------------------------------------------------
//  type   :  タイプ
//  kill   :  KILL数
//  DEATH  :  DEATH数
//=============================================================================
void CResultUIManager::SetNumber(CResultNumberManager::TYPE type,int kill,int death)
{
	ResultNumber->SetNumber(type,kill,death);
}


// end of file