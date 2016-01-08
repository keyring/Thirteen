#include "lua_cocos2dx_ios_share_auto.hpp"
#include "IOSShare.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_ios_share_IOSShare_goToAppStore(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"IOSShare",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_share_IOSShare_goToAppStore'", nullptr);
            return 0;
        }
        IOSShare::goToAppStore();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "IOSShare:goToAppStore",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_share_IOSShare_goToAppStore'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ios_share_IOSShare_share(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"IOSShare",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        double arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "IOSShare:share");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "IOSShare:share");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_share_IOSShare_share'", nullptr);
            return 0;
        }
        IOSShare::share(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "IOSShare:share",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_share_IOSShare_share'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_ios_share_IOSShare_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (IOSShare)");
    return 0;
}

int lua_register_cocos2dx_ios_share_IOSShare(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"IOSShare");
    tolua_cclass(tolua_S,"IOSShare","IOSShare","",nullptr);

    tolua_beginmodule(tolua_S,"IOSShare");
        tolua_function(tolua_S,"goToAppStore", lua_cocos2dx_ios_share_IOSShare_goToAppStore);
        tolua_function(tolua_S,"share", lua_cocos2dx_ios_share_IOSShare_share);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(IOSShare).name();
    g_luaType[typeName] = "IOSShare";
    g_typeCast["IOSShare"] = "IOSShare";
    return 1;
}
TOLUA_API int register_all_cocos2dx_ios_share(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ii",0);
	tolua_beginmodule(tolua_S,"ii");

	lua_register_cocos2dx_ios_share_IOSShare(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

