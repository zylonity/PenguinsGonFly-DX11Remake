#include "game.h"
#include "GameManager.h"
#include <SpriteFont.h>
const std::string Game::MODE_NAME = "GAME";

Game::Game(MyD3D& d3d)
{

	DDS_ALPHA_MODE alpha;

	background.push_back(Sprite::Sprite());
	background[0].createSprite(d3d, L"bin/data/Background/sky.dds", Vector2(0, 0), false, bgScale);
	background[0].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(100);

	background.push_back(Sprite::Sprite());
	background[1].createSprite(d3d, L"bin/data/Background/TinyCloud5.dds", Vector2(0, 0), true, bgScale);
	background[1].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(110);

	background.push_back(Sprite::Sprite());
	background[2].createSprite(d3d, L"bin/data/Background/SmallCloud3.dds", Vector2(0, 0), true, bgScale);
	background[2].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(140);

	background.push_back(Sprite::Sprite());
	background[3].createSprite(d3d, L"bin/data/Background/MedCloud5.dds", Vector2(0, 0), true, bgScale);
	background[3].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(170);

	background.push_back(Sprite::Sprite());
	background[4].createSprite(d3d, L"bin/data/Background/BigCloud3.dds", Vector2(0, 0), true, bgScale);
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
	
}

void Game::Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse)
{
	auto kb = m_keyboard->GetState();

	

	if (player.isAlive != true) {
		GameManager::Get().SetScore(score);
		ReleaseGame(d3d);
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