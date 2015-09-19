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

#ifndef UWB_MODULE_NODE_APP_H
#define UWB_MODULE_NODE_APP_H

#include "uwb-module-manager.h"

#include <ns3/uwb-module-net-device.h>
#include <ns3/uwb-module-nd-protocol.h>
#include <ns3/event-id.h>
#include <set>

namespace ns3
{
	class UwbModuleNodeApp : public UwbModuleManager
	{
	public:

		static TypeId GetTypeId();

		UwbModuleNodeApp(Ptr<UwbModuleNetDevice> netDevice);
		virtual ~UwbModuleNodeApp();

		virtual void Receive(Ptr<Packet> packet);
		virtual void Start();
		
		const std::set<Mac64Address> & GetNeighbors() const;

	protected:

		void EndNdPhase();
		void BroadcastPingPacket();

		EventId m_endPhase;
		EventId m_broadcastPhase;

		Ptr<UwbModuleNetDevice> m_netDevice;
		std::set<Mac64Address> m_neighbors;
		UwbModuleNdProtocol m_ndProtocol;

		Time m_expNdPhase;
		Time m_pingInterval;

	};
}

#endif