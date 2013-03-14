class Block
{
	bool vertical; // verticality
	Vec2f position; // real size
	Vec2f size; // real size
	int cellLength; // grid unit length
	Vec2f cellPosition; // grid unit position
	Color color;
	Sprite sprite;
}
array<Block> m_blocks;
Vec2f tablePosition;
Vec2f tableSize;
float cellSize = 80;
string currentLevel;

View view;

void initTable()
{
	// set the real positions of the blocks
	for(uint i = 0; i < m_blocks.length(); i++)
	{
		m_blocks[i].position.x = tablePosition.x + m_blocks[i].cellPosition.x * cellSize;
		m_blocks[i].position.y = tablePosition.y + m_blocks[i].cellPosition.y * cellSize;
		
		if(m_blocks[i].vertical)
		{
			m_blocks[i].size.x = cellSize;
			m_blocks[i].size.y = m_blocks[i].cellLength * cellSize;
			m_blocks[i].color.r = 255;
			m_blocks[i].color.b = 100;
		}
		else
		{
			m_blocks[i].size.y = cellSize;
			m_blocks[i].size.x = m_blocks[i].cellLength * cellSize;
			m_blocks[i].color.g = 50;
			m_blocks[i].color.r = 50;
			m_blocks[i].color.b = 50;
		}

		m_blocks[i].sprite.setTexture(game.content.getTexture("dummy.png"));
		m_blocks[i].sprite.setPosition(m_blocks[i].position.x, m_blocks[i].position.y);
		m_blocks[i].sprite.resize(m_blocks[i].size.x, m_blocks[i].size.y);
		
	}
}

void onMessage(string message)
{
	currentLevel = message;
	print("Got a message: " + currentLevel + "\n");
}

void buttonclicked()
{
	print("\n\n\nButton clicked\n\n");
	this.launchBindedState("level_select");
	this.finish();
}

void buttonclick()
{
	
}

bool loaded = false;
void onCreate()
{
	if(loaded) return;

	loaded = true;
	print("Time to load a level: " + "Levels/" + currentLevel);
	
	
	UIWindow@ ui = this.ui.create("game");
	
	UISurface@ surface = ui.addSurface("main");
	
	UIButton button;
	button.setPosition(0,0);
	button.setSize(120,40);
	button.setLabel("Menu");
	button.bindSignal("click", this.slot("buttonclicked"));
	surface.addControl(button);
	
	if(game.content.loadTexture("dummy.png"))
	{
		print("Loaded texture!\n");
	}
	
	while(m_blocks.length() > 0)
	{
		m_blocks.removeLast();
	}
	
	view.setRect(0,0,1024,768);
	
	tablePosition.x = 50;
	tablePosition.y = 50;
	tableSize.x = 10;
	tableSize.y = 7;
	
	File@ fp = game.content.openRawFile("Levels/" + currentLevel, "r");
	if(fp.good())
	{
		array<string> boardSize = fp.getLine().split(" ");
		tableSize.x = parseFloat(boardSize[0]);
		tableSize.y = parseFloat(boardSize[1]);
		
		// lets parse!
		int count = parseInt(fp.getLine());
		m_blocks.resize(count);
		for(int i = 0; i < count; i++)
		{
			// parse pieces
			string pieceLine = fp.getLine();
			array<string> elements = pieceLine.split(" ");
			
			// verticality 
			if(elements[0] == "H"){ m_blocks[i].vertical = false;print("Horizontal piece");}
			else{ m_blocks[i].vertical = true; print("Vertical piece");}
			
			// cell position
			m_blocks[i].cellPosition.x = parseInt(elements[1]);
			m_blocks[i].cellPosition.y = parseInt(elements[2]);
			m_blocks[i].cellLength = parseInt(elements[3]);

		}
	}
	
	initTable();
}

Block@ draggedBlock = null;
Sprite@ dragged = null;
Vec2f dragOffset;
Vec2f lastMouse;

