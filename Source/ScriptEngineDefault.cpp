#ifndef MINIMAL_BUILD

#include "ParabolaCore/ScriptEngineDefault.h"
#include "ParabolaCore/ScriptEngine.h"
#include "ParabolaCore/TextFileStream.h"
#include "ParabolaCore/StringList.h"

#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

PARABOLA_NAMESPACE_BEGIN

void EchoTask::run(const String &calledAs, String arguments){
	cout<< "echo: "<<arguments<<endl;
}

void ParseTask::run(const String &calledAs, String arguments){
	StringList args = arguments.split(" ");
	
	if(args.size() == 0){
		cout<<"Invalid use of Parse."<<endl;
	}
	else if(args.size() >= 1){
		TextStream in(args[0], StreamMode::ReadOnly);

		if(in){
			while(!in.atEnd()){
				String line = in.getLine();
				if(myParent)
					myParent->run(line);
			}
		}
	}

}

void GetHttpTask::run(const String &calledAs, String arguments){
	StringList args = arguments.split(" ");

	if(args.size() == 0){
		cout<<"Invalid use of GetHttp"<<endl;
	}
	else if(args.size() >= 1){
		sf::Http http;

		http.setHost(args[0]);

		// Prepare a request to get the 'features.php' page
		sf::Http::Request request("");

		// Send the request
		sf::Http::Response response = http.sendRequest(request);

		// Check the status code and display the result
		sf::Http::Response::Status status = response.getStatus();
		if (status == sf::Http::Response::Ok)
		{
			//std::cout << response.GetBody() << std::endl;
			cout<<"GetHttp was sucessfull: ";
			if(args.size() == 2){
				TextStream out(args[1], StreamMode::WriteOnly);
				if(out.valid()){
					out << response.getBody();
				}
				cout<<"saved file ["<<args[1]<<"].";
			}
			else{
				cout<<"no file, printing."<<endl<<response.getBody();
			}
			cout<<endl;
		}
		else
		{
			std::cout << "Error " << status << std::endl;
		}
	}

	
}

PARABOLA_NAMESPACE_END

#endif