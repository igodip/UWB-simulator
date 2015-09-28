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

#include <map>

namespace ns3
{
	class UwbModuleDrandProtocol 
	{
	public:
		UwbModuleDrandProtocol();
		~UwbModuleDrandProtocol();

		

		Ptr<Packet> GenerateRequest();
		Ptr<Packet> GenerateGrant(const std::map<uint32_t, Mac64Address>  & turns);
		Ptr<Packet> GenerateRelease(uint32_t turn, Mac64Address owner);
		Ptr<Packet> GenerateReject();
		Ptr<Packet> GenerateFail();

	private:
		
	};
}


#endif