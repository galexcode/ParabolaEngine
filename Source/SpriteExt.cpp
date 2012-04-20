#include "ParabolaCore/SpriteExt.h"
#include "ParabolaCore/TextFileStream.h"
#include "ParabolaCore/StringStream.h"
#include <ParabolaCore/StringList.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

void skiptonextword(TextFileStream &in){	
	bool found = false;
	bool skip = false;
	while(!found && !in.atEnd()){
		char c = in.readChar();

		if(c == '#')skip = true;
		else if(c == '\n')skip = false;

		if(!skip){
			if(isalpha(c)){
				in.seekOffset(-1);
				return;
			}
		}
	}

}

void strip_comments(String &content){
	while(content.find_first_of('#') != content.npos){
		content.erase(content.begin() + content.find_first_of('#'), content.begin() + content.find_first_of('\n', content.find_first_of('#')));
	}
}

void strip_tabs(String &content){
	while(content.find_first_of('\t') != content.npos){
		content.erase(content.begin() + content.find_first_of('\t'), content.begin() + content.find_first_of('\t') + 1);
	}
	
	bool intext = false;
	for(String::iterator it = content.begin();it != content.end(); it++){
		if((*it) == '"'){
			intext = !intext;
		}
		else if(!intext && (*it) == ' '){
			it = content.erase(it);
		}
	}

	char c = '\n';
	for(String::iterator it = content.begin();it != content.end(); it++){
		if((*it) == '\n' && ((*it) == c)){
			it = content.erase(it);
		}
		c = (*it);
	}


}

void trim_and_wasps(String &content){
	if(content.find_first_of('"') != content.npos){
		//there are wasps
		content.erase(content.begin(), content.begin() + content.find_first_of('"') + 1);
	}

	if(content.find_last_of('"') != content.npos){
		//there are wasps
		content.erase(content.begin() + content.find_last_of('"'), content.end());
	}
}

/// Creates a ready sprite, that is only a colored square
SpriteExt::SpriteExt(){
	myCurrentAnimation = NULL;
};

/// Check if the sprite contains a point within its rect
bool SpriteExt::containsPoint(float x, float y){
	return mySprite.containsPoint(x,y);
};

/// Check if the sprite contains a point within its rect
bool SpriteExt::containsPoint(Vec2f point){
	return mySprite.containsPoint(point);
};

/// Check if the sprite is flipped in x axis
bool SpriteExt::getFlippedX(){
	return mySprite.isFlippedHorizontally();
};

/// Check if the sprite is flipped in y axis
bool SpriteExt::getFlippedY(){
	return mySprite.isFlippedVertically();
};

/// Flip both axes optionally
/// Flipping is simply multiplying the scale by -1
void SpriteExt::flip(bool flipX, bool flipY){
	if(flipX) mySprite.scale(-1, 1);
	if(flipY) mySprite.scale(1, -1);
};

/// Set the origin of the sprite, relative to the top-left
void SpriteExt::setOrigin(float x, float y){
	mySprite.setOrigin(x,y);
};

/// Set the origin of the sprite, relative to the top-left
void SpriteExt::setOrigin(Vec2f origin){
	mySprite.setOrigin(origin.x, origin.y);
};

/// Set the position of the sprite
void SpriteExt::setPosition(Vec2f position){
	mySprite.setPosition(position);
};

/// Set the position of the sprite
void SpriteExt::setPosition(float x, float y){
	mySprite.setPosition(x,y);
};

/// Resize the sprite, using the scale factor
void SpriteExt::resize(float x, float y){
	mySprite.resize(x,y);
};

/// Orders the start of a new animation
void SpriteExt::triggerAnimation(const String &name){
	if(myAnimations.find(name) != myAnimations.end()){
		myCurrentAnimation = &myAnimations.find(name)->second;
		myCurrentAnimation->play();
	}
	else{
		cout<<"Attempting to start an invalid animation."<<endl;
	}
};

/// Update the sprite state
void SpriteExt::update(float elapsedTime){
	if(myCurrentAnimation){
		myCurrentAnimation->update(elapsedTime);
	}
};

/// Same as the other overload, with no option to load with content banks
bool SpriteExt::loadFromTextFile(const String &path){
	return loadFromTextFile(path, NULL);
};

/// Loads the sprite from a text definition
bool SpriteExt::loadFromTextFile(const String &path, ContentBank *bank){
	TextFileStream in(path, StreamMode::ReadOnly);

	if(!in.valid())return false;

	
	String content;
	while(!in.atEnd()){
		content += in.readChar();		
	}

	strip_comments(content);
	strip_tabs(content);
	StringStream ss(content);

	while(!ss.atEnd()){
		String parse_type = ss.readWord();
		parse_type.toLowerCase();
		if(parse_type == "sprite"){
			String block = ss.readBlock('{', '}');
			parseSettings(block);
		}
		else if(parse_type == "texture"){
			String block = ss.readBlock('{', '}');
			parseTexture(block, bank);
		}
		else if(parse_type == "animation"){
			String block = ss.readBlock('{', '}');
			parseAnimation(block);
		}


		//cout<<parse_type<<endl;
	}
	
	if(myAnimations.size() > 0 && !myDefaultAnimation.empty()){
		// can activate the starting animation
		if(myAnimations.find(myDefaultAnimation) != myAnimations.end()){
			myCurrentAnimation = &myAnimations.find(myDefaultAnimation)->second;
			myCurrentAnimation->play();
			update(0.f);
		}
		else{
			cout<<"Attempting to start an invalid animation."<<endl;
		}
	}	

	return true;
};

