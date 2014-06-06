-- TODO should specify actions!
-- only temporary for now
objects = {
    bed = {
        sprite = "bed.png",
        cost = 20,

        -- Something like these?
        -- build_action = increase_worker_cap(1),
        -- remove_action = decrease_worker_cap(1),
        -- increase_worker_exhaustion = 5,
    },
}

--print('calling display')
a,b = call_c(12, 3.23, 'pew')
print('a: ' .. a .. ' b: ' .. b)

-- Ability to call c functions with
-- c.fun(...)
local c = setmetatable({}, {
    __index = function (t, k)
        return function (...)
            -- call_c will lookup key k for registered callbacks
            return call_c(k, unpack(arg));
        end
    end,
})

a,b = c.hello(1, 2, 3)
print(a, b)

