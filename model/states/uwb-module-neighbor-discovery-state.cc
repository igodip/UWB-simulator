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

#include "uwb-module-neighbor-discovery-state.h"
#include <ns3/log.h>
#include<ns3/nstime.h>
#include <ns3/double.h>
#include <ns3/simulator.h>
#include <ns3/uwb-module-drand-app.h>
#include <ns3/uwb-module-drand-state.h>

/**
	Cambiare la fase finale
	Alla fine della fase passa la Drand
*/

namespace ns3
{
	
	NS_LOG_COMPONENT_DEFINE("UwbModuleNeighborDiscoveryState");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleNeighborDiscoveryState);

	TypeId UwbModuleNeighborDiscoveryState::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleNeighborDiscoveryState")
			.SetParent<UwbModuleAbstractState>()
			.AddAttribute("PingInterval", "The Ping Interval",
			TimeValue(MilliSeconds(10.0)),
			MakeTimeAccessor(&UwbModuleNeighborDiscoveryState::m_pingInterval),
			MakeTimeChecker())
			.AddAttribute("EndPhase", "Timeout for the endphase",
			TimeValue(MilliSeconds(500.0)),
			MakeTimeAccessor(&UwbModuleNeighborDiscoveryState::m_expPhase),
			MakeTimeChecker());

		return tid;
	}

	UwbModuleNeighborDiscoveryState::UwbModuleNeighborDiscoveryState(Ptr<UwbModuleManager> manager)
	{
		NS_LOG_FUNCTION(this);

		Ptr<UwbModuleDrandApp> app = DynamicCast<UwbModuleDrandApp>(manager);

		m_urv = CreateObject<UniformRandomVariable>();
		m_urv->SetAttribute("Min", DoubleValue(0.0));
		m_urv->SetAttribute("Max", DoubleValue(1000.0));

		m_leaderMac = Mac64Address::ConvertFrom(app->GetNetDevice()->GetAddress());
		m_netDevice = app->GetNetDevice();
		m_app = app;
	}

	UwbModuleNeighborDiscoveryState::~UwbModuleNeighborDiscoveryState()
	{
		NS_LOG_FUNCTION(this);



	}

	void UwbModuleNeighborDiscoveryState::Receive(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this);

		Mac64Address mac = m_ndleProtocol.GetLeaderAddress(packet);
		Mac64Address received = m_ndleProtocol.GetSenderAddress(packet);

		uint32_t size = m_neighbors.size();
		m_neighbors.insert(received);

		bool changed = false;


		if (m_leaderMac < mac)
		{
			changed = true;
			m_leaderMac = mac;

		}

		if (size != m_neighbors.size())
		{
			changed = true;
		}

		if (changed == true)
		{
			m_endPhase.Cancel();
			m_endPhase = Simulator::Schedule(m_expPhase, &UwbModuleNeighborDiscoveryState::EndPhase, this);
		}

	}

	void UwbModuleNeighborDiscoveryState::Start()
	{
		NS_LOG_FUNCTION(this);
		Time startTime = m_urv->GetInteger()*(m_pingInterval / 1000.0);
		NS_LOG_INFO("Start time" << startTime);

		m_pingPhase = Simulator::Schedule(startTime, &UwbModuleNeighborDiscoveryState::PingPacket, this);
		m_endPhase = Simulator::Schedule(m_expPhase, &UwbModuleNeighborDiscoveryState::EndPhase, this);
	}

	const std::set<Mac64Address> & UwbModuleNeighborDiscoveryState::GetNeighbors() const
	{
		NS_LOG_FUNCTION(this);

		return m_neighbors;
	}

	Mac64Address UwbModuleNeighborDiscoveryState::GetLeader() const
	{
		NS_LOG_FUNCTION(this);

		return m_leaderMac;
	}

	void UwbModuleNeighborDiscoveryState::EndPhase()
	{
		NS_LOG_FUNCTION(this);

		if (m_pingPhase.IsExpired())
		{
			return;
		}

		m_pingPhase.Cancel();
		
		NS_LOG_INFO(this << "End Nd/Le Phase" << Simulator::Now());
		Ptr<UwbModuleDrandState> new_state = CreateObject<UwbModuleDrandState>(m_app);
		new_state->SetNeighbors(m_neighbors);
		m_app->SetState(new_state);
		
		m_app->Start();

	}

	void UwbModuleNeighborDiscoveryState::PingPacket()
	{

		NS_LOG_FUNCTION(this);
		Mac64Address mac;

		Ptr<Packet> p = m_ndleProtocol.GeneratePingPacket(mac.ConvertFrom(m_netDevice->GetAddress()), m_leaderMac);
		m_netDevice->Send(p, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 10);

		Time offset = (m_urv->GetInteger())* (m_pingInterval / 1000.0);
		NS_LOG_INFO("Next packet" << offset);

		m_pingPhase = Simulator::Schedule(m_pingInterval + offset, &UwbModuleNeighborDiscoveryState::PingPacket, this);
	}


}