/// Parse sprite settings from the code
void SpriteExt::parseSettings(String &code){
	StringStream ss(code);

	while(!ss.atEnd()){
		String parse_type = ss.readWord();
		parse_type.toLowerCase();

		
		if(parse_type == "start"){
			String prop = ss.readUntil('\n');			
			myDefaultAnimation = prop;
			trim_and_wasps(myDefaultAnimation);
		}
	}
};

/// Parse a texture from the code
void SpriteExt::parseTexture(String &code, ContentBank* bank){
	StringStream ss(code);

	String texName;
	String texFile;
	StringList masks;

	while(!ss.atEnd()){
		String parse_type = ss.readWord();
		parse_type.toLowerCase();

		// Frame parsing
		if(parse_type == "file"){
			String prop = ss.readUntil('\n');			
			texFile = prop;
			trim_and_wasps(texFile); 
		}
		else if(parse_type == "resource"){
			String prop = ss.readUntil('\n');			
			texName = prop;
			trim_and_wasps(texName); 
		}
		else if(parse_type == "mask"){
			String prop = ss.readUntil('\n');		
			trim_and_wasps(prop);
			masks.append(prop);
		}

	}

	myTextures[texName] = std::make_shared<Texture>();
	myTextures[texName]->loadFromFile(texFile);

	for(unsigned int i = 0; i < masks.size(); i++){
		//rect of the texture, on absence, its full
		masks[i].removeCharacter(' ');
		StringList values = masks[i].split(',');		

		if(values.size() == 3){
			// i have three color floats
			myTextures[texName]->maskColor(Color(values[0].toInt(),values[1].toInt(),values[2].toInt()));
		}
	}

	cout<<"Parsed texture: "<<texName<<endl;
};

/// Parse an animation from the code
void SpriteExt::parseAnimation(String &code){
	StringStream ss(code);

	String animName;
	AnimationSprite animation;
	bool loop = false;

	while(!ss.atEnd()){
		String parse_type = ss.readWord();
		parse_type.toLowerCase();

		// Frame parsing
		if(parse_type == "frame"){
			AnimationSprite::AnimationFrame newFrame;

			String block = ss.readBlock('{', '}');
			StringStream bs(block);
			while(!bs.atEnd()){
				String prop = bs.readUntil('\n');
				if(!prop.empty()){
					StringList args = prop.split(':');
					if (args.size() == 2)
					{
						String proptype = args[0];
						String propvalue = args[1];

						proptype.toLowerCase();
						trim_and_wasps(propvalue);

						//cout<<"Prop: "<<proptype<<":"<<propvalue<<endl;

						if(proptype == "texture"){
							// fetch texture pointer here
							TextureIterator it = myTextures.find(propvalue);
							if(it == myTextures.end()){
								//throw error
							}
							else{
								newFrame.setTexture(it->second.get());
							}
						}
						else if(proptype == "rect"){
							//rect of the texture, on absence, its full
							StringList values = propvalue.split(",");
							propvalue.removeCharacter(' ');

							if(values.size() == 4){
								// i have four floats
								newFrame.myRect.Position.x = values[0].toFloat();
								newFrame.myRect.Position.y = values[1].toFloat();
								newFrame.myRect.Size.x = values[2].toFloat();
								newFrame.myRect.Size.y = values[3].toFloat();
							}
						}
						else if(proptype == "duration"){
							// duration of this frame
							newFrame.time = propvalue.toFloat();
							//cout<<"frame time:"<<newFrame.time<<endl;
						}
					}
				}
			}

			// now add the frame
			animation.addFrame(newFrame);
		}
		else if(parse_type == "name"){
			String prop = ss.readUntil('\n');			
			animName = prop;
			trim_and_wasps(animName);
		}
		else if(parse_type == "loop"){
			String prop = ss.readUntil('\n');
			trim_and_wasps(prop);
			prop.toLowerCase();
			if(prop == "yes"){
				loop = true;
			}			
		}
	}

	myAnimations[animName] = animation;
	cout<<"Parsed animation: "<<animName<<endl;
	myAnimations[animName].addAnimable(&mySprite);
	if(loop) myAnimations[animName].setLoop(true);
};

/// Making the sprite a drawable
void SpriteExt::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(mySprite, states);
};

PARABOLA_NAMESPACE_END