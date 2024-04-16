#pragma once

#include "Singleton.h"
#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "AudioMgrFMOD.h"

#include "sprite.h"
#include "player.h"
#include "EnemyController.h"
#include "ModeMgr.h"
#include <fstream>

class GameManager : public Singleton<GameManager>
{
public:


	GameManager(MyD3D& d3d);
	~GameManager() {
		Release();
	}
	void Release();
	void Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse);
	void Render(float dTime, MyD3D& d3d);
	void ProcessKey(char key) {
		mMMgr.ProcessKey(key);
	}

	void SetScore(int score);
	int GetScore() { return PlayerScore; }

	void SetName(wstring name);
	wstring GetName() { return PlayerName; }

	MyD3D& GetD3D() { return mD3D; }
	ModeMgr& GetModeMgr() { return mMMgr; }


	//Shared resources
	vector<int> userScores;
	vector<wstring> userNames;

	AudioMgrFMOD audio;
	unsigned int musicHdl;

	bool music_mute;
	float music_volume;




private:
	MyD3D& mD3D;
	ModeMgr mMMgr;
	int PlayerScore;
	wstring PlayerName;
	std::wofstream leaderboard;
};
