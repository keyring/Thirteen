#include "lua_cocos2dx_connect_auto.hpp"
#include "ConnectUtility.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_connect_ConnectUtility_SendToClient(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_SendToClient'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ConnectUtility:SendToClient"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_SendToClient'", nullptr);
            return 0;
        }
        cobj->SendToClient(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:SendToClient",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_SendToClient'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_JoinRoom(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_JoinRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ConnectUtility:JoinRoom"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_JoinRoom'", nullptr);
            return 0;
        }
        cobj->JoinRoom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:JoinRoom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_JoinRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_GameFailed(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_GameFailed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_GameFailed'", nullptr);
            return 0;
        }
        cobj->GameFailed();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:GameFailed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_GameFailed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_SendToServer(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_SendToServer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ConnectUtility:SendToServer"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_SendToServer'", nullptr);
            return 0;
        }
        cobj->SendToServer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:SendToServer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_SendToServer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_getClientIp(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_getClientIp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_getClientIp'", nullptr);
            return 0;
        }
        char* ret = cobj->getClientIp();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:getClientIp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_getClientIp'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_NewRoom(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_NewRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ConnectUtility:NewRoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_NewRoom'", nullptr);
            return 0;
        }
        cobj->NewRoom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:NewRoom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_NewRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_init(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_isJoinRoom(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_isJoinRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_isJoinRoom'", nullptr);
            return 0;
        }
        bool ret = cobj->isJoinRoom();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:isJoinRoom",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_isJoinRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_ExitRoom(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_ExitRoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_ExitRoom'", nullptr);
            return 0;
        }
        cobj->ExitRoom();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:ExitRoom",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_ExitRoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_executeLuaCallback(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_executeLuaCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ConnectUtility:executeLuaCallback"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_executeLuaCallback'", nullptr);
            return 0;
        }
        cobj->executeLuaCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:executeLuaCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_executeLuaCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_registerLuaCallback(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ConnectUtility*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_connect_ConnectUtility_registerLuaCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ConnectUtility:registerLuaCallback");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_registerLuaCallback'", nullptr);
            return 0;
        }
        cobj->registerLuaCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:registerLuaCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_registerLuaCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ConnectUtility",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_create'", nullptr);
            return 0;
        }
        ConnectUtility* ret = ConnectUtility::create();
        object_to_luaval<ConnectUtility>(tolua_S, "ConnectUtility",(ConnectUtility*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ConnectUtility:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_connect_ConnectUtility_constructor(lua_State* tolua_S)
{
    int argc = 0;
    ConnectUtility* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_connect_ConnectUtility_constructor'", nullptr);
            return 0;
        }
        cobj = new ConnectUtility();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ConnectUtility");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ConnectUtility:ConnectUtility",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_connect_ConnectUtility_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_connect_ConnectUtility_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ConnectUtility)");
    return 0;
}

int lua_register_cocos2dx_connect_ConnectUtility(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ConnectUtility");
    tolua_cclass(tolua_S,"ConnectUtility","ConnectUtility","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"ConnectUtility");
        tolua_function(tolua_S,"new",lua_cocos2dx_connect_ConnectUtility_constructor);
        tolua_function(tolua_S,"SendToClient",lua_cocos2dx_connect_ConnectUtility_SendToClient);
        tolua_function(tolua_S,"JoinRoom",lua_cocos2dx_connect_ConnectUtility_JoinRoom);
        tolua_function(tolua_S,"GameFailed",lua_cocos2dx_connect_ConnectUtility_GameFailed);
        tolua_function(tolua_S,"SendToServer",lua_cocos2dx_connect_ConnectUtility_SendToServer);
        tolua_function(tolua_S,"getClientIp",lua_cocos2dx_connect_ConnectUtility_getClientIp);
        tolua_function(tolua_S,"NewRoom",lua_cocos2dx_connect_ConnectUtility_NewRoom);
        tolua_function(tolua_S,"init",lua_cocos2dx_connect_ConnectUtility_init);
        tolua_function(tolua_S,"isJoinRoom",lua_cocos2dx_connect_ConnectUtility_isJoinRoom);
        tolua_function(tolua_S,"ExitRoom",lua_cocos2dx_connect_ConnectUtility_ExitRoom);
        tolua_function(tolua_S,"executeLuaCallback",lua_cocos2dx_connect_ConnectUtility_executeLuaCallback);
        tolua_function(tolua_S,"registerLuaCallback",lua_cocos2dx_connect_ConnectUtility_registerLuaCallback);
        tolua_function(tolua_S,"create", lua_cocos2dx_connect_ConnectUtility_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ConnectUtility).name();
    g_luaType[typeName] = "ConnectUtility";
    g_typeCast["ConnectUtility"] = "ConnectUtility";
    return 1;
}
TOLUA_API int register_all_cocos2dx_connect(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cu",0);
	tolua_beginmodule(tolua_S,"cu");

	lua_register_cocos2dx_connect_ConnectUtility(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

