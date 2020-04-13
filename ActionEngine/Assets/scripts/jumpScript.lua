
platform2 = nil
spawnTest = nil

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
		loadScene("testScene1")
	end
	
	x,y = platform2:getGlobalTransform()
	if keyHeld('W') then
		y = y+(-50*dt)
	end
	if keyHeld('S') then
		y = y+(50*dt)
	end
	if keyDown('V') then
		--platform2:destoryActor()
		--platform2 = nil
		this:setAnimation("spriteTest","water")
	end
	platform2:setGlobalTransform(x,y)
	
	if keyDown('T') then
		--if spawnTest == nil then
			x,y = this:getGlobalTransform()
			spawnTest = root:createActor("spawningTest")
			spawnTest:attachTransform()
			spawnTest:setLocalTransform(x+50,y+50)
			spawnTest:attachSprite(0,"water")
		--else
		--	spawnTest:destoryActor()
		--	spawnTest = nil
		--end
	end
	x,y =this:getGlobalTransform()
	setCameraOffset(0,(-x+320),(-y+240))


end

function onHit(other)
	if other:checkForTag("test") then
		screenText(250,250,"HIT TEST TAG" ,1)
	else
	screenText(250,250,"HIT" ,1)
	end
end


