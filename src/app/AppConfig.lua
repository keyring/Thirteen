--
-- Author: keyring
-- Date: 2016-01-04 15:35:46
--
local app = cc.Application:getInstance()
cc.exports.APP_TARGET_PLATFORM = app:getTargetPlatform()
if APP_TARGET_PLATFORM == cc.PLATFORM_OS_IPHONE or APP_TARGET_PLATFORM == cc.PLATFORM_OS_IPAD  then
	cc.exports.APP_FONTNAME = "DFPWaWaW5-GB"
else
	cc.exports.APP_FONTNAME = "DFPWaWaW5-GB.ttf"
end

display.loadSpriteFrames("pack.plist", "pack.png")

audio.preloadSound("click.wav")
audio.preloadSound("crush.wav")



function cc.exports.ShowFlashNotice()

	local scene = cc.Director:getInstance():getRunningScene()
	local sprite = scene:getChildByName("notice")
	if not sprite then
		sprite = display.newSprite("#kuang.png"):addTo(scene):move(display.cx-50, 200):setName("notice")

		local size = sprite:getContentSize()

		cc.Label:createWithSystemFont("NOT Enough", APP_FONTNAME, 26)
			:setColor(cc.c3b(207,40,47))
			:move(20, size.height*0.5)
			:addTo(sprite)
			:setAnchorPoint(0,0.5)

		display.newSprite("#coin.png"):move(190,size.height*0.5)
			:setScale(0.4)
			:addTo(sprite)

		cc.Label:createWithSystemFont(", Re-download game", APP_FONTNAME, 26)
			:setColor(cc.c3b(207,40,47))
			:move(215, size.height*0.5)
			:addTo(sprite)
			:setAnchorPoint(0,0.5)

		local move_ease_in = cc.EaseOut:create(cc.MoveBy:create(0.75, cc.p(100, 0)), 2.5)
		local move_ease_out = cc.EaseOut:create(cc.MoveBy:create(0.75, cc.p(-100, 0)), 2.5)

		sprite:runAction(cc.RepeatForever:create( cc.Sequence:create( move_ease_in, cc.DelayTime:create(0.1), move_ease_out, cc.DelayTime:create(0.1) )))
	end


end