#include "ParabolaCore/TextFileStream.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	bool IsAlphaNumeric(char c){
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') && c == '.')return true;
		else return false;
	}

	TextFileStream TextFileStream::Out = TextFileStream(stdout);
	TextFileStream TextFileStream::In = TextFileStream(stdin);
	TextFileStream TextFileStream::Err = TextFileStream(stderr);
	
	TextFileStream::TextFileStream() : FileStream(){
		delimiter = " ";
	};

	
	TextFileStream::TextFileStream(FILE* Handle) : FileStream(Handle){
		delimiter = " ";
	};

	
	TextFileStream::TextFileStream(String FileName, unsigned int OpenMode) : FileStream(FileName, StreamMode::Unknown + OpenMode){
		delimiter = " ";
	};

	TextFileStream::~TextFileStream(){

	};

	void TextFileStream::setDelimiter(char c){
		delimiter.clear();
		delimiter += c;
	};
	
	void TextFileStream::setDelimiter(const String &s){
		delimiter = s;
	};

	bool TextFileStream::hasNext(){
		Int64 pos = currentPosition();

		while(!atEnd()){
			char *buffer = new char[delimiter.size()];
			read(buffer, delimiter.size());

			if(delimiter != buffer){
				seek(pos); //go back
				return true;
			}
		}

		seek(pos); //go back
		return false;
	};

	String TextFileStream::nextString(){
		// \n always interrupts
		String output;

		bool stop = false;
		while(!stop){
			char c = readChar();
			if(c == '\n')stop = true;
			else{
				output += c; //keep reading until a end line is found or the delimiter
				
				// check if the delimiter was already found.
				if(output.compare(output.size() - 1 - delimiter.size(),delimiter.size(), delimiter) == 0 && delimiter.size() != output.size()){
					//the delimiter is the last characters, crop it out and stop and go back to the right place.
					output.erase(output.size() - delimiter.size() - 1, delimiter.size());
					stop = true;
					seekOffset(0 - delimiter.size());
				}
					
			}
		}

		return output;
	};

	bool TextFileStream::hasNextInt(){
		Int64 pos = currentPosition();
		bool result;
		String str = nextString();
		if(atoi(str.c_str()) == 0)result = false;
		else result = true;
		seek(pos); //go back
		return result;
	};
	
	int TextFileStream::nextInt(){
		return nextString().toInt();
	};

	bool TextFileStream::hasNextFloat(){
		Int64 pos = currentPosition();
		bool result;
		String str = nextString();
		if(atof(str.c_str()) == 0)result = false;
		else result = true;
		seek(pos); //go back
		return result;
	};

	float TextFileStream::nextFloat(){
		return nextString().toFloat();
	};

	char TextFileStream::readChar(){
		return fgetc(handle());
	};

	void TextFileStream::skipLine(){
		char c;
		while((c = readChar()) != '\n'){
			if(c == EOF)break;
		};
	};

	void TextFileStream::skipChar(char c){
		while(readChar() == c);
	};

	void TextFileStream::skipUntil(char c){
		while(readChar() != c);
	};

	void TextFileStream::skipWhitespace(){
		while(::isspace(readChar()));
		seekOffset(-1);
	};

	String TextFileStream::getLine(){
		String out;
		char c = readChar();
		while(c != '\n' && c != '\r' && !atEnd()){
			out += c;
			c = readChar();
		}
		return out;
	};

	bool TextFileStream::findChar(char c){
		skipUntil(c);
		char cc = readChar();
		seekOffset(-2);
		if(cc == EOF) return false;
		else return true;
	};

	
	String TextFileStream::readWord(bool acceptNumbers, bool acceptUnderscore){
		String out;



		return out;
	};

	String TextFileStream::readBlock(char beginChar, char endChar){
		String output;
		int BeginStack = 0;
		char c;
		while((c=readChar()) != EOF){
			if(c == beginChar){				
				BeginStack++;
				if(BeginStack > 1){
					output += c;
				}
			}
			else if(c == endChar){
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
					std::cout<<"Parsing Error: Expecting '" <<beginChar<<"'."<<std::endl;

			}
			else{
				//not begin , and not end, either right character, or outside limits
				if(BeginStack >= 1){
					output += c;
				}
			}
		}

		return output;
	};

	FileStream& TextFileStream::operator<<(const String &value){
		write(value.c_str(), value.size()*sizeof(char));
		return *this;
	};

	FileStream& TextFileStream::operator>>(String &value){
		value = nextString();
		return *this;
	};

PARABOLA_NAMESPACE_END