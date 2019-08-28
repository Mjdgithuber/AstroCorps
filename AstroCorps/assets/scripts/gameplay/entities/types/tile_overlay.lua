-- tile_overlay.lua

-- setup metatable for Overlay
local TileOverlayMetatable = {
	update = function(self)
		-- need to dim in and out
	end,
	entity_type = 'Tile Overlay'
}

-- for object orientedness
TileOverlayMetatable.__index = TileOverlayMetatable

-- to make a new overlay 
local TileOverlayConstructor = {
	new = function(overlay_texture_name, x, y)
		DEBUG('Created Tile Overlay, X: ' .. x .. ' Y: ' .. y .. ' with Texture \'' .. overlay_texture_name .. '\'')
		
		-- create new overlay
		local overlay_en = setmetatable({}, TileOverlayMetatable)

		-- Add C++ entity reference
		overlay_en.cpp_entity = get_tile_map():new_entity(TileOverlayMetatable.entity_type, x, y, 1, 1)
		overlay_en.cpp_entity:set_texture_sheet(1)

		-- return it
		return overlay_en
	end
}

-- load constructor into global table
EntityCreator.TileOverlay = TileOverlayConstructor