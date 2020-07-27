--[[
NOTE: The fact that certain actions can trigger scripted events doesn't necessarily mean
they should; stat mods, buffs and debuffs can be specified in the JSON descriptor.
]]--

-- Base Item
Item = {}

function Item:onPickup(player)
	-- Called when the item is added to a player's inventory.
end

function Item:onActivate(player)
	-- Called when the item is activated by a player from their inventory.
end

function Item:onDrop(player)
	-- Called when the item is removed from a player's inventory.
end

-- Weapon
Weapon = {}

function Weapon:onEquip(player)
	-- Called when the weapon is equipped.
end

-- Armor
Armor = {}

function Armor:onEquip(player)
	-- Called when the weapon is equipped.
end