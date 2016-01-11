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



-- local flashNoticeOffsetStack = {}
-- function cc.exports.ShowFlashNotice(text)
--     local width = 300
--     local height = 100

--     if #flashNoticeOffsetStack == 0 then
--         local stackCount = 5
--         for i = 1, stackCount do
--             table.insert(flashNoticeOffsetStack, {used = false, offset = (stackCount - i) * height})
--         end
--     end

--     local node = cc.Node:create()
--     node:setPosition(0, 250)
--     node:setAnchorPoint(0.5, 0.5)
--     node:setColor(cc.c3b(200, 200, 200))
--     node:setOpacity(50)
--     node:setContentSize(width, height)
--     cc.Director:getInstance():getRunningScene():addChild(node)

--     local bg = ccui.ImageView:create("flash.png")
--     bg:setScale9Enabled(true)
--     bg:setContentSize(cc.size(width, height))
--     bg:setAnchorPoint(0.5,0.5)
--     bg:setPosition(width / 2, height / 2)
--     node:addChild(bg)

--     local label = ccui.Text:create()
--     label:setTextAreaSize(cc.size(width, height))
--     label:setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER)
--     label:setTextVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
--     label:setFontSize(22)
--     label:setText(text)
--     label:setColor(cc.c3b(225, 247, 255))
--     label:setPosition(width / 2, height / 2)
--     label:setSize(cc.size(width, height))
--     label:setAnchorPoint(0.5, 0.5)
--     node:addChild(label)

--     local offset = 0
--     local offsetIndex = 0
--     for idx, data in ipairs(flashNoticeOffsetStack) do
--         if data.used == false then
--             offsetIndex = idx
--             offset = data.offset
--         end
--     end

--     local pushOffset = cc.CallFunc:create(function()
--         if offsetIndex > 0 and offsetIndex <= #flashNoticeOffsetStack then
--             flashNoticeOffsetStack[offsetIndex].used = true
--         end
--     end)

--     local moveTime = 0.4
--     local delayTime = 0.6
--     local outTime = 0.3
--     local move = cc.EaseExponentialOut:create(cc.MoveTo:create(moveTime, cc.p(display.cx, 250)))
--     local delay = cc.DelayTime:create(moveTime + delayTime + outTime)
--     local moveDelay = cc.DelayTime:create(moveTime + delayTime)
--     local moveOut = cc.MoveBy:create(outTime, cc.p(80, 0))
--     local fadeout = cc.FadeOut:create(outTime)
--     local spaOut = cc.Spawn:create(moveOut, fadeout)
--     local reomve = cc.RemoveSelf:create()
--     local popOffset =  cc.CallFunc:create(function()
--         if offsetIndex > 0 and offsetIndex <= #flashNoticeOffsetStack then
--             flashNoticeOffsetStack[offsetIndex].used = false
--         end
--     end)

--     local action = cc.Sequence:create({pushOffset, move, delay, reomve, popOffset})
--     node:runAction(action)
--     local seq = cc.Sequence:create(moveDelay, spaOut)
--     bg:runAction(seq)
--     label:runAction(seq:clone())
-- end