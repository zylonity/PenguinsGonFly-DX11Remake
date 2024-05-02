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

#include "ScreenText.h"

#include "GameManager.h"

#include "ModeMgr.h"
#include "Buttons.h"

class Leaderboard : public AMode{
	vector<Sprite> background;

	vector<Sprite> menuButtons;

	vector<float> bgTimers;
	vector<float> scrollSpeeds;
	float bgScale;

	Button mmBtn;
	Button quitBtn;

	Text title;
	Text positions[10];
	Text namestxt[10];
	Text scorestxt[10];


	std::wfstream scores;

	bool sortingNums;




public:
	static const std::string MODE_NAME;

	Leaderboard(MyD3D& d3d);

	//any memory or resources we made need releasing at the end
	void ResetScreen();

	//called over and over, use it to update game logic
	void Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse) override;


	//called over and over, use it to render things
	void Render(float dTime, MyD3D& d3d) override;

	std::string GetMName() const override;

};
