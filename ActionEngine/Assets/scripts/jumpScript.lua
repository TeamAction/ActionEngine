

function onStart()
	--playMusic("bgm1")
end

function onTick(dt)

	xVel, yVel = this:getVelocity()
	
	if(xVel > 0) then
		this:setFlip("",false)
	elseif (xVel < 0) then
		this:setFlip("",true)
	end
	
	if(math.abs(xVel) > 10 and this:isGrounded()) then
		this:setAnimation("","playerRun")
	else
		this:setAnimation("","playerIdle")
	end
	
	
	if yVel > 10 and not this:isGrounded()  then
		this:setAnimation("","playerJump")
		this:addImpulse(0,10)
	elseif not keyHeld(' ') and yVel < 0 then
		this:setAnimation("","playerJump")
		this:addImpulse(0,7)
	end

	
	if keyDown(' ') and this:isGrounded()then
		this:addImpulse(0,-200)
		playEffect("sfx1")
	end
	if keyHeld('D') then
		this:addImpulse(30,0)
	end
	if keyHeld('A') then
		this:addImpulse(-30,0)
	end
	x,y =this:getGlobalTransform()


	if x < 320 then
	 x = 320
	end
	if y > 240 then
	 y = 240
	end
	setCameraOffset(1,(-x+320),(-y+240))
	setCameraOffset(2,(-x+320),(-y+240))
	
end

function onHit(other)
	if other:checkForTag("enemy") then
		screenText(250,250,"DEATH" ,1)
		fireEvent(this,"death")
		fireEvent(this,"load")
	elseif other:checkForTag("goal") then
		fireEvent(this,"nextLevel")
	end
end


