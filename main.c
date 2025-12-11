#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void lua_config_present();

int main() {
    lua_State *L = luaL_newstate();   // создаём Lua-состояние
    luaL_openlibs(L);                 // подключаем стандартные библиотеки Lua

    if (luaL_dofile(L, "script.lua") != LUA_OK) { // выполняем скрипт Lua
        printf("Error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L); // закрываем Lua
    //-------------------------------------------------------------------------

    lua_config_present();

    return 0;
}

/*
Скрипты и конфиги на Lua можно менять на лету, и программа на C будет реагировать
на изменения без перекомпиляции

C-программа читает Lua-конфиг, использует его значения, и потом можно просто поменять 
Lua-файл — программа снова прочтёт новые значения.
*/
void lua_config_present(){

    lua_State *L = luaL_newstate();    // создаём Lua-состояние
    luaL_openlibs(L);                  // подключаем стандартные библиотеки

    // Загружаем Lua-файл
    if (luaL_dofile(L, "config.lua") != LUA_OK) {
        printf("Error loading config: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return;
    }

    // Достаем таблицу config
    lua_getglobal(L, "config"); // помещаем в стек
    if (!lua_istable(L, -1)) {
        printf("config is not a table!\n");
        lua_close(L);
        return;
    }

    // Достаем window.width
    lua_getfield(L, -1, "window"); // config.window
    lua_getfield(L, -1, "width");  // config.window.width
    int width = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);

    // Достаем window.height
    lua_getfield(L, -1, "height");
    int height = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);

    // Достаем fullscreen
    lua_getfield(L, -1, "fullscreen");
    int fullscreen = lua_toboolean(L, -1);
    lua_pop(L, 2); // pop window и fullscreen

    printf("Window: %dx%d, fullscreen: %s\n",
           width, height, fullscreen ? "yes" : "no");

    // Вызов функции window_area()
    lua_getglobal(L, "window_area");
    if (lua_isfunction(L, -1)) {
        if (lua_pcall(L, 0, 1, 0) == LUA_OK) {
            int area = (int)lua_tointeger(L, -1);
            printf("Window area: %d\n", area);
            lua_pop(L, 1);
        } else {
            printf("Error calling window_area(): %s\n", lua_tostring(L, -1));
        }
    }

    lua_close(L);

}