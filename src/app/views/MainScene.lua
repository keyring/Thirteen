
local MainScene = class("MainScene", cc.load("mvc").ViewBase)
local UserData = cc.UserDefault:getInstance()
local COST_MONEY = 5


function MainScene:onCreate()
    -- add background image
    -- display.newSprite("main_bg.jpg")
    --     :move(display.center)
    --     :addTo(self)
    local layer = cc.LayerColor:create(cc.c4b(255,255,255,255))
    self:addChild(layer)

    cc.Label:createWithSystemFont("Thirteen", APP_FONTNAME, 120)
    	:setColor(cc.c3b(207,40,47))
        :move(display.cx, display.cy + 300)
        :addTo(self)

    local btn_start = ccui.Button:create()
    btn_start:setPressedActionEnabled(false)
    btn_start:loadTextureNormal("start.png", ccui.TextureResType.plistType)
    btn_start:setPosition(display.cx, display.cy-100)
    self:addChild(btn_start)
    btn_start:runAction(cc.RepeatForever:create( cc.Sequence:create( cc.ScaleTo:create(0.3, 1.1), cc.ScaleTo:create(0.45, 1) ) ))
    btn_start:addTouchEventListener(function ( sender, eventType )
    	if eventType == ccui.TouchEventType.ended then
    		audio.playSound("click.wav", false)

		    local money = UserData:getIntegerForKey("money")
			if not money then
				money = 100
				UserData:setIntegerForKey("money", money)
			end

			if money - COST_MONEY < 0 then
				ShowFlashNotice()
				return
				-- money = money + 100
				-- UserData:setIntegerForKey("money", money)
			end

    		local view = require("app.views.PlayScene").new()
    		view:showWithScene("FADE", 1, cc.c3b(255,255,255))
    	end
    end)

	display.newSprite("effect.png"):move(display.cx, 20)
		:setAnchorPoint(0.5,0)
		:addTo(self)

end

return MainScene
