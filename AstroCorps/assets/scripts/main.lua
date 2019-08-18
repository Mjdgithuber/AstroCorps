-- main.lua

local function start() 
	INFO('Lua Started!')

	-- load entity management system
	load_file('entities/entity_manager.lua')

	-- load gameplay file
	load_file('game.lua')

	-- start game (from setup.lua)
	start_game()
end

start()