require 'TextureLoader.lua'

playerPos = {x = TextureLoader.player.posX, y = TextureLoader.player.posY}

moveSpeed = 1.0;

function movePlayer (deltaTime)

	playerPos.y += moveSpeed * deltaTime;
	return playerPos;
end