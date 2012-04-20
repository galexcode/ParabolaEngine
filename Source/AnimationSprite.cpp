#include "ParabolaCore/AnimationSprite.h"
#include <iostream>
#include <algorithm>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
	AnimationSprite::AnimationSprite(){
		currentTime = 0.f;
		totalDuration = 0.f;
		frameIndex = -1;
	};

	void AnimationSprite::update(float elapsedTime){		
		if(playing()){		
			
			currentTime += elapsedTime; //perform calculation on newest time

		//	cout<<"currentTime = "<<currentTime<<endl;

			if(currentTime > totalDuration){
				// all frames are over, what to do now?!
				if(looping()){
					//just start over
					currentTime = 0.f + currentTime - totalDuration;
				}
				else{
					stop();
				}
			}

			//find the right frame
			float aTime = 0.f;
			for(unsigned int i = 0; i < frames.size(); i++){
				if((currentTime >= aTime) && (currentTime <= (aTime + frames[i].time))){
					//found the right frame
					//cout<<"applying frame:"<<i<<endl;
					for(unsigned int j = 0; j < myAnimables.size(); j++){
						// apply the frame
						static_cast<Sprite*>(myAnimables[j])->setTexture(*frames[i].myTexture);
						static_cast<Sprite*>(myAnimables[j])->setTextureRect(sf::IntRect(frames[i].myRect.Position.x,frames[i].myRect.Position.y,frames[i].myRect.Size.x,frames[i].myRect.Size.y));
					}

					break;
				}
				aTime += frames[i].time;
			}
		}
		//else, we don't have interest in updating anything
	};

	void AnimationSprite::play(){
		AnimationInterface::play();

	};

	void AnimationSprite::stop(){
		AnimationInterface::stop();

		localTime = 0.0f;
		currentTime = 0.f;
		frameIndex = -1;
	};

	void AnimationSprite::applyFrame(int index){
		if(index < 0 || (unsigned int)index >= frames.size()){
			frameIndex = -1;
			return;
		}

		//index = 0;
		//cout<<"animation count "<<animationSprites.size()<<endl;
		for(unsigned int i = 0; i < animationSprites.size(); i++){
			if(animationSprites[i] == NULL){
				std::cout<<"USING A NULL SPRITE:"<<std::endl;
			}
/*			if(animationSprites[i]->getTexture() != frames[index].texture){
			//if(animationSprites[i]->GetTexture() == NULL && index > 0){
				animationSprites[i]->setTexture(*frames[index].texture, true);
			}*/
				//animationSprites[i]->SetTextureRect(sf::IntRect(0,0,6,6));
				//cout<<"Resized sprite to: "<<frames[index].subRect.BottomRight.x - frames[index].subRect.TopLeft.x<<endl;
				//animationSprites[i]->SetTextureRect(sf::IntRect(frames[index].subRect.TopLeft.x,frames[index].subRect.TopLeft.y, frames[index].subRect.BottomRight.x, frames[index].subRect.BottomRight.y));
				//cout<<"The assigned subrect is x from "<< frames[index].subRect.TopLeft.x<< " to "<<frames[index].subRect.BottomRight.x<<endl;
				//cout<<"Sprite is now "<<animationSprites[i]->GetSize().x<<" long.<"<<endl;
				//animationSprites[i]->Resize(frames[index].subRect.BottomRight.x - frames[index].subRect.TopLeft.x, frames[index].subRect.BottomRight.y - frames[index].subRect.TopLeft.y);

			//}
		}

		localTime = 0.0f;

		frameIndex = index;
	};

	int AnimationSprite::getFrameCount(){
		return (int)frames.size();
	};

	int AnimationSprite::buildFromHorizontalSheet(float frameWidth, int frameCount, Texture* texture ){
		if(!texture)
			return -1;

		int texture_width = texture->getSize().x;
		int texture_height = texture->getSize().y;
		double frame_length = 0.8;

		float offset = 0;
		int framesMade = 0;
		
		bool possible = true;
		while(possible){
			if((offset + frameWidth) > texture_width ){
				possible = false;
				continue;
			}else{
				//can still make a frame
				//do i want too?
				if(framesMade >= frameCount){
					possible = false;
					continue;
				}
				else{
					//there is room and i want the frame
					
					AnimationFrame frame;
//					frame.texture = texture;
				//	frame.subRect.set(offset, 0.f, /*offset +*/ (float)frameWidth, (float)texture_height);
					frame.time = frame_length;

					std::cout<<"made a frame with width: ";

					addFrame(frame);

					
					offset += frameWidth;
					framesMade++;
				}
			}
		}

		return framesMade;

	};
	void AnimationSprite::reset(){
		currentTime = 0.f;
		applyFrame(0);
	};

	void AnimationSprite::addFrame(AnimationFrame &frame){
		totalDuration += frame.time;
		frames.push_back(frame);
	};


/************************************************************************/
/* ANIMATION SPRITE FRAME                                               */
/************************************************************************/
AnimationSprite::AnimationFrame::AnimationFrame(){
		this->time = 0.f;
		this->myTexture = NULL;
		this->myRect.Position = Vec2f(-1.f,-1.f); // this will mean undefined rect, whole
};

AnimationSprite::AnimationFrame::AnimationFrame(BoundingBox &box, Texture *texture, double time){
		this->time = time;
		this->myTexture = texture;
		this->myRect = box;
};

/// Define the texture wanted, if the rect is still undefined (positioned at -1 -1), it becomes the full texture rect
void AnimationSprite::AnimationFrame::setTexture(Texture* texture){
	myTexture = texture;

	if(myRect.Position == Vec2f(-1,-1)){
		myRect.Position = Vec2f(0.f,0.f);
		myRect.Size = Vec2f(myTexture->getSize().x,myTexture->getSize().y);
	}
};

PARABOLA_NAMESPACE_END