#include "sprite.h"



using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//Sprite::Sprite(Vector2 globPos, ID3D11ShaderResourceView* textPointer, MyD3D& d3dToPass, bool alpha, bool isAnim, int sprAmount, float spd, float scl) {
//	pos = globPos;
//	pT = textPointer;
//	d3d = d3dToPass;
//	isAlpha = alpha;
//	isAnimated = isAnim;
//	spriteAmount = sprAmount;
//	animSpeed = spd;
//	scale = scl;
//
//	//Defaults not set by parameters
//	sprRect = RECT();
//	moveSpeed = 1.0f;
//	
//	pT->GetResource(&resource);
//	resource->QueryInterface<ID3D11Texture2D>(&text2D);
//
//	text2D->GetDesc(&desc);
//
//	sprRect.left = 0;
//	sprRect.top = 0;
//	sprRect.right = desc.Width;
//	sprRect.bottom = desc.Height;
//
//	texSize = Vector2(desc.Width, desc.Height);
//
//	spriteBatch = std::make_unique<SpriteBatch>(&d3d.GetDeviceCtx());
//
//	if (isAnimated) {
//		for (int i = 0; i < spriteAmount; i++) {
//			spriteRects.push_back(RECT());
//			spriteRects[i].left = i * (desc.Width / spriteAmount);
//			spriteRects[i].top = 0;
//			spriteRects[i].bottom = desc.Height;
//			spriteRects[i].right = (i + 1) * (desc.Width / spriteAmount);
//		}
//	}
//	
//}


Sprite::Sprite() {

	active = false;
}

void Sprite::createSprite(Vector2 globPos, ID3D11ShaderResourceView* textPointer, MyD3D& d3dToPass, bool alpha, float scl, bool isAnim, int sprAmount, float spd) {
	active = true;
	
	pos = globPos;
	pT = textPointer;
	d3d = d3dToPass;
	isAlpha = alpha;
	isAnimated = isAnim;
	spriteAmount = sprAmount;
	animSpeed = spd;
	scale = scl;

	//Defaults not set by parameters
	sprRect = RECT();
	moveSpeed = 1.0f;

	pT->GetResource(&resource);
	resource->QueryInterface<ID3D11Texture2D>(&text2D);

	text2D->GetDesc(&desc);

	sprRect.left = 0;
	sprRect.top = 0;
	sprRect.right = desc.Width;
	sprRect.bottom = desc.Height;

	texSize = Vector2(desc.Width, desc.Height);

	spriteBatch = std::make_unique<SpriteBatch>(&d3d.GetDeviceCtx());

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

void Sprite::Render() {
	if (active) {
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

			spriteBatch->Draw(pT, pos, &spriteRects[currentSprite], Colors::White, 0.0f, Vector2(0, 0), scale);
		}
		else {
			spriteBatch->Draw(pT, pos, &sprRect, Colors::White, 0.0f, Vector2(0, 0), scale);
		}



		spriteBatch->End();
	}
}

	