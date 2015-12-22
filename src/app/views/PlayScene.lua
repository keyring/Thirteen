--
-- Author: keyring
-- Date: 2015-12-17 17:37:49
--

local PlayScene = class("PlayScene", cc.load("mvc").ViewBase)
local Timer = cc.Director:getInstance():getScheduler()
local UserData = cc.UserDefault:getInstance()


local ROW = 7
local COL = 7
local PLAY_LAYER_WIDTH = 630
local PLAY_LAYER_HEIGHT = 630
local BLOCK_WIDTH = PLAY_LAYER_WIDTH / COL
local BLOCK_HEIGHT = PLAY_LAYER_HEIGHT / ROW
local HALF_BLOCK_WIDTH = BLOCK_WIDTH * 0.5
local HALF_BLOCK_HEIGHT = BLOCK_HEIGHT * 0.5
local GAME_OVER_CONDITION = ROW * COL * 7
local COST_MONEY = 5

function PlayScene:onCreate()

	-- self.money = UserData:getIntegerForKey("money")
	-- if not self.money or self.money == 0 then
	-- 	self.money = 100
	-- end

	self.money = 100

	self:CreateBackground():addTo(self)

	-- play数据初始化
	if not self:InitPlayData() then
		return
	end

    self:CreatePlayLayer(PLAY_LAYER_WIDTH, PLAY_LAYER_HEIGHT):addTo(self):move(display.cx, display.cy)

    --- 内存定时清理
	self.cleanerTimer = Timer:scheduleScriptFunc(function (  )
	    -- print("------------memory1-----------:", collectgarbage("count"))
	    collectgarbage("collect")
	    -- print("------------memory2-----------:", collectgarbage("count"))
	end,60,false)

end

function PlayScene:CreateBackground(  )
	local background = cc.LayerColor:create(cc.c4b(255,255,255,255))

	self.label_playScore = cc.Label:createWithSystemFont("0", "", 50)
		:setColor(cc.c3b(0,0,0))
		:move(display.right-50, display.cy+PLAY_LAYER_HEIGHT*0.5+40)
		:addTo(background)
		:setAnchorPoint(1,0.5)

	self.label_money = cc.Label:createWithSystemFont("0", "", 50)
		:setColor(cc.c3b(255,0,0))
		:move(50, display.cy+PLAY_LAYER_HEIGHT*0.5+40)
		:addTo(background,1)
		:setAnchorPoint(0,0.5)

	-- local restart = ccui.Button:create("restart.png")
	-- restart:setAnchorPoint(0,0)
	-- restart:setScale(0.2)
	-- background:addChild(restart)
	-- restart:setPosition(50, display.cy+PLAY_LAYER_HEIGHT*0.5+20)
	-- restart:addTouchEventListener(function ( event, eventType )
	-- 	if eventType == ccui.TouchEventType.ended then
	-- 		self:ResetGame()
	-- 	end
	-- end)

	return background
end

