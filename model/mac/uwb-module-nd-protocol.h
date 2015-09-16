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

#ifndef UWB_MODULE_ND_PROTOCOL_H
#define UWB_MODULE_ND_PROTOCOL_H

#include <ns3/trailer.h>
#include <ns3/packet.h>
#include <ns3/mac64-address.h>
#include <ns3/uwb-module-net-device.h>

namespace ns3
{
	class UwbModuleNdProtocol
	{
	public:
		UwbModuleNdProtocol();
		virtual ~UwbModuleNdProtocol();

		Ptr<Packet> GeneratePingPacket(const Mac64Address & senderAddress) ;
		Mac64Address GetSenderAddress(Ptr<const Packet>) ;

	private:



	};
}


#endif