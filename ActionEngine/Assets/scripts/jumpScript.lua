
function onStart()

end

function onTick(dt)
	screenText(50,150,"Grounded: "..tostring(this:isGrounded()),0)
	if keyDown(' ') and this:isGrounded()then
		this:addImpulse(0,-200)
	end
	if keyHeld('D') then
		this:addImpulse(10,0)
	end
	if keyHeld('A') then
		this:addImpulse(-10,0)
	end
end


