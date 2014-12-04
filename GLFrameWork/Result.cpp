#include "main.h"
#include "Result.h"
#include "ManagerGL.h"
#include "Keyboard.h"
#include "Polygon2D.h"
#include "Model.h"
CResult::CResult()
{

}

CResult::~CResult()
{

}

void CResult::Init(void)
{
	CPolygon2D* polygon = CPolygon2D::Create(VECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f-100.0f,0),VECTOR2(512.0f,128.0f));
	polygon->SetTex(CTexture::Texture(TEX_RESULT_LOGO));
}

void CResult::Uninit(void)
{
	CObject::ReleaseAll();
}

void CResult::Update(void)
{

	if (CKeyboard::GetTrigger(DIK_RETURN))
	{
		CManager::ChangeScene(SCENE_TITLE);
	}
}