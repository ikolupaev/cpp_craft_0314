#ifndef _MULTICAST_COMMUNICATION_MARKET_MESSAGE_HEADER_H_
#define _MULTICAST_COMMUNICATION_MARKET_MESSAGE_HEADER_H_


namespace multicast_communication
{
	struct market_message_header
	{
		char MessageCategory;
		char MessageType;
		char MessageNetwork;
		char RetransmissionRequester[2];
		char Identifier;
		char Reserved[2];
		char MessageSequenceNumber[9];
		char ParticipantID;
		char TimeStamp[6];
	};
}

#endif