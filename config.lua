-- Конфигурационный Lua-файл
config = {
    window = {
        width = 800,
        height = 600,
        fullscreen = false
    },
    player = {
        name = "Alice",
        lives = 3
    }
}

-- Можно добавить вычисляемое значение
function window_area()
    return config.window.width * config.window.height
end
