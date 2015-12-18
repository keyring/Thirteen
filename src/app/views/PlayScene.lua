--
-- Author: keyring
-- Date: 2015-12-17 17:37:49
--

local PlayScene = class("PlayScene", cc.load("mvc").ViewBase)
local ROW = 7
local COL = 7
local PLAY_LAYER_WIDTH = 630
local PLAY_LAYER_HEIGHT = 630
local BLOCK_WIDTH = PLAY_LAYER_WIDTH / COL
local BLOCK_HEIGHT = PLAY_LAYER_HEIGHT / ROW
local HALF_BLOCK_WIDTH = BLOCK_WIDTH * 0.5
local HALF_BLOCK_HEIGHT = BLOCK_HEIGHT * 0.5

function PlayScene:onCreate()
    -- add background image
    -- display.newSprite("HelloWorld.png")
    --     :move(display.center)
    --     :addTo(self)

    -- -- add HelloWorld label
    -- cc.Label:createWithSystemFont("Hello World", "Arial", 40)
    --     :move(display.cx, display.cy + 200)
    --     :addTo(self)

    self:CreatePlayLayer(PLAY_LAYER_WIDTH, PLAY_LAYER_HEIGHT):addTo(self):move(display.cx, display.cy)

end

function PlayScene:CreatePlayLayer( width, height )
	local layer = cc.LayerColor:create(cc.c4b(255,255,255,255), width, height)
	layer:ignoreAnchorPointForPosition(false)

	for i=1,COL do
		for j=1,ROW do
			display.newSprite("block0.png")
				:move(HALF_BLOCK_WIDTH+(i-1)*BLOCK_WIDTH, HALF_BLOCK_HEIGHT+(j-1)*BLOCK_HEIGHT)
				:addTo(layer)
		end
	end



	return layer
end

function PlayScene:IndexToRowCol( index )
	local row = math.ceil(index / COL)
	local col = (index - 1) % COL + 1

	return row, col
end

function PlayScene:RowColToIndex( row, col )

	return (row-1)*COL+col
end

function PlayScene:RowColToPosition( row, col )
	return HALF_BLOCK_WIDTH+(col-1)*BLOCK_WIDTH, HALF_BLOCK_HEIGHT+(row-1)*BLOCK_HEIGHT
end

function PlayScene:PositionToRowCol( pos )
	return (pos.y - HALF_BLOCK_HEIGHT)/BLOCK_HEIGHT + 1, (pos.x - HALF_BLOCK_WIDTH)/BLOCK_WIDTH + 1
end

return PlayScene
