void onCreate()
{
	//print("The game has started\n");
	
	ImageState engineLogo;
	engineLogo.setImage("logo.png");
	
	ImageState logo2;
	logo2.setImage("logo2.png");

	CustomState titleScreen;
	titleScreen.set("Scripts/titleScreen.as");
	
	CustomState menuScreen;
	menuScreen.set("Scripts/menuScreen.as");
	
	CustomState gameScreen;
	gameScreen.set("Scripts/game.as");
	
	CustomState levelCompleted;
	levelCompleted.set("Scripts/level_complete.as");
	
	CustomState levelSelect;
	levelSelect.set("Scripts/level_select.as");
	
	
	game.states.bind("game", gameScreen);
	game.states.bind("menu", menuScreen);
	game.states.bind("level_complete", levelCompleted);
	game.states.bind("level_select", levelSelect);
	
	//game.states.addWaiting(engineLogo);
	//game.states.addWaiting(logo2);
	//game.states.addWaiting(titleScreen);
	//game.states.addWaiting(menuScreen);	
	game.states.add(levelSelect);
	
	// Content related
	game.content.load("myAsset.extension"); // infer type by extension
	game.content.load("C:\\myOtherAsset.extension2");
	game.content.loadTexture("logo.png");
	//game.content.loadFont("myFont.ttf");
	Texture@ myTexture = game.content.getTexture("logo.png");
	// by default is binded main list (ContentGroup)
	//game.content.bindList("sub2");
	//game.content.unbindList("sub2");
}

void onEvent(Event@ event)
{
	
}

void onUpdate(float elapsedTime)
{
	
}

void onRender(Renderer@ renderer)
{
	//renderer.drawDebugText(200, 500, "Whats wrong?");
	
	//s.setPosition(200,500);
	
}