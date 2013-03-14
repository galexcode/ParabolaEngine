
int level = 1;

void makeButton(UISurface@ s, string label)
{
	UIButton b;
	b.setLabel(label);
	b.setPosition(0,450);
	s.addControl(b);
}

UIButton button3;
UIWindow@ ui;

bool loaded = false;
void onCreate()
{
	if(loaded) return;
	
	loaded  = true;

	print("IM just starting");
	print("You won:\n(1) Next Level!\n(2) Stop playing!\n\n");
	
	// setup ui
	@ui = this.ui.create("level_select");
	
	UISurface@ surface = ui.addSurface("main");
	
	UIImage imag;
	imag.setPosition(0,0);
	imag.setProportion(1.0, 1.0);
	imag.setImage("logo.png");
	surface.addControl(imag);
	
	UIButton button;
	button.setPosition(0,0);
	button.setSize(120,40);
	button.setLabel("[INCREASE]");
	button.bindSignal("click", this.slot("buttonclicked"));
	button.bindSignal("mouseenter", this.slot("beepsound"));
	surface.addControl(button);
	
	UIButton button2;
	button2.setPosition(120,0);
	button2.setSize(120,40);
	button2.setLabel("Decrease");
	button2.bindSignal("click", this.slot("buttonclicked2"));
	button2.bindSignal("mouseleave", this.slot("mouseMoved"));
	button2.bindSignal("mouseenter", this.slot("beepsound"));
	surface.addControl(button2);
	
	button3.setPlacement(0.5,0.5);
	button3.setProportion(0.3,0.1);
	button3.setLabel("[START]");
	button3.setProperty("color", "rgba(255,0,0)");
	button3.bindSignal("resize", this.slot("resized2"));
	button3.bindSignal("click", this.slot("buttonclicked3"));
	button3.bindSignal("mouseenter", this.slot("beepsound"));
	surface.addControl(button3);
	
	
	
	UIButton leftButton;
	leftButton.setLabel("EN");
	leftButton.setPosition(0, 100);
	leftButton.setSize(40,20);
	leftButton.bindSignal("click", this.slot("setEN"));
	surface.addControl(leftButton);
	
	UIButton rightButton;
	rightButton.setLabel("PT");
	rightButton.setPosition(40, 100);
	rightButton.setSize(40,20);
	rightButton.bindSignal("click", this.slot("setPT"));
	surface.addControl(rightButton);
	
	UILineEdit edit;
	edit.setPosition(0,400);
	edit.setSize(120,40);
	surface.addControl(edit);
	
	UILineEdit edit2;
	edit2.setPosition(120,400);
	edit2.setSize(120,40);
	surface.addControl(edit2);
	
	UIButton soundB;
	soundB.setPosition(0, 300);
	soundB.setSize(20,20);
	soundB.setLabel("P");
	soundB.bindSignal("click", this.slot("playSound"));
	surface.addControl(soundB);
	
	UIButton soundB2;
	soundB2.setPosition(50, 300);
	soundB2.setSize(20,20);
	soundB2.setLabel("P");
	soundB2.bindSignal("click", this.slot("playSound2"));
	surface.addControl(soundB2);
	

	
	/*float xx = 0;
	for(int i = 0; i < 20; i++)
	{
		UIImage im;
		im.setPosition(xx, 80);
		im.setSize(80,80);
		im.setImage("logo2.png");
		im.bindSignal("mouseenter", this.slot("try"));
		surface.addControl(im);
		
		xx += 80;
	}*/
	
	
}

void setEN()
{
	print("Language is now en-US\n");
	ui.setLanguage("en-US");
}

void setPT()
{
	print("Language is now pt-PT\n");
	ui.setLanguage("pt-PT");
}

void beepsound()
{
	game.music.play("beep.wav");
}

void try()
{
	print("entered image\n");
}

void playSound()
{
	game.music.play("cc.ogg");
}

void playSound2()
{
	game.music.play("groan.wav");
}

void resized2()
{
	print("control resized\n");
}

void surfaceMouse()
{
//	print("mouse in surface");
}

void buttonclicked()
{
	level++;
}

void buttonclicked2()
{
	level--;
}

void mouseMoved()
{
	
}

void buttonclicked3()
{
	this.sendMessage("game", "1.txt");
	this.launchBindedState("game");
	this.finish();
}


void onEvent(Event@ event)
{
	if(event.type == Events::KeyPressed && event.key() == Keyboard::Space)
	{
		// toggle console
		game.toggleConsole();
	}

	if(event.type == Events::KeyPressed)
	{		
		if(event.key() == Keyboard::Up)
		{
			level++;
		}
		if(event.key() == Keyboard::Down)
		{
			level--;
		}
		if(event.key() == Keyboard::Return)
		{
			this.sendMessage("game", "" + level + ".txt");
			this.launchBindedState("game");
			this.finish();
		}
		if(event.key() == Keyboard::F1)
		{
			print("Active States: " + game.states.getActiveStateCount());
		}
	}
}

void onUpdate(float elapsedTime)
{
	
}

void onRender(Renderer@ renderer)
{	
	
	this.ui.draw("level_select", renderer);
	renderer.drawDebugText(0, 250, "Choose your level: " + level);	
	
	//renderer.drawDebugQuad(0,0,0,300,300, Color(250,200,200));

}