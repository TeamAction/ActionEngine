
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
	scriptNamespace[this] = nil
end