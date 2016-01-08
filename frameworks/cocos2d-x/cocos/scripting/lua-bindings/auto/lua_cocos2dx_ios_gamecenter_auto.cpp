#include "lua_cocos2dx_ios_gamecenter_auto.hpp"
#include "DIAAchievement.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_ios_gamecenter_DIAAchievement_release(lua_State* tolua_S)
{
    int argc = 0;
    DIAAchievement* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"DIAAchievement",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (DIAAchievement*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_release'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_release'", nullptr);
            return 0;
        }
        cobj->release();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "DIAAchievement:release",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_release'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ios_gamecenter_DIAAchievement_reportScore(lua_State* tolua_S)
{
    int argc = 0;
    DIAAchievement* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"DIAAchievement",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (DIAAchievement*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_reportScore'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        long arg0;
        const char* arg1;

        ok &= luaval_to_long(tolua_S, 2, &arg0, "DIAAchievement:reportScore");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "DIAAchievement:reportScore"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_reportScore'", nullptr);
            return 0;
        }
        cobj->reportScore(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "DIAAchievement:reportScore",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_reportScore'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ios_gamecenter_DIAAchievement_openGameCenter(lua_State* tolua_S)
{
    int argc = 0;
    DIAAchievement* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"DIAAchievement",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (DIAAchievement*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_openGameCenter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_openGameCenter'", nullptr);
            return 0;
        }
        cobj->openGameCenter();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "DIAAchievement:openGameCenter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_openGameCenter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ios_gamecenter_DIAAchievement_reciveTopXScores(lua_State* tolua_S)
{
    int argc = 0;
    DIAAchievement* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"DIAAchievement",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (DIAAchievement*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_reciveTopXScores'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "DIAAchievement:reciveTopXScores");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_reciveTopXScores'", nullptr);
            return 0;
        }
        cobj->reciveTopXScores(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "DIAAchievement:reciveTopXScores",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_reciveTopXScores'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ios_gamecenter_DIAAchievement_instance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"DIAAchievement",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_instance'", nullptr);
            return 0;
        }
        DIAAchievement* ret = DIAAchievement::instance();
        object_to_luaval<DIAAchievement>(tolua_S, "DIAAchievement",(DIAAchievement*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "DIAAchievement:instance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_instance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ios_gamecenter_DIAAchievement_constructor(lua_State* tolua_S)
{
    int argc = 0;
    DIAAchievement* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_constructor'", nullptr);
            return 0;
        }
        cobj = new DIAAchievement();
        tolua_pushusertype(tolua_S,(void*)cobj,"DIAAchievement");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "DIAAchievement:DIAAchievement",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ios_gamecenter_DIAAchievement_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ios_gamecenter_DIAAchievement_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (DIAAchievement)");
    return 0;
}

int lua_register_cocos2dx_ios_gamecenter_DIAAchievement(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"DIAAchievement");
    tolua_cclass(tolua_S,"DIAAchievement","DIAAchievement","",nullptr);

    tolua_beginmodule(tolua_S,"DIAAchievement");
        tolua_function(tolua_S,"new",lua_cocos2dx_ios_gamecenter_DIAAchievement_constructor);
        tolua_function(tolua_S,"release",lua_cocos2dx_ios_gamecenter_DIAAchievement_release);
        tolua_function(tolua_S,"reportScore",lua_cocos2dx_ios_gamecenter_DIAAchievement_reportScore);
        tolua_function(tolua_S,"openGameCenter",lua_cocos2dx_ios_gamecenter_DIAAchievement_openGameCenter);
        tolua_function(tolua_S,"reciveTopXScores",lua_cocos2dx_ios_gamecenter_DIAAchievement_reciveTopXScores);
        tolua_function(tolua_S,"instance", lua_cocos2dx_ios_gamecenter_DIAAchievement_instance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(DIAAchievement).name();
    g_luaType[typeName] = "DIAAchievement";
    g_typeCast["DIAAchievement"] = "DIAAchievement";
    return 1;
}
TOLUA_API int register_all_cocos2dx_ios_gamecenter(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ii",0);
	tolua_beginmodule(tolua_S,"ii");

	lua_register_cocos2dx_ios_gamecenter_DIAAchievement(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

