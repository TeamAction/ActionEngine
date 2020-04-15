--this file is no longer used and is loaded as a string literal in c++ to prevent user changes
scriptNamespace = {}

function fireFunction(functionName,...)
	return (scriptNamespace[this][functionName](...))
end


function luaLoader(path)
    scriptNamespace[this]=setmetatable({},{__index=_G})
    local chunk = loadfile(path,nil,scriptNamespace[this])
	chunk()
end

function destroyScript()
	unBindAll(this) 
	scriptNamespace[this] = nil
end