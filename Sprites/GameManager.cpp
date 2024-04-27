#include "GameManager.h"
#include "game.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "leaderboard.h"


GameManager::GameManager(MyD3D& d3d)
	: mD3D(d3d)
{
	ls_textures = luaL_newstate();
	luaL_openlibs(ls_textures);

	if (!LuaOK(GameManager::Get().ls_textures, luaL_dofile(GameManager::Get().ls_textures, "bin/scripts/TextureLoader.lua")))
		assert(false);

	audio.Initialise();

	mMMgr.AddMode(new MainMenu(d3d));
	mMMgr.AddMode(new Game(d3d));
	mMMgr.AddMode(new GameOver(d3d));
	mMMgr.AddMode(new Leaderboard(d3d));

	mMMgr.SwitchMode(MainMenu::MODE_NAME);

	music_mute = false;
	music_volume = 50.0f;


	
}


//any memory or resources we made need releasing at the end
void GameManager::Release()
{

	//Save results to leaderboard file at the end
	leaderboard.open("leaderboard.csv");
	for (int i = 0; i < userScores.size(); i++) {
		leaderboard << to_wstring(userScores[i]) << ',' << userNames[i] << '\n';
	}
	leaderboard.close();
	
	

	mMMgr.Release();

	lua_close(ls_textures);

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

void GameManager::SetScore(int score) {
	PlayerScore = score;
}

void GameManager::SetName(wstring name) {
	PlayerName = name;
}