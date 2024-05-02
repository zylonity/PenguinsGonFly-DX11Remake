
score = 0
scoreMultiplier = 10

scoreText = {text = score, PosX = 230, PosY = 20, R = 1.0, G = 1.0, B = 1.0, A = 1.0, scale = 1.0}


-- Deals with updating the text on screen as well.
function updateScore (deltaTime)
	score = score + (scoreMultiplier * deltaTime)
	CDispatcher("changeTextLua", score)
end
