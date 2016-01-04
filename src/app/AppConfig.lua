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
