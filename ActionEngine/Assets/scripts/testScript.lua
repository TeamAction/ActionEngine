
timer = 0

function onStart()
	screenText(200,300,"test script prints for 5 seconds on start",5)
	bindEvent(this,"test","boundEvent")
	bindEvent(this,"test2","otherBoundEvent")
end

function onTick(dt)
	timer =  timer + dt
	screenText(0,0,(string.format("%.4f", dt)),0)
	screenText(50,150,"test script prints time since start using local varaiables "..string.format("%.3f",timer),0)
	x,y = this:getGlobalTransform()
	if keyHeld('W') then
		y = y+(-50*dt)
	end
	if keyHeld('A') then
		x = x+(-50*dt)
	end
	if keyHeld('S') then
		y = y+(50*dt)
	end
	if keyHeld('D') then
		x = x+(50*dt)
	end
	this:setGlobalTransform(x,y)
	
	if keyDown('P') then
		loadScene("../../../Assets/scenes/testScene_Physics.json")
	end


	fireEvent("test")
	fireEvent("test2","move ","with ","WASD")
end

function boundEvent()
	x,y = this:getGlobalTransform()
	x2,y2 = this:getLocalTransform()
	screenText(math.floor(x),math.floor(y-10),string.format("%.1f", x2) .. "," .. string.format("%.1f", y2) ,0)
end

function otherBoundEvent(arb, arb2, arb3)
	screenText(10,200,arb.. arb2.. arb3,0)
end

