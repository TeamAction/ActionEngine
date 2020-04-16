
direction = 1
timer = 0
dtHolder = 0
function onStart()
end

function onTick(dt)
	dtHolder = dt
	timer = timer + dt
	if timer > 5.0 then
		direction = direction * -1
		timer =0
	end
	x,y = this:getGlobalTransform()
	this:setLocalTransform(x,y+(30*dt*direction))
end

function onHit(other)
	if other:checkForTag("player") then
		x,y = other:getGlobalTransform()
		other:setLocalTransform(x,y+(31*dtHolder*direction))
		if direction == -1 then
			other:addImpulse(0,14*direction*-1)
		end
	end
end
