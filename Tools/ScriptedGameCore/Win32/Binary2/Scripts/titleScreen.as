void onCreate()
{
	print("Custom state started\n");
	
	print("WHY U NO WORK?\n\n\n");
}

void onEvent(Event@ event)
{
	if(event.type == Events::KeyPressed)
	{
		print("Title screen ended");
		this.finish();
	}
	
	if(event.type == Events::TouchPressed)
	{
		print("Title screen ended");
		this.finish();
	}
}

void onUpdate(float elapsedTime)
{
	
}

void onRender(Renderer@ renderer)
{	
	renderer.drawDebugText(0,400, "Press any key to continue");
}