function PlayScene:CreatePlayLayer( width, height )
	local layer = cc.LayerColor:create(cc.c4b(255,255,255,255), width, height)
	layer:ignoreAnchorPointForPosition(false)
	self.playLayer = layer

	-- 创建图块背景
	for i=1,COL do
		for j=1,ROW do
			display.newSprite("block0.png")
				:move(HALF_BLOCK_WIDTH+(i-1)*BLOCK_WIDTH, HALF_BLOCK_HEIGHT+(j-1)*BLOCK_HEIGHT)
				:addTo(layer)
		end
	end

	-- 随机创建新的block
	self:RefreshNext()


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

        -- 是自己
        if self.sourceBlockIndex == target_index then
        	self.BlockSprites[self.sourceBlockIndex]:runAction( cc.MoveTo:create(0.2, cc.p( self.BlockSprites[self.sourceBlockIndex].data.posx, self.BlockSprites[self.sourceBlockIndex].data.posy)))
        
        	return
        end


        if not self.BlockSprites[target_index] then  -- 移到空位
        	local target_posx, target_posy = self:RowColToPosition(target_row, target_col)
        	
        	self.BlockSprites[target_index] = clone(self.BlockSprites[self.sourceBlockIndex])
        	self.BlockSprites[self.sourceBlockIndex] = false

        	self.BlockSprites[target_index]:setPosition(cc.p(target_posx, target_posy))
        	self.BlockSprites[target_index].data.index = target_index
        	self.BlockSprites[target_index].data.row = target_row
        	self.BlockSprites[target_index].data.col = target_col
        	self.BlockSprites[target_index].data.posx = target_posx
        	self.BlockSprites[target_index].data.posy = target_posy

			if self.BlockSprites[target_index].data.value == 13 then
				self:CheckAndCrush(self.BlockSprites[target_index])
			end

        	self:RefreshNext()

        else

        	if self.BlockSprites[self.sourceBlockIndex].data.value + self.BlockSprites[target_index].data.value > 13 then
        		self.BlockSprites[self.sourceBlockIndex]:runAction( cc.MoveTo:create(0.2, cc.p( self.BlockSprites[self.sourceBlockIndex].data.posx, self.BlockSprites[self.sourceBlockIndex].data.posy)))

        		
	        else
	        	-- 相加
	        	self.BlockSprites[target_index].data.value = self.BlockSprites[target_index].data.value + self.BlockSprites[self.sourceBlockIndex].data.value
	        	self.BlockSprites[target_index].label:setString(self.BlockSprites[target_index].data.value)

				self.BlockSprites[target_index]:runAction(cc.Sequence:create( cc.ScaleTo:create(0.1, 1.2), cc.ScaleTo:create(0.2, 0.8), cc.ScaleTo:create(0.1, 1) ))
	        	self.BlockSprites[self.sourceBlockIndex]:removeFromParent()
	        	self.BlockSprites[self.sourceBlockIndex] = false

	        	self:UpdateScore(self.BlockSprites[target_index].data.value)
				
				if self.BlockSprites[target_index].data.value == 13 then
					self.BlockSprites[target_index].label:setColor(cc.c3b(255,0,0))
					self:CheckAndCrush(self.BlockSprites[target_index])
				end

	        	self:RefreshNext()
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

function PlayScene:RefreshNext(  )
	-- 可以随着分数的上涨增加难度，即同时多出现几个
	for i=1,2 do
		self:RandomCreateBlock()
	end
	
end

function PlayScene:ResetGame(  )
	for k,v in pairs(self.BlockSprites) do
		if v then
			v.data = nil
			v:removeFromParent()
			v = false
		end

	end
	-- 数据初始化
	if not self:InitPlayData() then
		return
	end

	self:RefreshNext()
end

function PlayScene:InitPlayData(  )
	self.BlockSprites = { 
					  false, false, false, false, false, false, false,
					  false, false, false, false, false, false, false,
					  false, false, false, false, false, false, false,
					  false, false, false, false, false, false, false,
					  false, false, false, false, false, false, false,
					  false, false, false, false, false, false, false,
					  false, false, false, false, false, false, false,
					}

	self.sourceBlockIndex = nil
	self.playScore = 0
	if self.money - COST_MONEY < 0 then
		return false
	end
	self.money = self.money - COST_MONEY
	UserData:setIntegerForKey("money", self.money)
	self.label_money:setString(self.money)


	self.label_playScore:setString(self.playScore)

	return true
end

function PlayScene:UpdateScore( score )
	self.playScore = self.playScore + score
	self.label_playScore:setString(self.playScore)
end

function PlayScene:UpdateMoney( )
	self.money = self.money + 1
	self.label_money:setString(self.money)
	UserData:setIntegerForKey("money", self.money)
end

