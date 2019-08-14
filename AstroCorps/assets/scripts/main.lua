GlobalComponentList = {
	Transform = setmetatable({}, {
		__call = function(self, parser, x, y)
			local transform_table = {}
			transform_table.x = x
			transform_table.y = y
			return transform_table
		end
	})
}

local function print_res(bool) if (bool) then print('true') else print('false') end end

print('Alright We is Good!\n')

main_parser = Parser.new('Main Lua Parser')
result = main_parser:open_document('assets/entities/luasTest.xml')

print('opened file:')
print_res(result)

result = main_parser:cache_element('Components')
print('\nfound components')
print(result)

result = main_parser:cache_child_element()
print('\nfound child')
print(result)

result = main_parser:int_attribute('y')
print('result: ' .. result)

result = main_parser:string_attribute('name')
print('\nname result: ' .. result)

print('\n' .. [[Who doesn't love some good lua]])

print("\nDone")