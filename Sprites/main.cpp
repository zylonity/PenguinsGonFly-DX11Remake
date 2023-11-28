#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include <vector>
#include <random>


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

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


const int ASCII_ESC = 27;


int randomNumber(int a, int b = 0) {

	int min, max;
	if (a > b) {
		min = b;
		max = a;
	}
	else if (b > a) {
		min = a;
		max = b;
	}
	else if (b == a) {
		return b;
	}

	LARGE_INTEGER seed;
	QueryPerformanceCounter(&seed);

	std::mt19937 rng(seed.QuadPart);
	std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased

	return gen(rng);

}

class Game {

	ID3D11ShaderResourceView* textures[7];

	vector<Sprite> sprites;
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;

	vector<float> bgTimers;
	vector<float> scrollSpeeds;
	float bgScale = 6;

public:
	Game(MyD3D& d3d)
	{
		DDS_ALPHA_MODE alpha;

		m_keyboard = std::make_unique<Keyboard>();
		m_mouse = std::make_unique<Mouse>();
		//m_mouse->SetWindow(window);
		
		//Make background texture
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Background/sky.dds", nullptr, &textures[0], 0, &alpha) != S_OK)
			assert(false);
		
		sprites.push_back(Sprite::Sprite(Vector2(0, 0), Vector2(1280, 720), textures[0], d3d));
		sprites[0].scale = bgScale;
		sprites[0].sprRect.right *= 2;
		bgTimers.push_back(0);
		scrollSpeeds.push_back(100);

		
		//Clouds
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Background/TinyCloud5.dds", nullptr, &textures[1], 0, &alpha) != S_OK)
			assert(false);

		sprites.push_back(Sprite::Sprite(Vector2(0, 0), Vector2(1280, 720), textures[1], d3d, true));
		sprites[1].scale = bgScale;
		sprites[1].sprRect.right *= 2;
		bgTimers.push_back(0);
		scrollSpeeds.push_back(110);
		
		
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Background/SmallCloud3.dds", nullptr, &textures[2], 0, &alpha) != S_OK)
			assert(false);

		sprites.push_back(Sprite::Sprite(Vector2(0, 0), Vector2(1280, 720), textures[2], d3d, true));
		sprites[2].scale = bgScale;
		sprites[2].sprRect.right *= 2;
		bgTimers.push_back(0);
		scrollSpeeds.push_back(140);
		
		
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Background/MedCloud5.dds", nullptr, &textures[3], 0, &alpha) != S_OK)
			assert(false);

		sprites.push_back(Sprite::Sprite(Vector2(0, 0), Vector2(1280, 720), textures[3], d3d, true));
		sprites[3].scale = bgScale;
		sprites[3].sprRect.right *= 2;
		bgTimers.push_back(0);
		scrollSpeeds.push_back(170);

		
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Background/BigCloud3.dds", nullptr, &textures[4], 0, &alpha) != S_OK)
			assert(false);

		sprites.push_back(Sprite::Sprite(Vector2(0, 0), Vector2(1280, 720), textures[4], d3d, true));
		sprites[4].scale = bgScale;
		sprites[4].sprRect.right *= 2;
		bgTimers.push_back(0);
		scrollSpeeds.push_back(200);


		//Make player texture
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Entities/birdneutralsprite.dds", nullptr, &textures[5], 0, &alpha) != S_OK)
			assert(false);

		sprites.push_back(Sprite::Sprite(Vector2(500, 500), Vector2(1280, 720), textures[5], d3d, true, true, 5, 10.0f, 5.0f));

		//Make enemy texture
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Entities/penguinplane_backwards.dds", nullptr, &textures[6], 0, &alpha) != S_OK)
			assert(false);

		sprites.push_back(Sprite::Sprite(Vector2(100, 100), Vector2(1280, 720), textures[6], d3d, true, true, 3, 10.0f, 3.5f));
	}


	//any memory or resources we made need releasing at the end
	void ReleaseGame()
	{
		ReleaseCOM(textures[0]);
		//ReleaseCOM(textures[1]);
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
		if (sprites[5].pos.y >= 0 && sprites[5].pos.y <= 570) {
			if (kb.W || kb.Up) {
				sprites[5].pos.y -= sprites[5].moveSpeed + dTime;
			}
			if (kb.S || kb.Down) {
				sprites[5].pos.y += sprites[5].moveSpeed + dTime;
			}
		}
		else if (sprites[5].pos.y <= 0){
			sprites[5].pos.y = 0;
		}
		else if (sprites[5].pos.y >= 550) {
			sprites[5].pos.y = 570;
		}
		

		if (sprites[5].pos.x >= 0 && sprites[5].pos.x <= 1100) {
			if (kb.A || kb.Left) {
				sprites[5].pos.x -= sprites[5].moveSpeed + dTime;
			}
			if (kb.D || kb.Right) {
				sprites[5].pos.x += sprites[5].moveSpeed + dTime;
			}
		}
		else if (sprites[5].pos.x <= 0) {
			sprites[5].pos.x = 0;
		}
		else if (sprites[5].pos.x >= 1100) {
			sprites[5].pos.x = 1100;
		}
		

		//auto mouse = m_mouse->GetState();



		
	}

	//called over and over, use it to render things
	void Render(float dTime, MyD3D& d3d)
	{
		WinUtil& wu = WinUtil::Get();
		

		d3d.BeginRender(Vector4(0, 0, 0, 0));

		//put sprites to render here
		if (sprites.empty() == false) {
			for (int i = 0; i < sprites.size(); i++) {
				sprites[i].Render();
			}
		}


		float bgWidth = sprites[1].texSize.x;

		//Scrolling background
		
		for (int i = 0; i < bgTimers.size(); i++) {
			bgTimers[i] += dTime;

			float scroll = bgTimers[i] * scrollSpeeds[i];

			if (sprites[i].pos.x <= -(bgWidth * bgScale)) {
				sprites[i].pos.x = 0;
				bgTimers[i] = 0;
			}
			else {
				sprites[i].pos.x = -scroll;
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
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Penguins gon cry", MainWndProc, true))
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