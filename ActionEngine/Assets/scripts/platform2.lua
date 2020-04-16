
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
	this:setLocalTransform(x+(30*dt*direction),y)
end

function onHit(other)
	if other:checkForTag("player") then
		x,y = other:getGlobalTransform()
		other:setLocalTransform(x+(30*dtHolder*direction),y)
		other:addImpulse(0,15)
	end
end
