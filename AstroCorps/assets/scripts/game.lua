-- setup.lua

-- Every game has exactly one tilemap
local tile_map = nil

-- loads a new tile map
-- TODO: take in string of map file
local function load_map()
	DEBUG('Lua init called')

	tile_map = TileMap.new()
	tile_map:load_map('assets/maps/xmltest.xml')
	
	load_tile_map(tile_map)

	tile_map:toggle_borders()
end

-- global function to get the current tile map
function get_tile_map()
	return tile_map
end


--[[ change entity system to use index instead of key!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ]]

-- test function
local function test_entity_system()
	print()
	INFO('Testing entity system')
	add_entity(EntityCreator.Player.new('Emma', 1, 4))
	add_entity(EntityCreator.Player.new('Leo', 2, 1))
	get_entity(0):update()
	update_game()
	INFO('Testing Done!\n')
end


local started = false
function start_game()
	-- ensure that game is started only once
	if started then return end
	started = true

	INFO('Game has started')

	load_map()
	test_entity_system()
end

local function get_dirs()
	local W = Keyboard[KEY_W]
	local A = Keyboard[KEY_A]
	local S = Keyboard[KEY_S]
	local D = Keyboard[KEY_D]

	if A ~= D then
		if A then
			return WEST
		else
			return EAST
		end
	end

	if W ~= S then
		if W then
			return NORTH
		else
			return SOUTH
		end
	end

	return STATIONARY
end

local function update_player()
	get_entity(0).cpp_entity:set_movement(get_dirs())
end

-- updates everything that needs it
function update_game()
	-- get the number of current entities
	local max_index = get_number_of_entites() - 1

	update_player()

	-- update each entity
	for i = 0, max_index, 1 do
		--get_entity(i).cpp_entity:set_movement(1)
		get_entity(i):update()
	end
end