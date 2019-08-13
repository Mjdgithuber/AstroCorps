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

print('Alright We is Good!\n')

main_parser = Parser.new('Main Lua Parser')
result = main_parser:open_document('assets/entities/luasTest.xml')
result = main_parser:open_document('assets/entities/luasTest.xml')

if (result) then
	print('true')
else
	print('false')
end

print("\nDone")