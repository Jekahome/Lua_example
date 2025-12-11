-- однострочный
--[[
многострочный комментарии
]]

-- глобальные переменный (по умолчанию)
x = 10        -- число
x = "hello"   -- теперь строка

 
local a = 1 -- локальная
local b = 2
if a > b then
    print("a > b")
else
    print("a <= b")
end


-- Функции

function add(a, b)
    return a + b
end

local f = function(x) return x * 2 end

-- Цикл while
local i = 0
while i < 10 do
    i = i + 1
end

-- Цикл for
i = nil  -- удаляет значение переменной (эквивалент NULL)
i = 0
for i = 1, 10 do
    print(i)
end

--[[
Lua не имеет массивов и структур как в C — есть таблицы, которые могут быть:
- массивом
- словарём
- объектом
- чем угодно одновременно

Индексация начинается с 1
]]

t = {10, 20, 30}   -- массив
person = {name="Bob", age=20}   -- словарь
print(t[1]) -- 10

-- Строки — иммутабельные
local s = "hello"
print(#s)        -- длина строки
print(s .. " world") -- конкатенация