-- it should be invalid
local pl = luambda.player.find_by_index(1)
print(pl:is_valid())

-- a hook example
luambda.register_hook("client_connect", function(player, name, ip)
    player:print_console(string.format("Player %s is connecting from %s.", name, ip))
    print("[LUA] Player " .. name .. " is connecting from " .. ip .. ".")
end)
