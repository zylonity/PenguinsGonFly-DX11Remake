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


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


const int ASCII_ESC = 27;


//Normal sprite class, just displays image
class Sprite {
private:
	Vector2 winSize = Vector2(1280, 720);
	
protected:
	Vector2 pos;
	ID3D11ShaderResourceView* pT = nullptr;
	MyD3D d3d;
	bool isAlpha;


	ID3D11Resource* resource;
	ID3D11Texture2D* text2D;
	D3D11_TEXTURE2D_DESC desc;

public:
	bool scaleHeightToWindow = false;
	bool scaleWidthToWindow = false;
	
	RECT sprRect = RECT();
	
	float scale = 1.0f;
	
	Sprite(Vector2 globPos, ID3D11ShaderResourceView* textPointer, MyD3D& d3dToPass, bool alpha = false) {
		pos = globPos;
		pT = textPointer;
		d3d = d3dToPass;
		isAlpha = alpha;
		
		pT->GetResource(&resource);
		resource->QueryInterface<ID3D11Texture2D>(&text2D);

		text2D->GetDesc(&desc);
		
		sprRect.left = 0;
		sprRect.top = 0;
		sprRect.right = desc.Width;
		sprRect.bottom = desc.Height;
	}

	void Render() {
		//Grabs the Texture2D and grabs the description for the resolution
		
		if (scaleHeightToWindow) {
			scale = winSize.y / desc.Height;
		}

		if (scaleWidthToWindow) {
			scale = winSize.x / desc.Width;
		}
		
		std::unique_ptr<SpriteBatch> spriteBatch;
		spriteBatch = std::make_unique<SpriteBatch>(&d3d.GetDeviceCtx());

		if (isAlpha == true) {
			CommonStates dxstate(&d3d.GetDevice());
			spriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), dxstate.PointClamp());
		}
		else {
			spriteBatch->Begin();
		}
		
		


		spriteBatch->Draw(pT, pos, &sprRect, Colors::White, 0.0f, Vector2(0, 0), scale);

		spriteBatch->End();

	}

};


//Animated sprite class
class AnimSprite : public Sprite {
	int spriteAmount;
	//Makes an array of each sprite in the image
	vector<RECT> spriteRects;
	
public:
	float speed = 10.0f;
	
	AnimSprite(Vector2 globPos, int sprAmount, ID3D11ShaderResourceView* textPointer, MyD3D& d3dToPass, bool alpha = false) : Sprite(globPos, textPointer, d3dToPass){
		pos = globPos;
		spriteAmount = sprAmount;
		pT = textPointer;
		d3d = d3dToPass;
		isAlpha = alpha;
	}
	
	void Render() {



		//Adds each image to the array
		for (int i = 0; i < spriteAmount; i++) {
			spriteRects.push_back(RECT());
			spriteRects[i].left = i * (desc.Width / spriteAmount);
			spriteRects[i].top = 0;
			spriteRects[i].bottom = desc.Height;
			spriteRects[i].right = (i + 1) * (desc.Width / spriteAmount);
		}
		
		std::unique_ptr<SpriteBatch> spriteBatch;
		spriteBatch = std::make_unique<SpriteBatch>(&d3d.GetDeviceCtx());



		
		if (isAlpha == true) {
			//Gets device states, makes it transparent and makes the upscaling point clamp so it doesnt blur
			CommonStates dxstate(&d3d.GetDevice());
			spriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), dxstate.PointClamp());
		}
		else {
			spriteBatch->Begin();
		}


		float currentTime = GetClock();
		int currentSprite = (int)(currentTime * speed) % spriteAmount;

		spriteBatch->Draw(pT, pos, &spriteRects[currentSprite], Colors::White, 0.0f, Vector2(0, 0), scale);

		spriteBatch->End();

	}

};

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

	ID3D11ShaderResourceView* textures[2];

	vector<Sprite> sprites;
	vector<AnimSprite> animSprites;

public:
	Game(MyD3D& d3d)
	{
		DDS_ALPHA_MODE alpha;

		//Make background texture
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Background/sky.dds", nullptr, &textures[1], 0, &alpha) != S_OK)
			assert(false);
		
		sprites.push_back(Sprite::Sprite(Vector2(0, 0), textures[1], d3d, false));
		sprites[0].scaleHeightToWindow = true;

		//Make player texture
		if (CreateDDSTextureFromFile(&(d3d.GetDevice()), L"bin/data/Entities/birdneutralsprite.dds", nullptr, &textures[0], 0, &alpha) != S_OK)
			assert(false);

		assert(textures[0]);

		animSprites.push_back(AnimSprite::AnimSprite(Vector2(500,500), 5, textures[0], d3d, true));
		animSprites[0].scale = 4.0f;
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
		
		if (animSprites.empty() == false) {
			for (int i = 0; i < animSprites.size(); i++) {
				animSprites[i].Render();
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
	case WM_CHAR:
		switch (wParam)
		{
		case ASCII_ESC:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;

			
		}
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