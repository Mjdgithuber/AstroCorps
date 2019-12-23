-- game_manager.lua

-- global GameManager table to access public methods
GameManager = {
	start_game = nil,
	update_game = nil,
	get_tile_map = nil
}

-- forward declare local methods
local load_map
local test_entity_system
local get_dirs
local update_player

-- function to start the game
local started = false
GameManager.start_game = function()
	-- ensure that game is started only once
	if started then return end
	started = true
	
	INFO('Game has started')

	-- JUST FOR TESTING REMOVE LATER
	load_map()
	test_entity_system()
end


-- Every game has exactly one tilemap
local tile_map = nil

-- loads a new tile map
-- TODO: take in string of map file
load_map = function()
	DEBUG('Lua init called')

	tile_map = TileMap.new()
	tile_map:load_map('assets/maps/xmltest.xml')
	
	load_tile_map(tile_map)

	tile_map:toggle_borders()
end

-- global function to get the current tile map
GameManager.get_tile_map = function()
	return tile_map
end


--[[ change entity system to use index instead of key!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ]]

-- updates everything that needs it
GameManager.update_game = function()
	-- get the number of current entities
	local max_index = get_number_of_entites() - 1

	update_player()

	-- update each entity
	for i = 0, max_index, 1 do
		--get_entity(i).cpp_entity:set_movement(1)
		get_entity(i):update()
	end
end

GameManager.on_click = function(type)
	if type == LEFT_MOUSE_BUTTON then 
		INFO('LEFT clicked')
	else
		INFO('Right Clicked')
	end

	INFO('Emma: ' .. type)
end

-- test function
test_entity_system = function()
	print()
	INFO('Testing entity system')
	add_entity(EntityCreator.Player.new('Emma', 1, 4))
	add_entity(EntityCreator.Player.new('Leo', 2, 1))
	add_entity(EntityCreator.TileOverlay.new('Is a texture', 0, 0))
	get_entity(0):update()
	GameManager.update_game()
	INFO('Testing Done!\n')
end

update_player = function()
	get_entity(0).cpp_entity:set_movement(Keyboard.get_dirs())
end

