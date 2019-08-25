-- player.lua

-- setup metatable for player
local PlayerMetatable = {
	update = function(self)
		--TRACE("Update called for '" .. self.cpp_entity:get_name() .. "'")
		--INFO('Player update called')
	end,
	entity_type = 'Player'
}

-- for object orientedness
PlayerMetatable.__index = PlayerMetatable

-- to make a new player 
local PlayerConstructor = {
	new = function(name, x, y)
		DEBUG('Created Player, Name: ' .. name .. ' X: ' .. x .. ' Y: ' .. y)
		
		-- create new player
		local player_en = setmetatable({}, PlayerMetatable)

		-- Add C++ entity reference
		player_en.cpp_entity = get_tile_map():new_entity(name, x, y, 1, 1)

		-- return it
		return player_en
	end
}

-- load constructor into global table
EntityCreator.Player = PlayerConstructor