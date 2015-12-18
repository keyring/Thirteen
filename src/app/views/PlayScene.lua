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

	-- 数据初始化
	self.BlockSprites = { 
						  false, false, false, false, false, false, false,
						  false, false, false, false, false, false, false,
						  false, false, false, false, false, false, false,
						  false, false, false, false, false, false, false,
						  false, false, false, false, false, false, false,
						  false, false, false, false, false, false, false,
						  false, false, false, false, false, false, false,
						}

	-- self.BlockSprites = {}
	self.sourceBlockIndex = nil

    self:CreateBackground():addTo(self)

    self:CreatePlayLayer(PLAY_LAYER_WIDTH, PLAY_LAYER_HEIGHT):addTo(self):move(display.cx, display.cy)

end

function PlayScene:CreateBackground(  )
	local background = cc.LayerColor:create(cc.c4b(255,255,255,255))

	return background
end

function PlayScene:CreatePlayLayer( width, height )
	local layer = cc.LayerColor:create(cc.c4b(255,255,255,255), width, height)
	layer:ignoreAnchorPointForPosition(false)

	-- 创建图块背景
	for i=1,COL do
		for j=1,ROW do
			display.newSprite("block0.png")
				:move(HALF_BLOCK_WIDTH+(i-1)*BLOCK_WIDTH, HALF_BLOCK_HEIGHT+(j-1)*BLOCK_HEIGHT)
				:addTo(layer)
		end
	end

	-- 随机创建一个新的block
	self:RandomCreateBlock():addTo(layer)


	-- 添加触摸事件，对应游戏规则
	local function onTouchBegan(touch, event)
		-- 坐标选 source ，并确定是否传递触摸
        -- local target = event:getCurrentTarget()
        
        local locationInNode = layer:convertToNodeSpace(touch:getLocation())
        local s = layer:getContentSize()
        local rect = cc.rect(0, 0, s.width, s.height)
        local row, col = self:PositionToRowCol(locationInNode)
        local index = self:RowColToIndex(row, col)

        
        if cc.rectContainsPoint(rect, locationInNode) and self.BlockSprites[index] then
        	self.sourceBlockIndex = index
			self.BlockSprites[index]:setLocalZOrder(1)
            return true
        end
        return false
	end

	local function onTouchMoved(touch, event)
		-- 将 source 跟随手指移动
		local locationInNode = layer:convertToNodeSpace(touch:getLocation())
		self.BlockSprites[self.sourceBlockIndex]:setPosition(locationInNode)
	end

	local function onTouchEnded(touch, event)
		-- 相同判断
		-- 目标不存在判断
		-- 相加判断 > 13
		-- 相加并修改UI
		local locationInNode = layer:convertToNodeSpace(touch:getLocation())
		local s = layer:getContentSize()
		local rect = cc.rect(0, 0, s.width, s.height)
        local target_row, target_col = self:PositionToRowCol(locationInNode)
        local target_index = self:RowColToIndex(target_row, target_col)

		self.BlockSprites[self.sourceBlockIndex]:setLocalZOrder(0)
        if not cc.rectContainsPoint(rect, locationInNode) then
        	
			self.BlockSprites[self.sourceBlockIndex]:runAction( cc.MoveTo:create(0.2, cc.p( self.BlockSprites[self.sourceBlockIndex].data.posx, self.BlockSprites[self.sourceBlockIndex].data.posy)))
        	self.sourceBlockIndex = 0
            return
        end

        if self.sourceBlockIndex == target_index then
        	self.BlockSprites[self.sourceBlockIndex]:runAction( cc.MoveTo:create(0.2, cc.p( self.BlockSprites[self.sourceBlockIndex].data.posx, self.BlockSprites[self.sourceBlockIndex].data.posy)))
        
        	return
        end

        if not self.BlockSprites[target_index] then
        	local target_posx, target_posy = self:RowColToPosition(target_row, target_col)
        	
        	self.BlockSprites[target_index] = clone(self.BlockSprites[self.sourceBlockIndex])
        	self.BlockSprites[self.sourceBlockIndex] = false

        	self.BlockSprites[target_index]:setPosition(cc.p(target_posx, target_posy))
        	self.BlockSprites[target_index].data.index = target_index
        	self.BlockSprites[target_index].data.row = target_row
        	self.BlockSprites[target_index].data.col = target_col
        	self.BlockSprites[target_index].data.posx = target_posx
        	self.BlockSprites[target_index].data.posy = target_posy

        	
        	self:RandomCreateBlock():addTo(layer)

        else

        	if self.BlockSprites[self.sourceBlockIndex].data.value + self.BlockSprites[target_index].data.value > 13 then
        		self.BlockSprites[self.sourceBlockIndex]:runAction( cc.MoveTo:create(0.2, cc.p( self.BlockSprites[self.sourceBlockIndex].data.posx, self.BlockSprites[self.sourceBlockIndex].data.posy)))

        		
	        else
	        	self.BlockSprites[target_index].data.value = self.BlockSprites[target_index].data.value + self.BlockSprites[self.sourceBlockIndex].data.value
	        	-- self.BlockSprites[target_index].label:setString(self.BlockSprites[target_index].data.value)

				self.BlockSprites[target_index]:runAction(cc.Sequence:create( cc.ScaleTo:create(0.1, 1.2), cc.ScaleTo:create(0.2, 0.8), cc.ScaleTo:create(0.1, 1) ))
	        	self.BlockSprites[self.sourceBlockIndex]:removeFromParent()
	        	self.BlockSprites[self.sourceBlockIndex] = nil
				
				if self.BlockSprites[target_index].data.value == 13 then
					-- self.BlockSprites[target_index].label:setColor(cc.c3b(255,0,0))
					self:CheckCrush(self.BlockSprites[target_index].data.row, self.BlockSprites[target_index].data.col)
				end

	        	self:RandomCreateBlock():addTo(layer)
        	end
        end

	end

	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
	listener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
	listener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)

	local eventDispatcher = self:getEventDispatcher()
	eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)


	return layer
end

function PlayScene:RandomCreateBlockIndex(  )
	-- body

	local unused = {}
	for index=1,#self.BlockSprites do
		if not self.BlockSprites[index] then
			table.insert(unused, index)
		end
	end	

	return unused[math.random(1, #unused)]

end

function PlayScene:RandomCreateBlock(  )
	local index = self:RandomCreateBlockIndex()
	local row, col = self:IndexToRowCol(index)
	local posx, posy = self:RowColToPosition(row, col)

	-- 自定义一个block类
	local block = display.newSprite("block13.png")
		:move(posx, posy)

	block.data = {}
	block.data.index = index
	block.data.row = row
	block.data.col = col
	block.data.posx = posx
	block.data.posy = posy
	block.data.value = math.random(1,12)
	-- block.label = cc.Label:createWithSystemFont(block.data.value, "", 30):move(HALF_BLOCK_WIDTH,HALF_BLOCK_HEIGHT)
	-- block:addChild(block.label)

	block:runAction(cc.Sequence:create( cc.ScaleTo:create(0.1, 1.2),  cc.ScaleTo:create(0.2, 0.8), cc.ScaleTo:create(0.1, 1) ))

	self.BlockSprites[index] = block

	return block
end

function PlayScene:CheckCrush(row, col)

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
	return math.ceil(pos.y/BLOCK_HEIGHT), math.ceil(pos.x/BLOCK_WIDTH)
end

return PlayScene
