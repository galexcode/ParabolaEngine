
int level = 1;

void onCreate()
{
	print("You won:\n(1) Next Level!\n(2) Stop playing!\n\n");
}

void onEvent(Event@ event)
{
	if(event.type == Events::KeyPressed)
	{
		if(event.key() == Keyboard::Num1)
		{
			// debug , trigger next level
			this.finish();		
		}
		if(event.key() == Keyboard::Up)
		{
			level++;
		}
	}
	

}

void onUpdate(float elapsedTime)
{
	
}

void onRender(Renderer@ renderer)
{	
	renderer.drawDebugText(0, 500, "Choose your level: " + level);
}