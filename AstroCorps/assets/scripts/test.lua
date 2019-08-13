global_component_list = {
	transform = setmetatable({}, {
		__call = function(self, x, y)
			local table = {}
			table.x = x
			table.y = y
			return table
		end
	})
}

a = global_component_list.transform(1, 3)
print(a.x)
print(a.y)

print()

b = global_component_list.transform(200, 52)
print(b.x)
print(b.y)

print()

print(a.x)
print(a.y)



--b = __call(b, 38, 40)


--component_list.Transform.constructor(component_list.Transform, 3, 2, 4, 1)
--print(component_list.Transform.y)
--print(component_list['Transform']['height'])

--[[constructor = local function get_25() 
			return 25 
		end]]