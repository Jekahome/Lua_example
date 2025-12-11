

Install

```
sudo apt update
sudo apt install lua5.4 liblua5.4-dev
lua -v
    Lua 5.4.6  Copyright (C) 1994-2023 Lua.org, PUC-Rio

# Path lua libray
dpkg -L liblua5.4-dev | grep lua.h
    /usr/include/lua5.4/lua.h
    /usr/include/lua5.4/lua.hpp

команда GCC должна указывать путь к заголовкам через -I, иначе компилятор ищет их только в стандартных /usr/include

-I/usr/include/lua5.4

```

Настройка проекта .vscode/c_cpp_properties.json

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/lua5.4"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c99",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64",
            "browse": {
                "path": [
                    "/usr/include/lua5.4"
                ],
                "limitSymbolsToIncludedHeaders": true
            }
        }
    ],
    "version": 4
}
```

**Compiling:**

```
gcc -std=c99 -Wall -Wextra -Wformat -Werror -Wconversion -Wformat=2 -Wformat-security -fdiagnostics-color=always -fmessage-length=0 -Wformat-diag \
-I/usr/include/lua5.4 -O0 main.c -o my_program.out -llua5.4 -lm -ldl
```

Где:
* -I — для компилятора, путь к заголовочным файлам при include
   * -I/usr/include/lua5.4 → путь к Lua заголовкам (lua.h, lauxlib.h, lualib.h)
* -L — для линкера, бинарные библиотеки, путь к библиотекам (liblua.so, liblua.a). Нужно линкеру, чтобы он мог найти реализацию функций при сборке если они в нестандартном месте, например /usr/local/lib или /home/user/mylibs.
   * -L/usr/local/lib
* -llua — линковка с Lua
   * -llua5.4 → линковка с библиотекой Lua
* -lm -ldl → дополнительные зависимости Lua на Linux