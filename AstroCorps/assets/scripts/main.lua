-- main.lua

local function init()
	-- fill
end

local function start() 
	INFO('Lua Started!')
	
	-- load keyboard file for input
	load_file('utils/keyboard.lua')

	-- load direction to act as enum
	load_file('utils/directions.lua')

	-- load entity management system
	load_file('entities/entity_manager.lua')

	-- load gameplay file
	load_file('game.lua')

	-- start game (from setup.lua)
	start_game()
end

start()