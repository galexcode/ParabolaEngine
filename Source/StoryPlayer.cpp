#ifndef MINIMAL_BUILD

#include "ParabolaCore/StoryPlayer.h"
#include "ParabolaCore/StringStream.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN
bool valid_char(char c){
	//std::cout<<"testing:"<<c<<"|";
	if(::isalpha(c) || ::isdigit(c) || c == '_'){
		return true;
	}
	else return false;
}

void log(String m){
	std::cout<<m<<std::endl;
}

void clean_command(String c){
	/*String::iterator it = c.begin();

	while(it != c.end()){
		if(::isspace(it) ){
			it = c.erase(it);
		}
	}*/
}

bool travel_to_next_valid(TextStream &stream){
	char c = stream.readChar();

	bool comment = false;

	bool found  = false;
	while(!found){
		if(c == '#'){
			comment = true;
		}
		else if(c == '\n'){
			comment = false;
		}
		else{
			if(stream.atEnd())return false;
			if(!comment && valid_char(c))found = true;
		}		

		c = stream.readChar();
	}

	stream.seekOffset(-2);

	log(String("First valid char: ")+c);

	return true;

};

void StoryPlayer::parseBlock(String token, String args, String styles, TextStream &stream, bool hasBlock, String parentFileName){
	token.toLowerCase();

	if(token == "include"){
		String path; //deduce the path to include it
		args.removeCharacter('"');
		if(args.startsWith(args[0]+":/") || args.startsWith("/") ){
			path = args; //absolute path
		}
		else{
			parentFileName.removeUntilReverse('/'); //remove until the slash /
			path = parentFileName + args;
		}

		TextStream in(path, StreamMode::ReadOnly);
		if(in.valid()){
			loadFromStream(in, path);
			std::cout<<"Include: "<<path<<std::endl;
		}
		else{
			std::cout<<" Including a invalid file."<<std::endl;
		}
	}
	else if(token == "resourcetable"){
		parseTable(token, args, styles, stream, hasBlock);
	}
	else if(token == "style"){
		parseStyle(token, args, styles, stream, hasBlock);
	}
	else if(token == "storyline"){
		parseStory(token, args, styles, stream, hasBlock);
	}
	else{
		char c;
		while((c = stream.readChar()) != '}'); //dump it
	}
};

void StoryPlayer::parseTable(String token, String args, String styles, TextStream &stream, bool hasBlock){
	char c;
	if(hasBlock){
		while((c = stream.readChar()) != '}');
	}
};

void StoryPlayer::parseStyle(String token, String args, String styles, TextStream &stream, bool hasBlock){
	char c;
	if(hasBlock){
		while((c = stream.readChar()) != '}');
	}
};

void StoryPlayer::parseStory(String token, String args, String styles, TextStream &stream, bool hasBlock){
	args.removeCharacter('"');
	stories[args] = Storyline();
	Storyline& story = stories[args];

	if(hasBlock){
		char c = stream.readChar();
		String command;
		while(c != '}'){
			if(c == '#')stream.skipLine();
			else if(c == ';'){
				clean_command(command);
				command.removeCharacter('\t');
				command.removeCharacter('\n');
				command.removeCharacter('\r');

				parseStoryCommand(story, command);

				std::cout<<"Read command: "<<command<<std::endl;
				command.clear();

			}
			else{
				command += c;
			}

			c = stream.readChar();
		}

	}
	story.parent = this;
	
};

