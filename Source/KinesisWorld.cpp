#include "ParabolaCore/KinesisWorld.h"

PARABOLA_NAMESPACE_BEGIN
	KinesisWorld::KinesisWorld() : b2World(b2Vec2(0.f, 0.98f)){
		VelocityIterations = 8;
		PositionIterations = 3;
		SetDebugDraw(&DebugRenderer);
		myPixelRatio = 100;
		DebugRenderer.PixelsPerMeter = myPixelRatio;
		DebugRenderer.myParent = this;
		pickerMouseJoint = NULL;
		defaultGroundBody = NULL;

		SetContactListener(&contactListener);
	};

	KinesisWorld::KinesisWorld(Vec2f gravityForce) : b2World(b2Vec2(gravityForce.x, gravityForce.y)){
		VelocityIterations = 8;
		PositionIterations = 3;
		SetDebugDraw(&DebugRenderer);
		myPixelRatio = 100;
		DebugRenderer.PixelsPerMeter = myPixelRatio;
		DebugRenderer.myParent = this;
		pickerMouseJoint = NULL;
		defaultGroundBody = NULL;

		SetContactListener(&contactListener);
	};

	void KinesisWorld::SetVelocityIterationCount(int velocityIterations){
		VelocityIterations = velocityIterations;
	};
		
	int KinesisWorld::GetVelocityIterationCount(){
		return VelocityIterations;
	};
		
	void KinesisWorld::SetPositionIterationCount(int positionIterations){
		PositionIterations = positionIterations;
	};
		
	int KinesisWorld::GetPositionIterationCount(){
		return PositionIterations;
	};

	b2Body* KinesisWorld::GetGroundBody(){
		if(!defaultGroundBody)
			return CreateDefaultGroundBody();
		else
			return defaultGroundBody;
	};

	b2Body* KinesisWorld::CreateDefaultGroundBody(){
		b2BodyDef def;
		def.position = b2Vec2(ToMeters(1), ToMeters(1));
		def.type = b2_staticBody;

		b2PolygonShape box;
		box.SetAsBox(ToMeters(2/2), ToMeters(2/2));

		b2Body *body = CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		fixDef.density = 0.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.5f;

		body->CreateFixture(&fixDef);

		return body;
	};

	bool KinesisWorld::LoadFromFile(String FileName){
		
		KinesisWorldDefinition WorldDef;

		if(!WorldDef.LoadFromFile(FileName, this))
			return false;

		return true;
	};


	void KinesisWorld::Update(float UpdateStep){
		sf::Lock lock(mutex);
		Step(UpdateStep, VelocityIterations, PositionIterations);
		
	};

	bool KinesisWorld::StartPicking(float x, float y){

		if(pickerMouseJoint)
			StopPicking();

		KinesisQueryCallback query;
		b2AABB aabb;
		float real_x_mouse = ToMeters(x);
		float real_y_mouse = ToMeters(y);

		aabb.lowerBound.Set(real_x_mouse - 0.001, real_y_mouse - 0.001);
		aabb.upperBound.Set(real_x_mouse + 0.001, real_y_mouse + 0.001);
		
		
		this->QueryAABB(&query, aabb);

		for(unsigned int i = 0; i < query.getFixtureCount(); i++){
			
			if(query.getFixture(i)->GetBody()->GetType() == b2_staticBody){
				
			}
			else{
				if(query.getFixture(i)->TestPoint(b2Vec2(real_x_mouse, real_y_mouse))){
					b2MouseJointDef jointDef;
					jointDef.bodyA = GetGroundBody();
					jointDef.bodyB = query.getFixture(i)->GetBody();
					jointDef.target = b2Vec2(real_x_mouse, real_y_mouse);
					jointDef.maxForce = 10000;
					//jointDef.frequencyHz = 1/60;
					query.getFixture(i)->GetBody()->SetAwake(true);

					pickerMouseJoint = (b2MouseJoint*)CreateJoint(&jointDef);
					return true;
				}
				else return false;
				
			}
		}

		return false;
	};

	void KinesisWorld::StopPicking(){
		if(IsPickingEnabled()){
			DestroyJoint(pickerMouseJoint);
			pickerMouseJoint = NULL;
		}
	};

	bool KinesisWorld::IsPickingEnabled(){
		return pickerMouseJoint ? true : false;
	};

	void KinesisWorld::UpdatePicking(float x, float y){
		if(pickerMouseJoint){
			pickerMouseJoint->SetTarget(b2Vec2(ToMeters(x), ToMeters(y)));
		
		}
	};

	void KinesisWorld::CreateQuickCircle(int x, int y, int r){
		b2BodyDef def;
		def.position = b2Vec2(ToMeters(x),ToMeters(y));
		def.type = b2_dynamicBody;

		b2CircleShape circle;
		circle.m_radius = ToMeters(r);
		circle.m_p = b2Vec2(0, 0);		

		b2Body *body = CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &circle;
		fixDef.density = 1.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.5f;

		body->CreateFixture(&fixDef);
	};

	b2Body* KinesisWorld::CreateQuickBox(int x, int y, int width, int height){
		b2BodyDef def;
		def.position = b2Vec2(ToMeters(x), ToMeters(y));
		def.type = b2_dynamicBody;

		b2PolygonShape box;
		box.SetAsBox(ToMeters(width/2), ToMeters(height/2));

		b2Body *body = CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		fixDef.density = 1.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.5f;

		body->CreateFixture(&fixDef);

		KinesisBodyActor *bodyActor = new KinesisBodyActor(body);
		body -> SetUserData(bodyActor);
		return body;
	};

	b2Body* KinesisWorld::CreateStaticBox(int x, int y, int width, int height){
		b2BodyDef def;
		def.position = b2Vec2(ToMeters(x), ToMeters(y));
		def.type = b2_staticBody;

		b2PolygonShape box;
		box.SetAsBox(ToMeters(width/2), ToMeters(height/2));

		b2Body *body = CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		//fixDef.density = 1.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.5f;

		body->CreateFixture(&fixDef);

		return body;
	};

	void KinesisWorld::CreateQuickLine(int x, int y, int xx, int yy){
		/*b2BodyDef def;
		def.position = b2Vec2(ToMeters(xx)/ToMeters(x), ToMeters(yy)/ToMeters(y));
		def.type = b2_dynamicBody;

		b2PolygonShape box;
		b2Vec2 v[2];
		v[0] = b2Vec2(ToMeters(x), ToMeters(y));
		v[1] = b2Vec2(ToMeters(xx), ToMeters(yy));
		box.Set(v, 2);

		b2Body *body = CreateBody(&def);

		b2FixtureDef fixDef;
		fixDef.shape = &box;
		fixDef.density = 1.0f;
		fixDef.friction = 0.5f;
		fixDef.restitution = 0.5f;

		body->CreateFixture(&fixDef);*/
	};


	KinesisDebugDraw* KinesisWorld::GetDebugRenderer(){
		return &DebugRenderer;
	};

	float KinesisWorld::getPixelRatio(){
		return myPixelRatio;
	};


	float KinesisWorld::ToMeters(float amount){
		return amount/getPixelRatio();
	};

	float KinesisWorld::ToPixels(float amount){
		return amount*getPixelRatio();
	};

PARABOLA_NAMESPACE_END	