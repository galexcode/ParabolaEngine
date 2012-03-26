#include "ParabolaCore/StringStream.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN


	StringStream::StringStream(){
		str = NULL;
	};
	StringStream::StringStream(String &in){
		str = &in;
		pos = 0;
	};
	StringStream::~StringStream(){


	};

	bool StringStream::atEnd(){
		if(! str || pos >= str->length()){
			return true;
		}
		else return false;
	};

	void StringStream::skipWhile(char c){

		while( readChar() == c);
		seekOffset(-1);
	};

	char StringStream::readChar(){
		if(pos >= str->length())return EOF;
		else return (*str).at(pos++);
	};

	void StringStream::seekOffset(int byteCount){
		pos += byteCount;
		if(pos < 0)pos = 0;
		if(pos >= str->length() ) pos = str->length();		
	};

	String StringStream::readAll(){
		String out;
		while(!atEnd())out += readChar();
		return out;
	};

	String StringStream::readUntil(char stop){
		String out;
		char c;
		while((c = readChar()) != stop) out += c;
		return out;
	};

	String StringStream::readBlock(char begin, char end){
		if(!str)return "";
		String output;
		int BeginStack = 0;
		char c;
		while(!atEnd()){
			c = readChar();

			if(c == begin){				
				BeginStack++;
				if(BeginStack > 1){
					output += c;
				}
			}
			else if(c == end){
				//done, output

				if(BeginStack == 1){
					//finished
					return output;
				}
				else if(BeginStack > 1){
					BeginStack--;
					output += c;
				}
				else
					std::cout<<"Parsing Error: Expecting '" <<begin<<"'."<<std::endl;

			}
			else{
				//not begin , and not end, either right character, or outside limits
				if(BeginStack >= 1){
					output += c;
				}
			}

			

		};
		return "";
	};	

PARABOLA_NAMESPACE_END