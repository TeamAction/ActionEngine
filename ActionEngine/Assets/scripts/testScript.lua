timer  = 0

function onStart()
	screenText(200,300,"test script prints for 5 seconds on start",5)
	bindEvent(this,"test","boundEvent")
	bindEvent(this,"test2","otherBoundEvent")
end

function onTick(dt)
	timer =  timer + dt
	screenText(50,150,"test script prints time since start using local varaiables "..tonumber(string.format("%.3f", timer)),0)
	screenText(0,0,tonumber(string.format("%.4f", dt)),0)
	x,y = this:getTransform()
	this:setTransform(x+(50*dt),y+(50*dt))
	fireEvent(this,"test")
	fireEvent(this,"test2","working "," arbitrary params ",11)
end

function boundEvent()
	x,y = this:getTransform()
	screenText(math.floor(x),math.floor(y-10),tonumber(string.format("%.1f", x)) .. "," .. tonumber(string.format("%.1f", y)) ,0)
end

function otherBoundEvent(arb, arb2, arb3)
	screenText(10,200,"second event fired".. arb.. arb2.. arb3,0)
end

