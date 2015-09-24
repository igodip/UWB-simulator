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

#ifndef UWB_MODULE_NDLE_APP
#define UWB_MODULE_NDLE_APP

#include <ns3/uwb-module-manager.h>
#include <ns3/uwb-module-ndle-protocol.h>
#include <ns3/random-variable-stream.h>

namespace ns3
{
	class UwbModuleNdleApp : public UwbModuleManager
	{
	public:

		static TypeId GetTypeId();

		UwbModuleNdleApp(Ptr<UwbModuleNetDevice> netDevice);
		virtual ~UwbModuleNdleApp();

		virtual void Receive(Ptr<Packet> packet);
		virtual void Start();

		const std::set<Mac64Address> & GetNeighbors() const;
		Mac64Address GetLeader() const;

	protected:

		void EndPhase();
		void PingPacket();

		EventId m_endPhase;
		EventId m_pingPhase;

		Ptr<UwbModuleNetDevice> m_netDevice;
		std::set<Mac64Address> m_neighbors;
		Mac64Address m_leaderMac;
		UwbModuleNdleProtocol m_ndleProtocol;

		Ptr<UniformRandomVariable> m_urv;

		Time m_expPhase;
		Time m_pingInterval;

	};
}

#endif