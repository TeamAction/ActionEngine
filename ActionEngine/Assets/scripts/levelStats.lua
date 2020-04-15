
function onStart()
	setCameraOffset(1,0,0)
	setCameraOffset(2,0,0)
end

function onTick(dt)
	fireEvent(this,"stats")
	if keyDown(string.char(13)) then
		fireEvent(this,"load")
	end	
end

