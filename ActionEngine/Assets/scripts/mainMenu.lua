cursor = 0
menu = true


function onStart()
	playMusic("bgm1")
end

function onTick(dt)
	if menu then
		screenText(250,300,"Play",0)
		screenText(250,350,"About",0)
		if keyDown('W') then
			cursor = 0
		end
		if keyDown('S') then
			cursor = 1
		end
		
		if keyDown(string.char(13)) then
			if cursor == 0 then
				loadScene("level1Scene")
			else
				menu = false
			end
		end
		
		if cursor == 0 then
			screenText(220,300,">",0)
		else
			screenText(220,350,">",0)
		end
	else
		screenText(50,150,"Engine and Game Written By:",0)
		screenText(200,200,"Team Action",0)
		screenText(50,250,"github.com/TeamAction",0)
		screenText(50,300,"Ted Bissada, Adam White,",0)
		screenText(200,350,"Nicolas Plumb",0)
		screenText(50,450,"Press enter to return to menu",0)
		if keyDown(string.char(13)) then
			menu = true
		end	
	end
end

