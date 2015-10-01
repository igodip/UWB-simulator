/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation;
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include "uwb-module-drand-protocol.h"
#include <ns3/uwb-module-mac-header.h>
#include <ns3/log.h>
#include <ns3/packet.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("UwbModuleDrandProtocol");

	UwbModuleDrandProtocol::UwbModuleDrandProtocol()
	{
		NS_LOG_FUNCTION(this);

		
	}

	UwbModuleDrandProtocol::~UwbModuleDrandProtocol()
	{
		NS_LOG_FUNCTION(this);

	}

	Ptr<Packet> UwbModuleDrandProtocol::GenerateRequest(const Mac64Address & senderMac)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[14];

		buffer[0] = UWB_MODULE_DRAND_PROTOCOL;
		buffer[1] = UWB_MODULE_DRAND_REQUEST & 0xFF;

		UwbModuleMacHeader macHeader;
		macHeader.SetSenderEuid(senderMac);

		Ptr<Packet> packet = Create<Packet>(buffer, 2);
		packet->AddHeader(macHeader);

		return packet;
	}

	Ptr<Packet> UwbModuleDrandProtocol::GenerateGrant(const Mac64Address & senderMac,const Mac64Address & receiverMac, const std::map<uint32_t, Mac64Address>  & turns)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[512];

		buffer[0] = UWB_MODULE_DRAND_PROTOCOL;
		buffer[1] = UWB_MODULE_DRAND_GRANT & 0xFF;

		UwbModuleMacHeader macHeader;
		macHeader.SetSenderEuid(senderMac);
		macHeader.SetReceiverEuid(receiverMac);

		Ptr<Packet> packet = Create<Packet>(buffer,2);
		packet->AddHeader(macHeader);

		return packet;
	}
	
	Ptr<Packet> UwbModuleDrandProtocol::GenerateRelease(const Mac64Address & senderMac,uint32_t turn, Mac64Address owner,UwbModuleDrandReleaseType type)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[22];

		buffer[0] = UWB_MODULE_DRAND_PROTOCOL;
		buffer[1] = UWB_MODULE_DRAND_RELEASE & 0xFF;

		UwbModuleMacHeader macHeader;
		macHeader.SetSenderEuid(senderMac);

		Ptr<Packet> packet = Create<Packet>(buffer,2);
		packet->AddHeader(macHeader);

		return packet;

	}

	Ptr<Packet> UwbModuleDrandProtocol::GenerateReject(const Mac64Address & senderMac,const Mac64Address & receiverMac)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[2];

		buffer[0] = UWB_MODULE_DRAND_PROTOCOL;
		buffer[1] = UWB_MODULE_DRAND_REJECT & 0xFF;

		UwbModuleMacHeader macHeader;
		macHeader.SetSenderEuid(senderMac);
		macHeader.SetReceiverEuid(receiverMac);

		Ptr<Packet> packet = Create<Packet>(buffer,2);
		packet->AddHeader(macHeader);
		return packet;

	}

	Ptr<Packet> UwbModuleDrandProtocol::GenerateFail(const Mac64Address & senderMac)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[2];

		buffer[0] = UWB_MODULE_DRAND_PROTOCOL;
		buffer[1] = UWB_MODULE_DRAND_FAIL & 0xFF;

		UwbModuleMacHeader macHeader;
		macHeader.SetSenderEuid(senderMac);

		Ptr<Packet> packet = Create<Packet>(buffer,2);
		packet->AddHeader(macHeader);

		return packet;
	}

	UwbModuleDrandPacketType UwbModuleDrandProtocol::GetPacketType(Ptr< Packet> p)
	{
		NS_LOG_FUNCTION(this);

		static uint8_t buffer[2];
		UwbModuleMacHeader macHeader;
		
		p->RemoveHeader(macHeader);
		p->CopyData(buffer,2);

		p->AddHeader(macHeader);

		NS_LOG_INFO("Output: "<< (int) buffer[0] << (int) buffer[1]);

		if (buffer[0] != UWB_MODULE_DRAND_PROTOCOL)
		{
			return UWB_MODULE_DRAND_NOT;
		}

		UwbModuleDrandPacketType result = UWB_MODULE_DRAND_NOT;

		switch (buffer[1])
		{
		case UWB_MODULE_DRAND_FAIL:
			
			result = UWB_MODULE_DRAND_FAIL;

			break;

		case UWB_MODULE_DRAND_GRANT:
			
			result = UWB_MODULE_DRAND_GRANT;

			break;
		
		case UWB_MODULE_DRAND_REQUEST:

			result = UWB_MODULE_DRAND_REQUEST;

			break;
		case UWB_MODULE_DRAND_REJECT:

			result = UWB_MODULE_DRAND_REJECT;
			
			break;

		default:

			break;



		}

		return result;
	}

	UwbModuleDrandProtocol & UwbModuleDrandProtocol::Get()
	{
		NS_LOG_FUNCTION_NOARGS();

		static UwbModuleDrandProtocol protocol;

		return protocol;
	}

}