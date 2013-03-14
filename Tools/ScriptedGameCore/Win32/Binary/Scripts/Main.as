class Ball
{
	float x;
	float y;
	
	float radius;
	
	Vec2f direction;
	float velocity;
}

class Block
{
	float x;
	float y;
	float width;
	float height;
	int life;
	Color color;
}

class Paddle
{
	float x;
	float y;
	float width;
	float height;
	
	float speed;
	int direction; // -1, 0, 1
	
	Color color;
}

Ball ball;
Paddle paddle;
array<Block> blocks;
bool gameOver;

void onCreate()
{
	print("The game has started\n");
	
	startGame();
}

void generateBlocks()
{
	for(float x = 200; x <= 800; x += 110){
		Block b;
		b.x = x;
		b.y = 200;
		b.width = 100;
		b.height = 10;
		b.life = 3;
		b.color.r = 200;
		b.color.g = 100;
		b.color.b = 100;
		blocks.insertLast(b);
	}
	for(float x = 200; x <= 800; x += 110){
		Block b;
		b.x = x;
		b.y = 220;
		b.width = 100;
		b.height = 10;
		b.life = 3;
		b.color.r = 200;
		b.color.g = 100;
		b.color.b = 150;
		blocks.insertLast(b);
	}
	for(float x = 200; x <= 800; x += 110){
		Block b;
		b.x = x;
		b.y = 240;
		b.width = 100;
		b.height = 10;
		b.life = 3;
		b.color.r = 200;
		b.color.g = 150;
		b.color.b = 100;
		blocks.insertLast(b);
	}
}

void startGame()
{
	while(blocks.length() > 0)blocks.removeAt(0);

	ball.x = 1024/2;
	ball.y = 40;
	ball.direction.x = 0;
	ball.direction.y = -1;
	ball.velocity = 600;
	ball.radius = 10;
	
	paddle.x = 1024 / 2;
	paddle.y = 700;
	paddle.width = 150;
	paddle.height = 10;
	paddle.speed = 1000;
	paddle.direction = 0;
	paddle.color.r = 100;
	paddle.color.g = 91;
	paddle.color.b = 91;
	paddle.color.a = 255;
	
	generateBlocks();
	
	gameOver = false;
}

bool isWithin(Ball ball, Block b)
{
	return ((ball.x + ball.radius > b.x) && (ball.x + ball.radius < b.x + b.width));
}

bool onSameHeight(Ball ball, Block b)
{
	return ((ball.y + ball.radius > b.y) && (ball.y + ball.radius < b.y + b.width));
}


void resolveCollision(Ball@ ball, Block@ b, int index)
{
	// Approaching from left
	if(ball.x < b.x)
	{
		if(ball.x + ball.radius > b.x && onSameHeight(ball, b))
		{
			ball.direction.x *= -1;
			ball.x = b.x - ball.radius;
		}
	}
	else if(ball.x > b.x + b.width) // on the right
	{
	
	}
	
	
	if(ball.y < b.y) // on the top
	{
	
	}
	else // approaching from down
	{
		if(isWithin(ball, b) && ball.y > b.y && ball.y - ball.radius < b.y + b.height)
		{
			// redirect ball
			ball.y = b.y + b.height + ball.radius;
			ball.direction.y *= -1;
			
			b.life--;
			b.color.a -= 50;
			
			// HIT
			if(b.life <= 0){
				blocks.removeAt(index);
			}
		}
	}
	
}

void onEvent(Event@ event)
{
		if(event.type == Events::KeyPressed)
		{
			if(event.key() == Keyboard::Left)
			{
				paddle.direction = -1;
			}
			if(event.key() == Keyboard::Right)
			{
				paddle.direction = 1;
			}
			
			if(event.key() == Keyboard::R)
			{
				startGame();
			}
		}
		if(event.type == Events::KeyReleased)
		{
			if(event.key() == Keyboard::Left)
			{
				if(paddle.direction == -1)
					paddle.direction = 0;
			}
			if(event.key() == Keyboard::Right)
			{
				if(paddle.direction == 1)
					paddle.direction = 0;
			}
		}
		
		if(event.type == Events::TouchPressed)
		{
			if(gameOver)
			{
				// start over
				startGame();
			}
		
			if(event.x <= 480/2)
			{
				paddle.direction = -1;
			}
			else
			{
				paddle.direction = 1;
			}
		}
		if(event.type == Events::TouchReleased)
		{					
			paddle.direction = 0;
		}

}

void onUpdate(float elapsedTime)
{
	paddle.x += paddle.direction * paddle.speed * elapsedTime;
	if(paddle.x < 0)paddle.x = 0;
	if(paddle.x + paddle.width > 1024)paddle.x = 1024 - paddle.width;

	ball.x += ball.direction.x * elapsedTime * ball.velocity;
	ball.y += ball.direction.y * elapsedTime * ball.velocity;
	
	for(uint i = 0; i < blocks.length(); i++)
	{
		resolveCollision(ball, blocks[i], i);
	}
	
	if(ball.y - ball.radius < 0)
	{
		ball.direction.y *= -1;
	}	
	
	if(ball.x - ball.radius < 0)
	{
		ball.x = ball.radius;
		ball.direction.x *= -1;
	}
	if(ball.x + ball.radius > 1024)
	{
		ball.x = 1024 - ball.radius;
		ball.direction.x *= -1;
	}
	
	// Check paddle colision - either goes up or loses
	if((ball.y + ball.radius > paddle.y) && !gameOver)
	{
		if((ball.x - ball.radius * 0.8 < paddle.x + paddle.width) && (ball.x + ball.radius * 0.8 > paddle.x))
		{
			//calculate the angle
			float factor = (ball.x - paddle.x) / paddle.width;
			float angle = - 3.14159 * factor;
			float centerAngle = - 3.14159 / 2;
			Vec2f attenuation;
			attenuation.x = -cos(centerAngle) * 0.3;
			attenuation.y = sin(centerAngle) * 0.3;
			
			ball.direction.x = -cos(angle) + attenuation.x;
			ball.direction.y = sin(angle) + attenuation.y;
			ball.y = paddle.y - ball.radius ;
			
		}
		else
		{
			// can still check left and right collision with paddle
			if(ball.x - ball.radius < paddle.x + paddle.width)
			{
				ball.direction.x *= -1;
			}	
			// can still check left and right collision with paddle
			if(ball.x + ball.radius > paddle.x)
			{
				ball.direction.x *= -1;
			}
			
			gameOver = true;
		}
	}
}

void onRender(Renderer@ renderer)
{	
	renderer.drawDebugQuad(paddle.x + paddle.width/2,paddle.y + paddle.height/2,0,paddle.width,paddle.height, paddle.color);
	
	renderer.drawDebugCircle(Vec2f(ball.x, ball.y), ball.radius, Vec2f(0,0), Color(255,255,255));
	
	for(uint i = 0; i < blocks.length(); i++)
	{
		Block b = blocks[i];
		renderer.drawDebugQuad(b.x + b.width/2,b.y + b.height/2,0,b.width,b.height,b.color);
	}
}