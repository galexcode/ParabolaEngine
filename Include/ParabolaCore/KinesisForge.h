#ifndef PARABOLA_KINESISFORGE_H
#define PARABOLA_KINESISFORGE_H

#include "Platform.h"

#include "SceneGraph.h"
#include <Box2D/Box2D.h>
#include "Strings.h"
#include "Vectors.h"
#include <vector>
#include <map>

PARABOLA_NAMESPACE_BEGIN
	class KinesisWorld;

	/**
		\class KinesisWorldDefinition
		\brief Allows loading physic simulations from files into a KinesisWorld
	*/
	class KinesisShapeDefinition{
	public:
		enum ShapeTypes{
			BoxShape = 0,
			CircleShape,
			ChainShape
		};

		int ShapeType;
		Vec2f Dimensions;
		float Density;
		float Friction;
		Vec2f Pin;
	};

	class KinesisBodyDefinition{
	public:
		KinesisBodyDefinition();

		String Name;
		bool Spawn;
		b2BodyType BodyType;
		Vec2f Origin;

		std::vector<KinesisShapeDefinition> Shapes;

	private:

	};

	class KinesisWorldDefinition{
	public:
		
		typedef std::pair<String, String> BlockProperty;
		typedef std::vector<BlockProperty> BlockProperties;
		typedef std::pair<String, BlockProperties> BlockDefinition;

		class BlockSettings{
		public:
			typedef std::pair<String, BlockSettings>  _blockSettings;

			BlockProperties Settings;
			std::vector<_blockSettings> ChildSettings;
		};
		


		KinesisWorldDefinition();

		bool LoadBlock(String BlockName, String BlockContent, KinesisWorld *changeWorld);


		bool LoadFromFile(String FileName, KinesisWorld *changeWorld);

	private:
		BlockSettings ParseBlockSettings(String content);

		KinesisBodyDefinition ParseBodyDefinition(String content);
		
		bool SpawnBody(KinesisBodyDefinition &BodyDef, KinesisWorld *world);

		std::map<String, KinesisBodyDefinition> BodyDefinitions;

	};

PARABOLA_NAMESPACE_END
#endif