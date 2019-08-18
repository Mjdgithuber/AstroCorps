-- entity_manager.lua

--[[ Entites holds each created entity and is
     local to promote encapsulation getters
	 and setters are provided below ]]
local Entities = {}
local entity_count = 0

-- return entity_count
function get_number_of_entites()
	return entity_count
end

-- add an entity to the table
function add_entity(entity)
	-- add entity to entities table
	Entities[entity_count] = entity

	-- increment entity_count
	entity_count = entity_count + 1
end

-- returns an entity at the given index
function get_entity(entity_number)
	return Entities[entity_number]
end

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

--[[ Entity creator holds info on how to make
     entites of every type ]]
EntityCreator = {}

-- setup metatable
local metatable = {
	__index = function(table, key) 
		print("The entity '" .. key .. "' doesn't exist!")
	end
}
setmetatable(EntityCreator, metatable)

-- add each type to EntityCreator
local function load_entites()
	-- get types dir
	local dir = Directory.new('assets/scripts/entities/types')

	-- get the number of entity types
	local size = dir:number_of_files()

	-- load every entity type from types dir
	for i = 0, size-1 do
		load_file('entities/types/' .. dir:get_filename(i))
	end
end

load_entites()