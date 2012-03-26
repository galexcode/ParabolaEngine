#ifndef PARABOLA_KINESISWORLD_H
#define PARABOLA_KINESISWORLD_H

#include "Platform.h"
#include <Box2D/Box2D.h>
#include "Vectors.h"
#include "KinesisDebugDraw.h"
#include "KinesisActors.h"
#include <SFML/System.hpp>
#include "KinesisForge.h"
#include "KinesisContactListener.h"
#include "KinesisQueryCallback.h"

PARABOLA_NAMESPACE_BEGIN

	
/**
	\ingroup Kinesis
	\class KinesisWorld
	\brief Provides a complete physics simulation, powered by Box2D.

	You may use this class to create rich physics simulations.

*/
class KinesisWorld : public b2World{
public:		
	/// Constructs the world with normal gravity (0, 0,98), scaled for optimal performance.
	KinesisWorld();

	/// Constructs the world with the given settings		
	KinesisWorld(Vec2f gravityForce);
		
	/// Get the number of pixels in a meter.		
	float getPixelRatio();


		/**
			\brief Set the Velocity iteration count
		*/
		void SetVelocityIterationCount(int velocityIterations);
		/**
			\brief Get the Velocity iteration count
		*/
		int GetVelocityIterationCount();
		/**
			\brief Set the Position iteration count
		*/
		void SetPositionIterationCount(int positionIterations);
		/**
			\brief Sets the Position iteration count
		*/
		int GetPositionIterationCount();

		/**
			\brief Updates the simulation by <UpdateStep>
		*/
		void Update(float UpdateStep);

		float ToMeters(float amount);
		float ToPixels(float amount);

		b2Body* GetGroundBody();
		b2Body* CreateDefaultGroundBody();

		/**
			\brief Picking
		*/
		bool StartPicking(float x, float y);
		void StopPicking();
		bool IsPickingEnabled();
		void UpdatePicking(float x, float y);

		void CreateQuickCircle(int x, int y, int r);
		b2Body* CreateQuickBox(int x, int y, int width, int height);
		void CreateQuickLine(int x, int y, int xx, int yy);
		b2Body* CreateStaticBox(int x, int y, int width, int height);


	

		/**
			\brief Loads objects from FileName and adds them to this simulation

			Creates a World Definition object and loads the custom text file with it, making changes in this KinesisWorld
		*/
		bool LoadFromFile(String FileName);



		/**
			\brief d
		*/
		KinesisDebugDraw* GetDebugRenderer();
		

	private:
		int VelocityIterations, PositionIterations;

		/// Amount of pixels in a meter
		float myPixelRatio;
		
		KinesisDebugDraw DebugRenderer;
		KinesisContactListener contactListener;
		mutable sf::Mutex mutex;

		b2MouseJoint* pickerMouseJoint;
		b2Body* defaultGroundBody;
		
		friend class SceneRenderer;
		
	};

PARABOLA_NAMESPACE_END
#endif