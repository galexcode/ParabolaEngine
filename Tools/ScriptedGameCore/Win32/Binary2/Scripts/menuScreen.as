void onCreate()
{
	print("Main menu:\n(1) Play!\n(2) Exit!\n\n");
}

void onEvent(Event@ event)
{
	if(event.type == Events::KeyPressed)
	{
		if(event.key() == Keyboard::Num1)
		{
			print("Playyyyyy\n\n");
				
			if(!this.launchBindedState("level_select"))
			{
				print("Failed to launch");
			}
			else print("Binded !!!!");
			
			this.finish();
		
		}
		if(event.key() == Keyboard::Num2)
		{
			print("Exit!!!\n\n");
		}
	}
}

void onUpdate(float elapsedTime)
{
	
}

void onRender(Renderer@ renderer)
{	
	renderer.drawDebugText(0, 500, "A daniela é linda");
}