--
-- Author: keyring
-- Date: 2016-02-04 14:54:31
--
local ConnectRoomScene = class("ConnectRoomScene", cc.load("mvc").ViewBase)
local Timer = cc.Director:getInstance():getScheduler()
local UserData = cc.UserDefault:getInstance()

local ConnectMsgType = {
    ADD_ROOM = 1,     -- data = "ip+name"
    GAME_READY = 2,       -- data = "ip"
    GAME_START = 3,       -- data = ""
    BLOCK_CRUSH = 4,      -- data = "ip+count"
    GAME_OVER  = 5       -- data = "ip"
}


function ConnectRoomScene:onCreate()

	self:CreateBackground():addTo(self)
	self:CreateUI():addTo(self)

	self:InitConnectUtility()

end

function ConnectRoomScene:CreateBackground( )
	local background = cc.LayerColor:create(cc.c4b(255,255,255,0))

    local btn_newroom = ccui.Button:create("btn.png")
    -- btn_newroom:setPressedActionEnabled(false)
    -- btn_newroom:loadTextureNormal("start.png", ccui.TextureResType.plistType)
    btn_newroom:addTouchEventListener(function ( sender, eventType )
		if eventType == ccui.TouchEventType.ended then
    		audio.playSound("click.wav", false)

    		self.connectUtility:NewRoom("hehenidaye")
    	end
	end)
    btn_newroom:setPosition(display.cx, 150)
    background:addChild(btn_newroom)

	return background
end

function ConnectRoomScene:CreateUI(  )
	local layer = cc.Layer:create()

    self.roomList = ccui.ListView:create()
    layer:addChild(self.roomList)

    self.roomList:setDirection(ccui.ScrollViewDir.vertical)
    self.roomList:setBounceEnabled(false)
    self.roomList:setContentSize(cc.size(display.width,display.height*0.8))
    self.roomList:setPosition(0,display.height*0.2)

	return layer
end

function ConnectRoomScene:InitConnectUtility(  )
	local connect = cu.ConnectUtility:create()
	self.connectUtility = connect

	self:addChild(connect)

	connect:registerLuaCallback(function ( msg )
		local msgtype = tonumber( string.sub(msg, 1,1) )
		local data = string.sub(msg, 3)

		if msgtype == ConnectMsgType.ADD_ROOM then
			local index = string.find(data, "_")
			local roomip = string.sub(data, 1, index-1)
			local roomname = string.sub(data, index)
			self:CreateListItem(roomip, roomname)
		elseif msgtype == ConnectMsgType.GAME_START then

		elseif msgtype == ConnectMsgType.GAME_OVER then
			

		elseif msgtype == ConnectMsgType.BLOCK_CRUSH then

		end
	end)

end

function ConnectRoomScene:CreateListItem( roomip, roomname )
	local default_item = ccui.Layout:create()

	local item_size = cc.size(display.width, 75)
	default_item:setContentSize(item_size)

	local itembg = display.newSprite("#kuang.png")
		:addTo(default_item)
		:move(item_size.width*0.5-50, item_size.height*0.5)

	cc.Label:createWithSystemFont(roomname, APP_FONTNAME, 26)
		:addTo(default_item)
		:move(item_size.width*0.5-50, item_size.height*0.5)




    self.roomList:pushBackCustomItem(default_item)
    self.roomList:scrollToBottom(0.1,true) 
end

return ConnectRoomScene
