
platform2 = nil

function onStart()
	platform2 = getActorByName("platform2")
end

function onTick(dt)
	screenText(50,150,"Grounded: "..tostring(this:isGrounded()),0)
	xVel, yVel = this:getVelocity()
	screenText(50,250,string.format("%.1f", xVel) .. "," .. string.format("%.1f", yVel) ,0)

	if yVel > 10 and not this:isGrounded()  then
		this:addImpulse(0,10)
	elseif not keyHeld(' ') and yVel < 0 then
		this:addImpulse(0,7)
	end

	
	if keyDown(' ') and this:isGrounded()then
		this:addImpulse(0,-200)
	end
	if keyHeld('D') then
		this:addImpulse(30,0)
	end
	if keyHeld('A') then
		this:addImpulse(-30,0)
	end
	if keyDown('P') then
		loadScene("../../../Assets/scenes/testScene.json")
	end
	
	x,y = platform2:getGlobalTransform()
	if keyHeld('W') then
		y = y+(-50*dt)
	end
	if keyHeld('S') then
		y = y+(50*dt)
	end
	platform2:setGlobalTransform(x,y)


end


