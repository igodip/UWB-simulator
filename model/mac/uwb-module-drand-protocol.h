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

#ifndef UWB_MODULE_DRAND_PROTOCOL_H
#define UWB_MODULE_DRAND_PROTOCOL_H

#include <ns3/packet.h>
#include <ns3/mac64-address.h>
#include <ns3/uwb-module-net-device.h>

#include <map>

#define UWB_MODULE_DRAND_PROTOCOL 0x3F

namespace ns3
{

	enum UwbModuleDrandPacketType
	{
		UWB_MODULE_DRAND_REQUEST ,
		UWB_MODULE_DRAND_GRANT   ,
		UWB_MODULE_DRAND_RELEASE ,
		UWB_MODULE_DRAND_REJECT  ,
		UWB_MODULE_DRAND_FAIL   ,
		UWB_MODULE_DRAND_NOT
	};

	enum UwbModuleDrandReleaseType
	{
		UWB_MODULE_DRAND_ONE_HOP_RELEASE,
		UWB_MODULE_DRAND_TWO_HOP_RELEASE,
		UWB_MODULE_DRAND_NO_RELEASE
	};

	class UwbModuleDrandProtocol 
	{
	public:

		static UwbModuleDrandProtocol & Get();
		

		Ptr<Packet> GenerateRequest(const Mac64Address & sender);
		Ptr<Packet> GenerateGrant(const Mac64Address & sender,const Mac64Address & receiver, const std::map<uint32_t, Mac64Address>  & turns);
		Ptr<Packet> GenerateRelease(const Mac64Address & sender, uint32_t turn, Mac64Address owner,UwbModuleDrandReleaseType type);
		Ptr<Packet> GenerateReject(const Mac64Address & sender, const Mac64Address & address);
		Ptr<Packet> GenerateFail(const Mac64Address & sender);

		UwbModuleDrandPacketType GetPacketType(Ptr< Packet> p);
		UwbModuleDrandReleaseType GetDrandReleaseType(Ptr<Packet> p);

		void ParseRequest(Ptr<const Packet> p, Mac64Address & sender);
		void ParseGrant(Ptr<const Packet> p, std::map<uint32_t, Mac64Address> & turns);
		void ParseRelease(Ptr<const Packet> p, Mac64Address & sender);
		void ParseReject(Ptr<const Packet> p, Mac64Address & sender);
		void ParseFail(Ptr<const Packet> p, Mac64Address & sender);

	protected:
		UwbModuleDrandProtocol();
		~UwbModuleDrandProtocol();

		
	};
}


#endif