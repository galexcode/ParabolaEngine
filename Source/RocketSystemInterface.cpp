#include "ParabolaCore/RocketSystemInterface.h"
#include "ParabolaCore/Strings.h"
#include "ParabolaCore/Logger.h"

PARABOLA_NAMESPACE_BEGIN
	
	// Get the number of seconds elapsed since the start of the application
	float RocketSystemInterface::GetElapsedTime()
	{
		//return timer.getElapsedTime().asSeconds() / 1000.f;
		return 0.f;
	}

	bool RocketSystemInterface::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message)
	{
		String Type;

		switch(type)
		{
		case Rocket::Core::Log::LT_ALWAYS:
			Type = "[Always]";
			break;
		case Rocket::Core::Log::LT_ERROR:
			Type = "[Error]";
			break;
		case Rocket::Core::Log::LT_ASSERT:
			Type = "[Assert]";
			break;
		case Rocket::Core::Log::LT_WARNING:
			Type = "[Warning]";
			break;
		case Rocket::Core::Log::LT_INFO:
			Type = "[Info]";
			break;
		case Rocket::Core::Log::LT_DEBUG:
			Type = "[Debug]";
			break;
		};

		//printf("%s - %s\n", Type.c_str(), message.CString());
		PRINTLOG("[LibRocket]","%s - %s\n", Type.c_str(), message.CString())

		//pLogger::Log(2, String(" ") + Type + message.CString(), "[libRocket]");

		return true;
	};

	int RocketSystemInterface::TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input){
		translated = input;
		
		return 0;
		/*if(input.Length() == 0 || (input.Length() == 1 && input[0] == '\n')){
			translated = input;

			return 0;
		}

		//Rocket localization
		bool Token = false;
		string tokenstr;
		for(unsigned int i = 0; i < input.Length(); i++){
			if(input[i] == '['){
				Token = true;
			}
			else if(input[i] == ']'){
	
				Token = false;
				//process token code				
				//translated += LocalizationSystem::GetString(tokenstr).c_str();
				tokenstr.clear();
			}
			else{
				if(Token){
					tokenstr += input[i];
				}
				else{
					//regular text
					translated += input[i];
				}
			}
		}*/
		return 0;
	};
PARABOLA_NAMESPACE_END