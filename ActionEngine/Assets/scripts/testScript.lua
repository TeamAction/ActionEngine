
timer = 0
otherActor = nil


function onStart()

	--this:setPreserveInTransition(true)
	screenText(200,300,"test script prints for 5 seconds on start",5)
	bindEvent(this,"test","boundEvent")
	bindEvent(this,"test2","otherBoundEvent")
	otherActor = getActorByName("Actor2")
end

function onTick(dt)
	timer =  timer + dt
	screenText(0,0,(string.format("%.4f", dt)),0)
	screenText(50,150,"test script prints time since start using local varaiables "..string.format("%.3f",timer),0)
	x,y = this:getGlobalTransform()
	if keyHeld('w') then
		y = y+(-50*dt)
	end
	if keyHeld('a') then
		x = x+(-50*dt)
	end
	if keyHeld('S') then
		y = y+(50*dt)
	end
	if keyHeld('D') then
		x = x+(50*dt)
	end
	this:setGlobalTransform(x,y)
	
	if keyDown('p') then
		loadScene("testScene2")
	end

	screenText(300,350,tostring(scriptNamespace[otherActor].oribtDistance),0)
	if keyHeld(' ') then
		scriptNamespace[otherActor].oribtDistance = scriptNamespace[otherActor].oribtDistance+(50*dt)
	end

	
	fireEvent(this,"test")
	fireEvent(this,"test2","move ","with ","WASD")
	
	this:setGlobalTransform(x,y)

end

function boundEvent()
	x,y = this:getGlobalTransform()
	x2,y2 = this:getLocalTransform()
	screenText(math.floor(x),math.floor(y-10),string.format("%.1f", x2) .. "," .. string.format("%.1f", y2) ,0)
end

function otherBoundEvent(arb, arb2, arb3)
	screenText(10,200,arb.. arb2.. arb3,0)
end

