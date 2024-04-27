#include "sprite.h"



using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Sprite::Sprite(){
}

void Sprite::createSprite(MyD3D& d3dToPass, wstring textureLocation, Vector2 globPos, bool isAalpha, float scl, bool isAnim, int sprAmount, float spd) {
	pos = globPos;
	d3d = d3dToPass;
	isAlpha = isAalpha;
	isAnimated = isAnim;
	spriteAmount = sprAmount;
	animSpeed = spd;
	scale = scl;

	isVisible = true;

	const wchar_t* texLoc = textureLocation.c_str();

	if (CreateDDSTextureFromFile(&(d3d.GetDevice()), texLoc, nullptr, &texture, 0, &alpha) != S_OK)
		assert(false);

	//Defaults not set by parameters
	sprRect = RECT();

	texture->GetResource(&resource);
	resource->QueryInterface<ID3D11Texture2D>(&text2D);

	text2D->GetDesc(&desc);

	sprRect.left = 0;
	sprRect.top = 0;
	sprRect.right = desc.Width;
	sprRect.bottom = desc.Height;

	texSize = Vector2(desc.Width, desc.Height);

	spriteBatch = std::make_unique<SpriteBatch>(&d3d.GetDeviceCtx());


	//Divide the sprite into rects if animated
	if (isAnimated) {

		for (int i = 0; i < spriteAmount; i++) {
			spriteRects.push_back(RECT());
			spriteRects[i].left = i * (desc.Width / spriteAmount);
			spriteRects[i].top = 0;
			spriteRects[i].bottom = desc.Height;
			spriteRects[i].right = (i + 1) * (desc.Width / spriteAmount);
		}
	}

}

void Sprite::createSprite(MyD3D& d3dToPass, string strTextureLocation, Vector2 globPos, bool isAalpha, float scl, bool isAnim, int sprAmount, float spd) {
	pos = globPos;
	d3d = d3dToPass;
	isAlpha = isAalpha;
	isAnimated = isAnim;
	spriteAmount = sprAmount;
	animSpeed = spd;
	scale = scl;

	isVisible = true;

	wstring widestr;
	for (int i = 0; i < strTextureLocation.length(); ++i)
		widestr += wchar_t(strTextureLocation[i]);

	const wchar_t* texLoc = widestr.c_str();

	if (CreateDDSTextureFromFile(&(d3d.GetDevice()), texLoc, nullptr, &texture, 0, &alpha) != S_OK)
		assert(false);

	//Defaults not set by parameters
	sprRect = RECT();

	texture->GetResource(&resource);
	resource->QueryInterface<ID3D11Texture2D>(&text2D);

	text2D->GetDesc(&desc);

	sprRect.left = 0;
	sprRect.top = 0;
	sprRect.right = desc.Width;
	sprRect.bottom = desc.Height;

	texSize = Vector2(desc.Width, desc.Height);

	spriteBatch = std::make_unique<SpriteBatch>(&d3d.GetDeviceCtx());


	//Divide the sprite into rects if animated
	if (isAnimated) {

		for (int i = 0; i < spriteAmount; i++) {
			spriteRects.push_back(RECT());
			spriteRects[i].left = i * (desc.Width / spriteAmount);
			spriteRects[i].top = 0;
			spriteRects[i].bottom = desc.Height;
			spriteRects[i].right = (i + 1) * (desc.Width / spriteAmount);
		}
	}

}

void Sprite::createSpriteFromLua(MyD3D& d3dToPass, SpriteDetails luaTextureDetails) {

	strTextureLocation = luaTextureDetails.TexLoc;
	pos = Vector2(luaTextureDetails.PosX, luaTextureDetails.PosY);
	d3d = d3dToPass;
	isAlpha = luaTextureDetails.isAlpha;
	isAnimated = luaTextureDetails.isAnim;
	spriteAmount = luaTextureDetails.spriteAmount;
	animSpeed = luaTextureDetails.animSpeed;
	scale = luaTextureDetails.scale;

	isVisible = true;

	wstring widestr;
	for (int i = 0; i < strTextureLocation.length(); ++i)
		widestr += wchar_t(strTextureLocation[i]);

	const wchar_t* texLoc = widestr.c_str();

	if (CreateDDSTextureFromFile(&(d3d.GetDevice()), texLoc, nullptr, &texture, 0, &alpha) != S_OK)
		assert(false);

	//Defaults not set by parameters
	sprRect = RECT();

	texture->GetResource(&resource);
	resource->QueryInterface<ID3D11Texture2D>(&text2D);

	text2D->GetDesc(&desc);

	sprRect.left = 0;
	sprRect.top = 0;
	sprRect.right = desc.Width;
	sprRect.bottom = desc.Height;

	texSize = Vector2(desc.Width, desc.Height);

	spriteBatch = std::make_unique<SpriteBatch>(&d3d.GetDeviceCtx());


	//Divide the sprite into rects if animated
	if (isAnimated) {

		for (int i = 0; i < spriteAmount; i++) {
			spriteRects.push_back(RECT());
			spriteRects[i].left = i * (desc.Width / spriteAmount);
			spriteRects[i].top = 0;
			spriteRects[i].bottom = desc.Height;
			spriteRects[i].right = (i + 1) * (desc.Width / spriteAmount);
		}
	}

}

void Sprite::RenderSprite() {
	if (isVisible) {
		if (isAlpha == true) {
			//Gets device states, makes it transparent and makes the upscaling point clamp so it doesnt blur
			CommonStates dxstate(&d3d.GetDevice());
			spriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), dxstate.PointWrap());
		}
		else {
			spriteBatch->Begin();
		}

		if (isAnimated) {
			float currentTime = GetClock();
			int currentSprite = (int)(currentTime * animSpeed) % spriteAmount;

			spriteBatch->Draw(texture, pos, &spriteRects[currentSprite], Colors::White, 0.0f, Vector2(0, 0), scale);
		}
		else {
			spriteBatch->Draw(texture, pos, &sprRect, Colors::White, 0.0f, Vector2(0, 0), scale);
		}



		spriteBatch->End();
	}
	
}




void Sprite::setTexRect(RECT rectToPass) {
	sprRect = rectToPass;
}

void Sprite::setTexture(wstring textureLocation) {
	if (CreateDDSTextureFromFile(&(d3d.GetDevice()), textureLocation.c_str(), nullptr, &texture, 0, &alpha) != S_OK)
		assert(false);
}