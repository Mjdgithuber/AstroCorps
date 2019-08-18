-- old_main.lua

local function init()
	load_file('component_register.lua')
end

print('Femma;a')

--init()

player = Entity.new(-71, 5, 2, 9, 'player')
print()
info('X: ' .. player:get_x() .. ' Y: ' .. player:get_y())


--[[info('Testing print')
local x = 65
local y = 'emma'
error('Testing concat ' .. y .. " " .. '' .. x)
trace('Trace')
debug('debug')]]

--[[local dir = Directory.new()--'assets/scripts'
dir:open_dir("assets/scripts/")
--dir:print_files()
local size = dir:number_of_files()
for i = 0, size-1 do
	print(dir:get_filename(i))
end]]

