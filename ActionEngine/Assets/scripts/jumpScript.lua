
function onStart()

end

function onTick(dt)
	screenText(50,150,"Grounded: "..tostring(this:isGrounded()),0)
	if keyDown(' ') and this:isGrounded()then
		this:addImpulse(0,-200)
	end
end


