#include "ParabolaCore/Lighting.h"
#include "Lighting/LightSystem.h"
#include "Lighting/Light_Point.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

class LightingEffects::LightingHolder{
public:
	/*LightingHolder(const ltbl::AABB &region, sf::RenderWindow *window) : myLightSystem(region, window, "data/softShadowsTexture.png", "data/attenuation.ps"){
		cout<<"Creating a light system at "<<region.GetCenter().x<<","<<region.GetCenter().y<<endl;

		// Create a light
		ltbl::Light_Point* testLight = new ltbl::Light_Point();
		testLight->intensity = 2.0f;
		testLight->center = region.GetCenter();
		testLight->radius = 600.0f;
		testLight->size = 15.0f;
		testLight->spreadAngle = 2.0f * static_cast<float>(M_PI);
		testLight->softSpreadAngle = 0.0f;
		testLight->CalculateAABB();

		testLight->bleed = 0.4f;
		testLight->linearizeFactor = 0.2f;

		myLightSystem.AddLight(testLight);
		testLight->SetAlwaysUpdate(true);

		// Create a light
		ltbl::Light_Point* testLight2 = new ltbl::Light_Point();
		testLight2->center = ltbl::Vec2f(region.GetCenter().x + 150.0f, region.GetCenter().y);
		testLight2->radius = 500.0f;
		testLight2->size = 30.0f;
		testLight2->color.r = 0.5f;
		testLight2->intensity = 1.5f;
		testLight2->spreadAngle = 2.0f * static_cast<float>(M_PI);
		testLight2->softSpreadAngle = 0.0f;
		testLight2->CalculateAABB();

		myLightSystem.AddLight(testLight2);

		testLight2->SetAlwaysUpdate(false);


		// Create a hull by loading it from a file
		ltbl::ConvexHull* testHull = new ltbl::ConvexHull();

		if(!testHull->LoadShape("data/testShape.txt"))
			abort();

		// Pre-calculate certain aspects
		testHull->CalculateNormals();
		testHull->GenerateAABB();

		testHull->SetWorldCenter(ltbl::Vec2f(region.GetCenter().x - 200, region.GetCenter().y + 50.0f));

		myLightSystem.AddConvexHull(testHull);

	}
	ltbl::LightSystem myLightSystem;*/
};

LightingEffects::LightingEffects(){
	myData = NULL;
	myReady = false;
};

void LightingEffects::create(BoundingBox &area, Window *window){
	//myData = new LightingHolder(ltbl::AABB(ltbl::Vec2f(area.Position.x, area.Position.y), ltbl::Vec2f(area.Size.x, area.Size.y)), window);


	//myData = new LightingHolder(ltbl::AABB(ltbl::Vec2f(area.Position.x, area.Position.y), ltbl::Vec2f( area.Position.x + area.Size.x , area.Position.y + area.Size.y)), window);
	myReady = true;
	myBounds = area;
};

void LightingEffects::setView(View &view){
//	myData->myLightSystem.SetView(view);
}

void LightingEffects::render(SceneRenderer* renderer){
	View v;
	v.reset(sf::FloatRect(myBounds.Position.x, myBounds.Position.y, myBounds.Size.x, myBounds.Size.y));

	//myData->myLightSystem.SetView(renderer->renderTarget()->GetDefaultView());
	//myData->myLightSystem.viewAABB.IncCenter(ltbl::Vec2f(0,500));
	//myData->myLightSystem.SetView()
	//myData->myLightSystem.viewAABB.SetCenter(ltbl::Vec2f(400, 400));
//	v.Reset(sf::FloatRect(myBounds.Position.x, myBounds.Position.y, myBounds.Size.x,myBounds.Size.y));
	/*myData->myLightSystem.SetView(v);
	renderer->setView(v);
	myData->myLightSystem.RenderLights();
	myData->myLightSystem.RenderLightTexture(0.0f);*/
};

bool LightingEffects::ready(){
	return myReady;
};

PARABOLA_NAMESPACE_END