-- keyboard.lua

Keyboard = {
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	update_keyboard = nil,
	get_dirs = nil
}

KEY_A = 1
KEY_B = 2
KEY_C = 3
KEY_D = 4
KEY_E = 5
KEY_F = 6
KEY_G = 7
KEY_H = 8
KEY_I = 9
KEY_J = 10
KEY_K = 11
KEY_L = 12
KEY_M = 13
KEY_N = 14
KEY_O = 15
KEY_P = 16
KEY_Q = 17
KEY_R = 18
KEY_S = 19
KEY_T = 20
KEY_U = 21
KEY_V = 22
KEY_W = 23
KEY_X = 24
KEY_Y = 25
KEY_Z = 26
UPDATED = 27

--[[ Have bool for free vs turn based movement ]]

-- will update keyboard table if needed
Keyboard.update_keyboard = function(key, pressed)
	-- get last keyboard state
	local prev_val = Keyboard[_G['KEY_' .. key]]

	if prev_val == nil then return end

	-- check if it changed
	if pressed ~= prev_val then
		-- set the current key state to the new state
		Keyboard[_G['KEY_' .. key]] = pressed

		-- let keyboard know it has been updated
		Keyboard[UPDATED] = true
	end
end

Keyboard.get_dirs = function()
	-- get key states for WASD keys
	local W = Keyboard[KEY_W]
	local A = Keyboard[KEY_A]
	local S = Keyboard[KEY_S]
	local D = Keyboard[KEY_D]

	-- A xor D
	if A ~= D then
		if A then
			return WEST
		else
			return EAST
		end
	end

	-- W xor S
	if W ~= S then
		if W then
			return NORTH
		else
			return SOUTH
		end
	end

	-- if no movement return STATIONARY
	return STATIONARY
end