local WINDOW_WIDTH  = 800
local WINDOW_HEIGHT = 600

local x, y   = 1, 1
local dx, dy = 50, 50

function update()
    x = x + dx
    y = y + dy

    -- set_player_pos(x, y)
    print("CALLED")
end

function render()

end