void onEvent(Event@ event)
{
	if(event.type == Events::KeyPressed)
	{
		if(event.key() == Keyboard::Escape)
		{
			this.launchBindedState("level_select");
			this.finish();
		}
		
		if(event.key() == Keyboard::F1)
		{
			print("Active States: " + game.states.getActiveStateCount());
		}

	}

	if(event.isPointerPressed())
	{
		Vec2i position = event.getPointerPosition();
		Vec2f realPosition = game.window.convertCoords(position, view);
		print("" + realPosition.x);
		
		for(uint i = 0; i < m_blocks.length(); i++)
		{
			if(m_blocks[i].sprite.contains(realPosition.x, realPosition.y))
			{
				print("DRAGGING");
				@dragged = m_blocks[i].sprite;
				@draggedBlock = m_blocks[i];
				dragOffset.x = realPosition.x - m_blocks[i].sprite.getPosition().x;
				dragOffset.y = realPosition.y - m_blocks[i].sprite.getPosition().y;
			}
		}
		
		lastMouse = realPosition;
	}
	
	if(event.isPointerMoved())
	{
		Vec2i position = event.getPointerPosition();
		Vec2f realPosition = game.window.convertCoords(position, view);
		
		if(dragged !is null)
		{
			if(draggedBlock.vertical)
			{
				float finalY = realPosition.y - dragOffset.y;
				if(finalY < tablePosition.y) finalY = tablePosition.y;
				else if(finalY + draggedBlock.size.y > tablePosition.y + tableSize.y * cellSize) finalY =  tablePosition.y + tableSize.y * cellSize - draggedBlock.size.y;
			
				dragged.setPosition(dragged.getPosition().x, finalY);
			}
			else
			{
				float finalX = realPosition.x - dragOffset.x;
				if(finalX < tablePosition.x) finalX = tablePosition.x;
				else if(finalX + draggedBlock.size.x > tablePosition.x + tableSize.x * cellSize) finalX =  tablePosition.x + tableSize.x * cellSize - draggedBlock.size.x;
				
				if(realPosition.x - lastMouse.x > 0)
				{
					// right movement check
					//print("moving right");
				}
				else
				{
					//print("moving left");
					// left movement check
					for(uint i = 0; i < m_blocks.length(); i++)
					{
						if(@m_blocks[i] !is @draggedBlock)
						{
							if(m_blocks[i].sprite.contains(finalX, m_blocks[i].sprite.getPosition().y + 2))
							{
								// intersect, push right
								finalX = m_blocks[i].sprite.getPosition().x + m_blocks[i].size.x;
								break;
							}
						}
					}
				}
				
				
				
				
				dragged.setPosition(finalX, dragged.getPosition().y);
			}
			
		}
		
		lastMouse = realPosition;
	}
	
	if(event.isPointerReleased())
	{
		Vec2i position = event.getPointerPosition();
		Vec2f realPosition = game.window.convertCoords(position, view);
		
		if(dragged !is null)
		{
			@dragged = null;
		}
	}
}

void onUpdate(float elapsedTime)
{
	
}

void onRender(Renderer@ renderer)
{	
	renderer.drawDebugCircle(Vec2f(20,20), 50, Vec2f(), Color(200,200,200));

	for(int i = 0; i < tableSize.x; i++)
	{
		for(int j = 0; j < tableSize.y; j++)
		{
			// draw block
			Vec2f middle;
			middle.x = tablePosition.x + cellSize / 2 + cellSize * i;
			middle.y = tablePosition.y + cellSize / 2 + cellSize * j;
			renderer.drawDebugQuad(middle.x, middle.y, 0, cellSize*0.9, cellSize*0.9, Color(255,255,255));
			//print("Drawing grid");
		}
	}

	//renderer.drawDebugText(400,400, "Game mode: ");
	for(uint i = 0; i < m_blocks.length(); i++)
	{
		//renderer.drawDebugQuad(m_blocks[i].position.x + m_blocks[i].size.x / 2, m_blocks[i].position.y + m_blocks[i].size.y / 2, 0, m_blocks[i].size.x, m_blocks[i].size.y, m_blocks[i].color);
		renderer.draw(m_blocks[i].sprite);
	}
	
	this.ui.draw("game", renderer);

}