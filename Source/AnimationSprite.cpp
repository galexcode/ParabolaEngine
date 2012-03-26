#include "ParabolaCore/AnimationSprite.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	AnimationSprite::AnimationSprite(){
		currentTime = 0.f;
		totalTime = 0.f;
		frameIndex = -1;
	};

	void AnimationSprite::addSprite(Sprite &animatedSprite){
		animationSprites.push_back(&animatedSprite);
	};

	void AnimationSprite::update(float elapsedTime){
		if(playing()){
			currentTime += elapsedTime;

			if(currentTime > totalTime){
				//animation finished.
				//cout<<"ANIMATION ENDED"<<endl<<endl;
				if(looping()){
					stop();
					play();	
					return;
				}
				else{
					stop();
					return;
				}
			}
			
			//if i got here, there is something to do
			
			localTime += elapsedTime;
			if(localTime >= frames[frameIndex].time){
				//time to apply a new frame
				applyFrame(frameIndex+1);
			}

			
			
		}
		//else, we don't have interest in updating anything
	};

	void AnimationSprite::play(){
		AnimationInterface::play();
		if(frameIndex == -1){
			if(frames.size() == 0){
				stop();
				//will not play at all because there are no frames.
			}
			else{
				applyFrame(0); //apply the first frame so the animation starts.
			}
		}
	};

	void AnimationSprite::stop(){
		AnimationInterface::stop();

		localTime = 0.0f;
		currentTime = 0.f;
		frameIndex = -1;
	};

	void AnimationSprite::applyFrame(int index){
		if(index < 0 || index >= frames.size()){
			frameIndex = -1;
			return;
		}

		//index = 0;
		//cout<<"animation count "<<animationSprites.size()<<endl;
		for(unsigned int i = 0; i < animationSprites.size(); i++){
			if(animationSprites[i] == NULL){
				std::cout<<"USING A NULL SPRITE:"<<std::endl;
			}
			if(animationSprites[i]->GetTexture() != frames[index].texture){
			//if(animationSprites[i]->GetTexture() == NULL && index > 0){
				animationSprites[i]->SetTexture(*frames[index].texture, true);
			}
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

		int texture_width = texture->GetWidth();
		int texture_height = texture->GetHeight();
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
					
					AnimationSpriteFrame frame;
					frame.texture = texture;
					frame.subRect.set(offset, 0, /*offset +*/ frameWidth, texture_height);
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

	void AnimationSprite::addFrame(AnimationSpriteFrame &frame){
		totalTime += frame.time;
		frames.push_back(frame);
	};


	/************************************************************************/
	/* ANIMATION SPRITE FRAME                                               */
	/************************************************************************/
	AnimationSpriteFrame::AnimationSpriteFrame(){
		this->time = 0.f;
		this->texture = NULL;
	};

	AnimationSpriteFrame::AnimationSpriteFrame(BoundingBox &box, Texture *texture, double time){
		this->time = time;
		this->texture = texture;
		this->subRect = box;
	};
PARABOLA_NAMESPACE_END