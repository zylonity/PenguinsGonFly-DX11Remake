#include "game.h"
#include "GameManager.h"
#include <SpriteFont.h>
const std::string Game::MODE_NAME = "GAME";

Game::Game(MyD3D& d3d)
{

	DDS_ALPHA_MODE alpha;

	bgScale = LuaGetFloat(GameManager::Get().ls_textures, "backgroundsScale");
	scoreMultiplier = 10;
	difficultyMultiplier = 10;

	//Add background
	background.push_back(Sprite::Sprite());
	background[0].createSprite(d3d, LuaGetStr(GameManager::Get().ls_textures, "background0.Loc"), LuaGetVector2(GameManager::Get().ls_textures, "background0.StartPos"), true, LuaGetFloat(GameManager::Get().ls_textures, "background0.Scale"));
	background[0].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(100);

	background.push_back(Sprite::Sprite());
	background[1].createSprite(d3d, LuaGetStr(GameManager::Get().ls_textures, "background1Loc"), LuaGetVector2(GameManager::Get().ls_textures, "background1StartPos"), true, LuaGetFloat(GameManager::Get().ls_textures, "background1Scale"));
	background[1].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(110);

	background.push_back(Sprite::Sprite());
	background[2].createSprite(d3d, LuaGetStr(GameManager::Get().ls_textures, "background2Loc"), LuaGetVector2(GameManager::Get().ls_textures, "background2StartPos"), true, LuaGetFloat(GameManager::Get().ls_textures, "background2Scale"));
	background[2].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(140);

	background.push_back(Sprite::Sprite());
	background[3].createSprite(d3d, LuaGetStr(GameManager::Get().ls_textures, "background3Loc"), LuaGetVector2(GameManager::Get().ls_textures, "background3StartPos"), true, LuaGetFloat(GameManager::Get().ls_textures, "background3Scale"));
	background[3].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(170);

	background.push_back(Sprite::Sprite());
	background[4].createSprite(d3d, LuaGetStr(GameManager::Get().ls_textures, "background4Loc"), LuaGetVector2(GameManager::Get().ls_textures, "background4StartPos"), true, LuaGetFloat(GameManager::Get().ls_textures, "background4Scale"));
	background[4].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(200);


	//Make player texture
	player.createSprite(d3d, L"bin/data/Entities/birdneutralsprite.dds", Vector2(200, 100), true, 5.0f, true, 5, 10.0f);
	player.moveSpeed = 650.0f;

	enemiess.SpawnEnemies(d3d);

	scoreindicator.createText(d3d, L"Score:", Vector2(50, 20), Color::Color(Colors::White), 1);

	scoreCounter.createText(d3d, L"000", Vector2(230, 20), Color::Color(Colors::White), 1);

	score = 0;
	difficulty = 0;

	pAudio = &GameManager::Get().audio;


	string shieldLoc = LuaGetStr(GameManager::Get().ls_textures, "shieldSpriteLoc");
	shield.createSprite(d3d, shieldLoc, LuaGetVector2(GameManager::Get().ls_textures, "shieldPos"), true, LuaGetFloat(GameManager::Get().ls_textures, "shieldScale"));

}

void Game::Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse)
{
	auto kb = m_keyboard->GetState();

	if (!pAudio->GetSongMgr()->IsPlaying(GameManager::Get().musicHdl))
		pAudio->GetSongMgr()->Play("game", true, false, &GameManager::Get().musicHdl, GameManager::Get().music_volume);

	pAudio->GetSongMgr()->Mute(GameManager::Get().music_mute);



	//Dead or alive code
	if (player.isAlive != true) {
		GameManager::Get().SetScore(score);
		ReleaseGame(d3d);
		pAudio->GetSongMgr()->Stop();
		GameManager::Get().GetModeMgr().SwitchMode("OVER");
	}
	else {
		difficulty += difficultyMultiplier * dTime;
		player.HandleMovement(kb, dTime);

		player.HandleCollisions(enemiess.enemies);// enemies);

		player.Update();

		enemiess.EnemySpawn(dTime, difficulty);

		score += scoreMultiplier * dTime;

		scoreCounter.changeText(std::to_wstring((int)score));
	}



}

void Game::Render(float dTime, MyD3D& d3d)
{
	WinUtil& wu = WinUtil::Get();


	d3d.BeginRender(Vector4(0, 0, 0, 0));

	//put background to render here
	if (background.empty() == false) {
		for (int i = 0; i < background.size(); i++) {
			background[i].RenderSprite();
		}
	}

	player.RenderSprite();
	enemiess.RenderEnemies();

	shield.RenderSprite();

	//Draw text on screen
	scoreindicator.write();
	scoreCounter.write();


	float bgWidth = background[1].texSize.x;

	//Scrolling background

	for (int i = 0; i < bgTimers.size(); i++) {
		bgTimers[i] += dTime;

		float scroll = bgTimers[i] * (scrollSpeeds[i] + difficulty);

		if (background[i].pos.x <= -(bgWidth * bgScale)) {
			background[i].pos.x = 0;
			bgTimers[i] = 0;
		}
		else {
			background[i].pos.x = -scroll;
		}
	}



	d3d.EndRender();
}

void Game::ReleaseGame(MyD3D& d3d) {
	//Release/reset game
	enemiess.enemies.clear();
	player.pos = Vector2(200, 100);
	if (background.empty() == false) {
		for (int i = 0; i < background.size(); i++) {
			background[i].pos = Vector2(0, 0);
		}
	}
	enemiess.SpawnEnemies(d3d);
	player.isAlive = true;
	player.isVisible = true;
	score = 0;
	difficulty = 0;

}


std::string Game::GetMName() const {

	return MODE_NAME;
}
