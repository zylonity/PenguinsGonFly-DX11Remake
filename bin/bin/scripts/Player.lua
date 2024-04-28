local TextureLoader = require("bin.scripts.TextureLoader")

playerPos = {x = TextureLoader.player.PosX, y = TextureLoader.player.PosY}

moveSpeed = 650;

function movePlayer (up, down, left, right, deltaTime)

	if playerPos.y >= 0 and playerPos.y <= 570 then
		if up then
			playerPos.y = playerPos.y - (moveSpeed * deltaTime)
		end
		if down then
			playerPos.y = playerPos.y + (moveSpeed * deltaTime)
		end
	end

	if playerPos.x >= 0 and playerPos.x <= 1100 then
		if left then
			playerPos.x = playerPos.x - (moveSpeed * deltaTime)
		end
		if right then
			playerPos.x = playerPos.x + (moveSpeed * deltaTime)
		end
	end

	if playerPos.x <= 0 then
			playerPos.x = 0
	end
	if playerPos.x >= 1100 then
			playerPos.x = 1100
	end
	if playerPos.y <= 0 then
			playerPos.y = 0
	end
	if playerPos.y >= 570 then
			playerPos.y = 570
	end

	return playerPos.x, playerPos.y;
end

function ResetPlayer()
	playerPos.x = TextureLoader.player.PosX
	playerPos.y = TextureLoader.player.PosY
end