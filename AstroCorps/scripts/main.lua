-- main.lua

local function init()
	-- fill
end

local function start() 
	INFO('Lua Started!')
	
	-- load keyboard file for input
	load_file('utils/keyboard.lua')

	-- load entity management system
	load_file('gameplay/entities/entity_manager.lua')

	-- load gameplay file
	load_file('gameplay/game_manager.lua')

	-- start game (from setup.lua)
	start_game()
end

start()