#include "GameObject.h"


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

GameObject::GameObject(MyD3D& d3dToPass, Vector2 pos) {
	d3d = d3dToPass;
	position = pos;

	isActive = false;
}

void GameObject::CreateSprite(wstring textureLocation, bool isAlpha, float scale) {

	const wchar_t* texLoc = textureLocation.c_str();

	if (CreateDDSTextureFromFile(&(d3d.GetDevice()), texLoc, nullptr, &texture, 0, &alpha) != S_OK)
		assert(false);

	sprite.createSprite(position, texture, d3d, isAlpha, scale);

	isActive = true;

}

void GameObject::CreateAnimatedSprite(wstring textureLocation, bool isAlpha, bool isAnim, int sprAmount, float animSpeed, float scale) {

	const wchar_t* texLoc = textureLocation.c_str();

	if (CreateDDSTextureFromFile(&(d3d.GetDevice()), texLoc, nullptr, &texture, 0, &alpha) != S_OK)
		assert(false);

	sprite.createSprite(position, texture, d3d, isAlpha, scale, isAnim, sprAmount, animSpeed);

}


void GameObject::Update() {
	sprite.pos = position;

}

void GameObject::Render() {
	sprite.Render();

}
