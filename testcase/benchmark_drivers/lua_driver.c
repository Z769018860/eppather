#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(void) {
    lua_State *L = luaL_newstate();
    if (L == NULL) {
        return 1;
    }

    luaL_openlibs(L);
    if (luaL_dostring(L, "return 10 + 32") != LUA_OK) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }

    printf("%lld\n", (long long)lua_tointeger(L, -1));
    lua_close(L);
    return 0;
}
