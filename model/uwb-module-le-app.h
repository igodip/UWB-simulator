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

#ifndef UWB_MODULE_LE_APP_H
#define UWB_MODULE_LE_APP_H

#include <ns3/uwb-module-manager.h>
#include <ns3/random-variable-stream.h>
#include <ns3/event-id.h>
#include <ns3/mac64-address.h>
#include <ns3/uwb-module-election-protocol.h>
#include <ns3/uwb-module-net-device.h>

namespace ns3
{
	class UwbModuleLeApp : public UwbModuleManager
	{
	public:

		static TypeId GetTypeId();

		UwbModuleLeApp(Ptr<UwbModuleNetDevice> netDevice);
		virtual ~UwbModuleLeApp();

		virtual void Receive(Ptr<Packet> packet);
		virtual void Start();

		Mac64Address GetLeader() const;

	protected:

		void EndLePhase();
		void BroadcastLePacket();

		EventId m_endPhase;
		EventId m_broadcastPhase;

		Mac64Address m_leaderMac;

		Ptr<UniformRandomVariable> m_urv;

		UwbModuleElectionProtocol m_electionProtocol;
		Ptr<NetDevice> m_netDevice;

		Time m_pingInterval;
		Time m_expLePhase;


	};
}

#endif