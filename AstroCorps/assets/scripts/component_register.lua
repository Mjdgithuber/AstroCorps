-- component_register.lua

GlobalComponentList = {}

local ComponentListMetatable = {
	__index = function(table, key) 
		print("The key '" .. key .. "' doesn't exist in the GlobalComponentList Table")
	end
}

setmetatable(GlobalComponentList, ComponentListMetatable)


--register all components
local dir = Directory.new('assets/scripts/components')

-- get the number of components
local size = dir:number_of_files()


for i = 0, size-1 do
	load_file('components/' .. dir:get_filename(i))
end

print(GlobalComponentList.Transform)



--[[local main_parser = Parser.new('Main Lua Parser')
result = main_parser:open_document('assets/entities/luasTest.xml')
print('opened file:')
print(result)

result = main_parser:cache_root_element('Entity')
print('Found entity: ')
print(result)
print()

result = main_parser:string_attribute('name')
print('Name: ' .. result)

result = main_parser:cache_element('Components')
print('\nfound components')
print(result)

result = main_parser:cache_child_element('Component')
print('\nfound child Component')
print(result)

some_table = GlobalComponentList.Transform(main_parser)
print(some_table.name)]]