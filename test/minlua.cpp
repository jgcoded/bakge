
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

/* *
 * Simple program to print Hello, world from Lua
 * */

int main(int argc, char* argv[])
{
    lua_State* L;

    /* Create and setup Lua state */
    L = luaL_newstate();
    luaL_openlibs(L);

    /* Say hello! */
    luaL_dostring(L, "print \"Hello, world\"");

    /* Clean-up */
    lua_close(L);

    return 0;
}