function PlayScene:CreateGameOverLayer(  )
	local layer = cc.LayerColor:create(cc.c4b(255,255,255,180))
	self:addChild(layer)

	local restart = ccui.Button:create("restart.png")
	layer:addChild(restart)
	restart:setPosition(display.cx, display.top+50)
	restart:runAction(cc.Sequence:create( cc.MoveTo:create(0.3, cc.p(display.cx, display.cy-50)), cc.MoveTo:create(0.05, cc.p(display.cx, display.cy)) ))
	restart:addTouchEventListener(function ( event, eventType )
		if eventType == ccui.TouchEventType.ended then
			self:ResetGame()
			layer:removeFromParent()
		end
	end)


	local listener = cc.EventListenerTouchOneByOne:create()
	listener:setSwallowTouches(true)
	listener:registerScriptHandler(function ( event, eventType ) return true end, cc.Handler.EVENT_TOUCH_BEGAN)


	local eventDispatcher = self:getEventDispatcher()
	eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)
end


function PlayScene:RandomCreateBlock(  )

	local unused = {}
	for index=1,#self.BlockSprites do
		if not self.BlockSprites[index] then
			table.insert(unused, index)
		end
	end	

	if #unused == 0 then
		return
	end

	local index = unused[math.random(1, #unused)]
	local row, col = self:IndexToRowCol(index)
	local posx, posy = self:RowColToPosition(row, col)

	local data = {}
	data.index = index
	data.row = row
	data.col = col
	data.posx = posx
	data.posy = posy
	data.value = math.random(1,10)
	data.value = math.random(1,10)

	self:CreateSpecialBlock(data)

	if #unused == 1 then
		-- 下一次没有空位了
		self:CreateGameOverLayer()
	end

end

function PlayScene:CreateSpecialBlock( data )
	local block = display.newSprite("block13.png")
		:move(data.posx, data.posy)
		:addTo(self.playLayer)

	block.data = clone(data)

	block.label = cc.Label:createWithSystemFont(block.data.value, "", 30):move(HALF_BLOCK_WIDTH,HALF_BLOCK_HEIGHT)
	block:addChild(block.label)

	block:runAction(cc.Sequence:create( cc.ScaleTo:create(0.1, 1.2),  cc.ScaleTo:create(0.2, 0.8), cc.ScaleTo:create(0.1, 1) ))

	self.BlockSprites[block.data.index] = block

	if block.data.value == 13 then
		self.BlockSprites[block.data.index].label:setColor(cc.c3b(255,0,0))
		self:CheckAndCrush(self.BlockSprites[data.index])
	end
	
end

function PlayScene:CheckAndCrush(checkblock)
	local row_checklist = {}
	local col_checklist = {}

	-- 横着检查一遍
	local neighborcol = checkblock.data.col - 1
	while neighborcol > 0 do 	-- 向左检查
		local tempblock = self.BlockSprites[(checkblock.data.row-1)*COL+neighborcol]
		if tempblock and tempblock.data.value == checkblock.data.value then
			table.insert(row_checklist, tempblock.data.index)
			neighborcol = neighborcol - 1
		else
			break
		end
	end

	neighborcol = checkblock.data.col + 1
	while neighborcol <= COL do 	-- 向右检查
		local tempblock = self.BlockSprites[(checkblock.data.row-1)*COL+neighborcol]
		if tempblock and tempblock.data.value == checkblock.data.value then
			table.insert(row_checklist, tempblock.data.index)
			neighborcol = neighborcol + 1
		else
			break
		end
	end

	-- 竖着检查一遍
	local neighborrow = checkblock.data.row - 1
	while neighborrow > 0 do 	-- 向下检查
		local tempblock = self.BlockSprites[(neighborrow-1)*COL+checkblock.data.col]
		if tempblock and tempblock.data.value == checkblock.data.value then
			table.insert(col_checklist, tempblock.data.index)
			neighborrow = neighborrow - 1
		else
			break
		end
	end

	neighborrow = checkblock.data.row + 1
	while neighborrow <= ROW do 	-- 向上检查
		local tempblock = self.BlockSprites[(neighborrow-1)*COL+checkblock.data.col]
		if tempblock and tempblock.data.value == checkblock.data.value then
			table.insert(col_checklist, tempblock.data.index)
			neighborrow = neighborrow + 1
		else
			break
		end
	end

	-- 简单实现多消，未来扩展不同的多消不同的增强
	local crush_row = false
	local crush_col = false
	if #row_checklist > 1 then
		crush_row = true
		for i=1,#row_checklist do
			self:CrushOneBlock(row_checklist[i])
		end
	end

	if #col_checklist > 1 then
		crush_col = true
		for i=1,#col_checklist do
			self:CrushOneBlock(col_checklist[i])
		end
	end

	if not crush_row and not crush_col then
		return
	end

	local checkblock_index = checkblock.data.index
	local checkblock_row = checkblock.data.row
	local checkblock_col = checkblock.data.col

	if crush_row or crush_col then
		self:CrushOneBlock(checkblock_index)
	end

	if crush_row and not crush_col then                -- 只有横
		if #row_checklist == 3 then    -- 四消       
			--[[  
				  ####  
			--]]
			self:CrushOne()
			
		elseif #row_checklist == 4 then  -- 五消
			--[[  
				  #####  
			--]]
			-- 消除one line
			for col=1,COL do
				local index = (checkblock_row-1)*COL + col
				self:CrushOneBlock(index)
			end
		end


	elseif not crush_row and crush_col then            --只有竖
		if #col_checklist == 3 then    -- 四消
			--[[  
				  #
				  #
				  #
				  # 
			--]]
			self:CrushOne()

		elseif #col_checklist == 4 then  -- 五消
			--[[  
				  #
				  #
				  #
				  #
				  # 
			--]]
			-- 消除one line
			for row=1,ROW do
				local index = (row-1)*COL + checkblock_col
				self:CrushOneBlock(index)
			end
		end

	elseif crush_row and crush_col then               --都有  
		if #row_checklist + #col_checklist == 4 then
			--[[  
				  #
				  #
				  ###

 				   #
				   #
				  ###

				  #
				 ###
				  #
				   
			--]]
			-- 消除one line
			for row=1,ROW do
				local index = (row-1)*COL + checkblock_col
				self:CrushOneBlock(index)
			end
			-- 消除one line
			for col=1,COL do
				local index = (checkblock_row-1)*COL + col
				self:CrushOneBlock(index)
			end
		elseif #row_checklist + #col_checklist == 5 then
			--[[  
				  #
				  #
				 ####

				  #
				 ###
				  #
				  #
				   
			--]]
			-- 消一类
			self:CrushOneType()
		elseif #row_checklist + #col_checklist == 6 then
			--[[  
				  #
				  #
				#####

				  #
				  #
				 ###
				  #
				  #
				   
			--]]
			self:ChangeOneType()
		elseif #row_checklist + #col_checklist == 7 then
			--[[  
				  #
				  #
				#####
				  #
				   
			--]]
            self:ChangeSomeone(3)
		elseif #row_checklist + #col_checklist == 8 then
			--[[  
				  #
				  #
				#####
				  #
				  #		   
			--]]
			-- 	全消
			-- for index=1,#self.BlockSprites do
			-- 	self:CrushOneBlock(index)
			-- end
			self:ChangeOneZone(checkblock_row, checkblock_col)
		end

	end



end

function PlayScene:CrushOne(  )
	-- 随机消一个
	local used = {}
	for k,v in pairs(self.BlockSprites) do
		if v then
			table.insert(used, v.data.index)
		end
	end	

	if #used == 0 then
		return
	end

	local index = used[math.random(1, #used)]
	self:CrushOneBlock(index)

end

function PlayScene:CrushOneType(  )
	-- 随机消一类
	local used = {}
	for k,v in pairs(self.BlockSprites) do
		if v and v.data.value ~= 13 then
			table.insert(used, v.data.index)
		end
	end	

	if #used == 0 then
		return
	end

	local index = used[math.random(1, #used)]
	local value = self.BlockSprites[index].data.value

	for _,v in pairs(used) do
		if self.BlockSprites[v].data.value == value then
			self:CrushOneBlock(v)
		end
	end
	

end

function PlayScene:ChangeOneType(  )
	-- 随机消一类并替换为13
	local used = {}
	for k,v in pairs(self.BlockSprites) do
		if v and v.data.value ~= 13 then
			table.insert(used, v.data.index)
		end
	end	

	if #used == 0 then
		return
	end

	local index = used[math.random(1, #used)]
	local value = self.BlockSprites[index].data.value

	for _,v in pairs(used) do
		if self.BlockSprites[v].data.value == value then
			local data = clone(self.BlockSprites[v].data)
			data.value = 13
			self:CrushOneBlock(v)
			self:CreateSpecialBlock(data)

		end
	end
	

end

function PlayScene:ChangeSomeone( count )
	local used = {}
	for k,v in pairs(self.BlockSprites) do
		if v and v.data.value ~= 13 then
			table.insert(used, v.data.index)
		end
	end	

	if #used == 0 then
		return
	end
    
    if #used <= count then
        for _,v in pairs(used) do
            local data = clone(self.BlockSprites[v].data)
            data.value = 13
            self:CrushOneBlock(v)
            self:CreateSpecialBlock(data)
        end
    else
        local selected = {}
        for i=1,count do
            local idx = math.random( 1, #used )
            table.insert( selected, used[idx] )
            table.remove( used, idx )
        end
        for _,v in pairs(selected) do
            local data = clone(self.BlockSprites[v].data)
            data.value = 13
            self:CrushOneBlock(v)
            self:CreateSpecialBlock(data)
        end
        selected = nil
    end
end

function PlayScene:ChangeOneZone( checkrow, checkcol )
	local delta_row = {-2, 2, 0, -2, 2}
	local delta_col = {-2, 2, 0, 2, -2}

    for i =1, 4 do
        local row = checkrow+delta_row[i]
        local col = checkcol+delta_col[i]
        local idx = (row-1)*COL+col
        if self.BlockSprites[idx] then
            local data = clone(self.BlockSprites[idx].data)
            data.value = 13
            self:CrushOneBlock(idx)
            self:CreateSpecialBlock(data)
        else
        	local x, y = self:RowColToPosition(row, col)
        	local data = {
        		index = idx,
        		row = row,
        		col = col,
        		posx = x,
        		posy = y,
        		value = 13,
        	}
        	self:CreateSpecialBlock(data)
        end
    end



end


function PlayScene:CrushOneBlock( index )
	if self.BlockSprites[index] then

		if self.BlockSprites[index].data.value == 13 then
			
		    local startPoint = cc.p(self.BlockSprites[index].data.posx, self.BlockSprites[index].data.posy+(self.playLayer:getPositionY()-PLAY_LAYER_HEIGHT*0.5))
		    local endPoint = cc.p( self.label_money:getPositionX()+self.label_money:getContentSize().width*0.5, self.label_money:getPositionY())
		    local centerPoint = cc.p((startPoint.x - endPoint.x)*0.5, (endPoint.y - startPoint.y)*0.5+20 )
		    
			local bezier = {
				startPoint,
				centerPoint,
				endPoint,
			}

			local emitter = cc.ParticleFlower:create()
			emitter:setLife(1)
			emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage("particle_stars.png"))
			emitter:setPosition(startPoint)
			emitter:runAction( cc.Sequence:create( cc.BezierTo:create(1, bezier), cc.DelayTime:create(1.2), cc.RemoveSelf:create() ))
			self:addChild(emitter)	

			self:UpdateMoney()		
		end
	    


		self:UpdateScore(self.BlockSprites[index].data.value)

		self.BlockSprites[index].data = nil
		self.BlockSprites[index]:removeFromParent()
		self.BlockSprites[index] = false	
	end
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
