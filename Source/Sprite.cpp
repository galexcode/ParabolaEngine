#include "ParabolaCore/Sprite.h"

PARABOLA_NAMESPACE_BEGIN

	void Sprite::SetPosition(Vec2f Position){
		sf::Sprite::SetPosition(*(sf::Vector2f*)&Position);

	}

	void Sprite::SetPosition(float x, float y){
		sf::Sprite::SetPosition(x, y);
	};

	void Sprite::SetCenterPosition(float x, float y){
		sf::Sprite::SetPosition(x - (GetLocalBounds().Width/2), y - (GetLocalBounds().Height/2));
	};

	Vec2f Sprite::GetPosition(){
		return (*(Vec2f*)&(sf::Sprite::GetPosition()));
	}

	void Sprite::Resize(float x, float y){
		SetScale((x / GetGlobalBounds().Width),(y / GetGlobalBounds().Height)); 
	};

	bool Sprite::ContainsPoint(Vec2f Point){
		return (Point.x >= GetPosition().x
				&& Point.x <= GetPosition().x + GetLocalBounds().Width
				&& Point.y >= GetPosition().y
				&& Point.y <= GetPosition().y + GetLocalBounds().Height);
	}

	/*GameSprite::GameSprite(){
		StaticFlag = true;
		CurrentAnimation = 0;
	}

	sf::Sprite& GameSprite::Get(){
		return Sprite;
	}

	KeyFrameAnimation* GameSprite::CreateAnimation(string AnimationName){
		if(StaticFlag)StaticFlag = false;
		KeyFrameAnimation* Animation = new KeyFrameAnimation(AnimationName);
		Animations.insert(Animations.end(), Animation);
		return Animation;
	}

	void GameSprite::SetActiveAnimation(KeyFrameAnimation *Animation){
		if(Animation == 0)
			return;

		CurrentAnimation = Animation;
		CurrentAnimation->SetTime(0);
		Update(0);
	}

	void GameSprite::Update(float Time){
		if(StaticFlag || CurrentAnimation == 0)
			return;

		if(CurrentAnimation->Update(Time)){
			//Update the object because the keyframe changed
			Sprite.SetImage(CurrentAnimation->GetKeyFrame(CurrentAnimation->GetFrameIndex())->Image());
		}
		
	}*/
PARABOLA_NAMESPACE_END