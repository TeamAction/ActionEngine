
deaths = 0
timer = 0
level = 1
levels = {"level1Scene","level2Scene"}

finalDeaths = 0
finalTime = 0

hudActive = true

function onStart()
	this:setPreserveInTransition(true)
	bindEvent(this,"death","playerDeath")
	bindEvent(this,"load","loadLevel")
	bindEvent(this,"nextLevel","levelOver")
	bindEvent(this,"stats","displayStats")
end

function onTick(dt)
	if hudActive then
		timer = timer + dt
		screenText(50,10,string.format("Deaths %.0f", deaths),0)
		screenText(350,10,string.format("Time %.2f", timer),0)
	end
end

function playerDeath()
	deaths = deaths + 1
end

function levelOver()
	finalDeaths = deaths
	finalTime = timer
	deaths = 0
	timer = 0
	level = level + 1
	hudActive = false
	loadScene("levelStatsScene")
end

function loadLevel()
	hudActive = true
	if level > #levels then
		this:setPreserveInTransition(false)
		loadScene("menuScene")
	else
		loadScene(levels[level])
	end
end

function displayStats()
	screenText(150,150,string.format("Deaths: %.0f", finalDeaths),0)
	screenText(150,250,string.format("Time: %.2f", finalTime),0)
	screenText(150,450,"Press enter to continue",0)
end
