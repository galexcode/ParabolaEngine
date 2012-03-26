#ifndef PARABOLA_NETWORKPACKET_H
#define PARABOLA_NETWORKPACKET_H

#include "Platform.h"
#include "NetworkSocket.h"
#include "Strings.h"
#include <enet/enet.h>
#include <SFML/Network/Packet.hpp>

PARABOLA_NAMESPACE_BEGIN
/**
	\ingroup Network
	\class NetworkPacket
	\brief Holds temporarily an Enet packet, and allows to retrieve the data

	\warning This class' objects are only valid during the callback
*/
class PARABOLA_API NetworkPacket{
public:
	/// Creates a packet
	NetworkPacket(ENetEvent *event);

	/// Destroy the packet, deallocate
	~NetworkPacket();

	/// Get the packet size in bytes
	size_t getPacketSize();

	/// Get the packet as a raw array
	void* getRawData();

	/// Get as a string
	String toString();

	/// Get the packet as an SFML packet
	sf::Packet asSFMLPacket();

private:
	ENetPacket *myPacket;
};
PARABOLA_NAMESPACE_END
#endif