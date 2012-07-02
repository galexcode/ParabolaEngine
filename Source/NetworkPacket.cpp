#include "ParabolaCore/NetworkPacket.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates a packet
NetworkPacket::NetworkPacket(ENetEvent *event){
	myPacket = event->packet;
};

/// Destroy the packet, deallocate
NetworkPacket::~NetworkPacket(){
	enet_packet_destroy(myPacket);
};

/// Get the packet size in bytes
size_t NetworkPacket::getPacketSize(){
	return myPacket->dataLength;
};

/// Get as a string
String NetworkPacket::toString(){
	return String((char*)myPacket->data, myPacket->dataLength);
};

/// Get the packet as a raw array
void* NetworkPacket::getRawData(){
	return myPacket->data;
};

/// Get the packet as an SFML packet
/*sf::Packet NetworkPacket::asSFMLPacket(){
	sf::Packet p;
	p.append(myPacket->data, myPacket->dataLength);
	return p;
};*/

PARABOLA_NAMESPACE_END