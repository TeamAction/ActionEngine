
test = 0
timer = 0

function onStart()

	x,y = this:getTransform()
	screenText(math.floor(x+200),math.floor(y+300),"test script prints for 5 seconds on start",5)
	bindEvent(this,"test","boundEvent")
	bindEvent(this,"test2","otherBoundEvent")
	test = test + 1
end

function onTick(dt)
	timer =  timer + dt
	screenText(0,0,(string.format("%.4f", dt)),0)
	screenText(50,150,"test script prints time since start using local varaiables "..string.format("%.3f",timer),0)
	if keyHeld(' ') then
		x,y = this:getTransform()
		this:setTransform((x+(50*dt)),(y+(50*dt)))
	end
	if keyDown('R') then
		this:setTransform(0,0)
	end
	fireEvent(this,"test")
	fireEvent(this,"test2","press "," space to move ",test)
end

function boundEvent()
	x,y = this:getTransform()
	screenText(math.floor(x),math.floor(y-10),string.format("%.1f", x) .. "," .. string.format("%.1f", y) ,0)
end

function otherBoundEvent(arb, arb2, arb3)
	screenText(10,200,arb.. arb2.. arb3,0)
end

