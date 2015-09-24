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

#ifndef UWB_MODULE_NEIGHBOR_DISCOVERY_STATE_H
#define UWB_MODULE_NEIGHBOR_DISCOVERY_STATE_H

#include "uwb-module-abstract-state.h"
#include <ns3/nstime.h>
#include <ns3/uwb-module-net-device.h>
#include <ns3/random-variable-stream.h>
#include <ns3/mac64-address.h>
#include <ns3/uwb-module-ndle-protocol.h>

#include <set>

namespace ns3
{
	class UwbModuleNeighborDiscoveryState : public UwbModuleAbstractState
	{
	public:

		UwbModuleNeighborDiscoveryState(Ptr<UwbModuleNetDevice> state);
		virtual ~UwbModuleNeighborDiscoveryState();

		static TypeId GetTypeId();

		virtual void Start();
		virtual void Receive(Ptr<Packet> p);

		const std::set<Mac64Address> & GetNeighbors() const;
		Mac64Address GetLeader() const;

	protected:

		void EndPhase();
		void PingPacket();

		Time m_pingInterval;
		Time m_expPhase;

		Ptr < UwbModuleNetDevice> m_netDevice;
		Ptr < UniformRandomVariable > m_urv;

		Mac64Address m_leaderMac;

		std::set<Mac64Address> m_neighbors;

		UwbModuleNdleProtocol m_ndleProtocol;

		EventId m_endPhase;
		EventId m_pingPhase;

	};
}

#endif