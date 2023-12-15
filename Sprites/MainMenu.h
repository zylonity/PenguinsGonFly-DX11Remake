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
#include "Effects.h"
#include "Model.h"

#include "sprite.h"
#include "player.h"
#include "EnemyController.h"

#include "GameManager.h"

#include "ModeMgr.h"
#include "Buttons.h"

class MainMenu : public AMode{

	vector<Sprite> background;

	vector<Sprite> menuButtons;

	vector<float> bgTimers;
	vector<float> scrollSpeeds;
	float bgScale;
	float time;
	
	Button startBtn;
	Button quitBtn;
	Button leaderBtn;
	Button muteBtn;


	Sprite logo;

	bool isActive;

	float birdScale;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;

	IAudioMgr* pAudio;



public:
	static const std::string MODE_NAME;

	MainMenu(MyD3D& d3d);

	//any memory or resources we made need releasing at the end
	void ReleaseGame(){}

	//called over and over, use it to update game logic
	void Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse) override;


	//called over and over, use it to render things
	void Render(float dTime, MyD3D& d3d) override;

	void ResetMenu();

	std::string GetMName() const override;

};
