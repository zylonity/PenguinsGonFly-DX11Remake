#pragma once
#include "LuaHelper.h"
#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <string> 

#include <filesystem>

#include "sprite.h"
#include "player.h"
#include "EnemyController.h"
#include "ModeMgr.h"
#include "ScreenText.h"
#include "GameManager.h"

class Game : public AMode {

	vector<Sprite> background;
	EnemyController enemiess;

	vector<float> bgTimers;
	vector<float> scrollSpeeds;
	float bgScale;

	int scoreMultiplier;
	int difficultyMultiplier;
	float score;

	
	float difficulty;

	Player player;
	Sprite shield;
	Text scoreindicator;
	Text scoreCounter;

	bool musicPaused;
	
	IAudioMgr* pAudio;

	lua_State* ls_textures;
	//lua_State* L;

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

	wstring StringToWString(const string& str);



};
