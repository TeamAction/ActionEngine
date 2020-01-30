
currentScope = nil
scriptNamespace = {}

function fireFunction(functionName,...)
	return (scriptNamespace[currentScope][functionName](...))
end


function luaLoader(path,scopeName)
    scriptNamespace[scopeName]=setmetatable({},{__index=_G})
    local chunk = loadfile(path,nil,scriptNamespace[scopeName])
	chunk()
end
