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

class MainMenu : public AMode{

	vector<Sprite> background;

	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	vector<float> bgTimers;
	vector<float> scrollSpeeds;
	float bgScale = 6;

public:
	static const std::string MODE_NAME;

	MainMenu(MyD3D& d3d);

	//any memory or resources we made need releasing at the end
	void ReleaseGame(){}

	//called over and over, use it to update game logic
	void Update(float dTime, MyD3D& d3d) override;


	//called over and over, use it to render things
	void Render(float dTime, MyD3D& d3d) override;

	std::string GetMName() const override;

};
