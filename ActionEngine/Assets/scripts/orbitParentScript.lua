
oribtDistance = 200
timer = 0

function onStart()
	bindEvent(this,"test","boundEvent")
end

function onTick(dt)
	timer =  timer + dt
	this:setLocalTransform((oribtDistance*math.cos(timer)),(oribtDistance*math.sin(timer)))
end

function boundEvent()
	x,y = this:getGlobalTransform()
	x2,y2 = this:getLocalTransform()
	screenText(math.floor(x),math.floor(y-10),string.format("%.1f", x2) .. "," .. string.format("%.1f", y2) ,0)
end

