#include "Splash.h"
#include "ManagerGL.h"
#include "Polygon2D.h"
#include "CommonGL.h"
#include "Input/VC.h"

CSplash::CSplash()
{
	Logo = nullptr;

}

CSplash::~CSplash()
{

}

void CSplash::Init(void)
{
	Logo = CPolygon2D::Create(VECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0),VECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT));
	Logo->SetTex(CTexture::Texture(TEX_TEAM_LOGO));
	Frame = 0;
}

void CSplash::Uninit(void)
{
	Logo->Release();
	Logo = nullptr;
}

void CSplash::Update(void)
{
	if (Frame>90 || VC::Instance()->Trigger(COMMAND_OK))
	{
		CManager::ChangeScene(SCENE_TITLE);
	}

	Frame++;

}