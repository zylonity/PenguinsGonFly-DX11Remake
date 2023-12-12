#include "GameManager.h"
#include "game.h"
#include "MainMenu.h"

GameManager::GameManager(MyD3D& d3d)
	: mD3D(d3d)
{
	mMMgr.AddMode(new MainMenu(d3d));
	mMMgr.AddMode(new Game(d3d));

	mMMgr.SwitchMode(MainMenu::MODE_NAME);
}


//any memory or resources we made need releasing at the end
void GameManager::Release()
{

	mMMgr.Release();
}

//called over and over, use it to update game logic
void GameManager::Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse)
{
	mMMgr.Update(dTime, d3d, m_keyboard, m_mouse);
}

//called over and over, use it to render things
void GameManager::Render(float dTime, MyD3D& d3d)
{
	mMMgr.Render(dTime, d3d);

}