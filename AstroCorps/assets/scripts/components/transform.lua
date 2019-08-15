-- transform.lua

-- transform component
local transform_metatable = {
	update = function(self)
		return 'emma'
	end,
	name = 'Transform'
}

transform_metatable.__index = transform_metatable


-- global transform entry
GlobalComponentList.Transform = setmetatable({}, {
	__call = function(self, parser)
		--[[at this point the correct element should
			already be cached]]
		local tc = setmetatable({}, transform_metatable)

		-- parse all transform attributes
		tc.x = parser:int_attribute('x')
		tc.y = parser:int_attribute('y')
		tc.width = parser:int_attribute('width')
		tc.height = parser:int_attribute('height')

		return tc
	end
})