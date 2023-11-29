#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include <vector>



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

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


const int ASCII_ESC = 27;


class Game {

	vector<Sprite> background;
	EnemyController enemiess;
	//vector<Enemy> enemies;

	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	vector<float> bgTimers;
	vector<float> scrollSpeeds;
	float bgScale = 6;

	Player player;

public:
	Game(MyD3D& d3d)
	{
		DDS_ALPHA_MODE alpha;

		m_keyboard = std::make_unique<Keyboard>();
		m_mouse = std::make_unique<Mouse>();
		//m_mouse->SetWindow(window);
		
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

		enemiess.enemies.push_back(Enemy::Enemy());
		enemiess.enemies[0].createSprite(d3d, L"bin/data/Entities/penguinplane_backwards.dds", Vector2(900, 250), true, 3.5f, true, 3, 10.0f);
		enemiess.enemies[0].moveSpeed = 500.0f;
	}


	//any memory or resources we made need releasing at the end
	void ReleaseGame()
	{
		
	}

	//called over and over, use it to update game logic
	void Update(float dTime, MyD3D& d3d)
	{
		//Movement
		auto kb = m_keyboard->GetState();
		if (kb.Escape)
		{
			PostQuitMessage(0);
			
		}

		enemiess.enemies[0].SetHitbox();


		player.HandleMovement(kb, dTime);

		player.HandleCollisions(enemiess.enemies);// enemies);

		player.Update();

		enemiess.EnemySpawn(dTime);


		
	}

	//called over and over, use it to render things
	void Render(float dTime, MyD3D& d3d)
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
		enemiess.enemies[0].RenderSprite();

		float bgWidth = background[1].texSize.x;

		//Scrolling background
		
		for (int i = 0; i < bgTimers.size(); i++) {
			bgTimers[i] += dTime;

			float scroll = bgTimers[i] * scrollSpeeds[i];

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


};


//if ALT+ENTER or resize or drag window we might want do
//something like pause the game perhaps, but we definitely
//need to let D3D know what's happened (OnResize_Default).
void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}

//messages come from windows all the time, should we respond to any specific ones?
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
	// Respond to a keyboard event.
	case WM_ACTIVATEAPP:
		Keyboard::ProcessMessage(msg, wParam, lParam);
		Mouse::ProcessMessage(msg, wParam, lParam);
		break;
	case WM_ACTIVATE:
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(msg, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(msg, wParam, lParam);
		break;

	case WM_SYSKEYDOWN:
		Keyboard::ProcessMessage(msg, wParam, lParam);
		if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
		}
		break;
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::Get().DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

	int w(1280), h(720);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Penguins gon fly", MainWndProc, true))
		assert(false);

	MyD3D d3d;
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil& wu = WinUtil::Get();
	wu.SetD3D(d3d);
	Game game = Game::Game(d3d);


	bool canUpdateRender;
	float dTime = 0;
	while (wu.BeginLoop(canUpdateRender))
	{
		if (canUpdateRender)
		{
			game.Update(dTime, d3d);
			game.Render(dTime, d3d);
		}
		dTime = wu.EndLoop(canUpdateRender);
	}

	game.ReleaseGame();
	d3d.ReleaseD3D(true);	
	return 0;
}