void StoryPlayer::parseStoryCommand(Storyline &story, String command){
	StringStream stream(command);

	while(!stream.atEnd()){
		// skip possible whitespace before the command
		stream.skipWhile(' ');

		String command_name, command_args, command_styles;
		char c;
		while(valid_char(c = stream.readChar())){
			command_name += c;
			
		}

		if(c == '('){
			//it has function like arguments
			c = stream.readChar();
			while(c != ')'){
				//the actual arglist
				command_args += c;
				
				c = stream.readChar();
			}
			c = stream.readChar();
		}

		//read styles
		command_styles = stream.readAll();
		

		std::cout<<"Command name: "<<command_name<<std::endl;
		std::cout<<"Command args: "<<command_args<<std::endl;
		std::cout<<"Command styles: "<<command_styles<<std::endl;

		command_name.toLowerCase();
		command_args.removeCharacter('"');

		if(command_name == "wait"){
			story.append(new StoryActionWait(command_args));
		}
		else if(command_name == "playsound"){
			story.append(new StoryActionPlaySound(command_args));
		}
		else if(command_name == "showsub"){
			story.append(new StoryActionShowSub(command_args, command_styles));
		}
		else if(command_name == "log"){
			story.append(new StoryActionLog(command_args));
		}
	}
};



	StoryPlayer::StoryPlayer(){
		current_story = NULL;
	};

	bool StoryPlayer::loadStoryFromFile(String fileName){
		TextStream in(fileName, StreamMode::ReadOnly);

		if(in.valid()){
			return loadFromStream(in, fileName);
		}else return false;
	};

	bool StoryPlayer::loadStoryFromPackage(PackageStream *stream){
		return false;
	};

	bool StoryPlayer::loadFromStream(TextStream &stream, String parentFileName){
		
		while(!stream.atEnd()){ //while there is file to read
			if(!travel_to_next_valid(stream)) //travel to the next block beginning
			{
				break; //end of tokens.
			}
			
			String token, args, styles;

			// find a token
			char c;
			while(valid_char(c = stream.readChar())){
				token += c;
			}

			printf("Read token %s\n", token.c_str());

			
			//find if function like call
			if(c == '('){
				//handle as function like
				while((c = stream.readChar()) != ')'){
					args += c;
				}
				c = stream.readChar();
			}

printf("Read args %s\n", args.c_str());

			//find if there are styles
			if(c != '{' && c != ';'){

				while((c = stream.readChar()) != ';' ){
					if(c == '{')break;
					styles += c;
				}
			}

			printf("Read styles %s\n", styles.c_str());

			//now the block, if any
			if(c == '{'){
				log("Block{");
				//parse a block
				parseBlock(token, args, styles, stream, true, parentFileName);
				//while((c = stream.readChar()) != '}')std::cout<<c;
				log("}");
				if(stream.readChar() != ';')stream.seekOffset(-1); //ensure the optional ; is bypassed - only for blocks
			}
			else{
				parseBlock(token, args, styles, stream, false, parentFileName);
			}
			

			// everything is read by now. process
	
		}

		return true;
	};

	/// Feeds events to the storyline
	void StoryPlayer::onEvent(Event &event){

	};
	/// Updates the story playback
	void StoryPlayer::onUpdate(double deltaTime){
		if(current_story && status == PlayModes::PLAYING){
			current_story->update(deltaTime);
		}
	};
	void StoryPlayer::onDraw(){
		if(current_story){
			current_story->onDraw();
		}
	};

	PlayModes::PlayType StoryPlayer::getStatus(){
		return status;
	};

	void StoryPlayer::play(){
		std::cout<<"> Now playing.."<<std::endl;
		if(!renderer){
			std::cout<<">> Warning: No renderer was found, graphics commands won't work."<<std::endl;
		}

		/*if(!soundPlayer){
			std::cout<<">> Warning: No sound player found. Can't use sound commands."<<std::endl;
		}*/

		if(!current_story){
			current_story = &stories["Main"];
			current_story->setParent(this);
			current_story->reset();
			current_story->play();

			status = PlayModes::PLAYING;
		}
	};

	void StoryPlayer::pause(){	
		status = PlayModes::PAUSED;
	};

	void StoryPlayer::stop(){
		status = PlayModes::STOPPED;
		/*if(soundPlayer){
			soundPlayer->stop();
		}*/
		current_story = NULL;
	};

	int StoryPlayer::storyCount(){
		return stories.size();
	};

PARABOLA_NAMESPACE_END

#endif