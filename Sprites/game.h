#pragma once
#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"
#include "Mouse.h"
#include "Keyboard.h"


#include "sprite.h"
#include "player.h"
#include "EnemyController.h"
#include "ModeMgr.h"
#include "ScreenText.h"

class Game : public AMode {

	vector<Sprite> background;
	EnemyController enemiess;

	vector<float> bgTimers;
	vector<float> scrollSpeeds;
	float bgScale = 6;

	const int scoreMultiplier = 10;
	int difficultyMultiplier = 10;
	float score;

	
	float difficulty;

	Player player;
	Text scoreindicator;
	Text scoreCounter;

public:

	static const std::string MODE_NAME;

	Game(MyD3D& d3d);

	//any memory or resources we made need releasing at the end
	void ReleaseGame(MyD3D& d3d);


	//called over and over, use it to update game logic
	void Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse) override;
	

	//called over and over, use it to render things
	void Render(float dTime, MyD3D& d3d) override;

	std::string GetMName() const override;

};
