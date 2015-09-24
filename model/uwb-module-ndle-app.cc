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

#include <ns3/uwb-module-ndle-app.h>
#include <ns3/log.h>
#include <ns3/nstime.h>
#include <ns3/double.h>
#include <ns3/simulator.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleNdleApp");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleNdleApp);

	TypeId UwbModuleNdleApp::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleNdleApp")
			.SetParent<UwbModuleManager>()
			.AddAttribute("PingInterval", "The Ping Interval",
			TimeValue(MilliSeconds(10.0)),
			MakeTimeAccessor(&UwbModuleNdleApp::m_pingInterval),
			MakeTimeChecker())
			.AddAttribute("EndPhase", "Timeout for the endphase",
			TimeValue(MilliSeconds(500.0)),
			MakeTimeAccessor(&UwbModuleNdleApp::m_expPhase),
			MakeTimeChecker());

		return tid;
	}

	UwbModuleNdleApp::UwbModuleNdleApp(Ptr<UwbModuleNetDevice> netDevice)
	{
		NS_LOG_FUNCTION(this);

		m_netDevice = netDevice;

		m_urv = CreateObject<UniformRandomVariable>();
		m_urv->SetAttribute("Min", DoubleValue(0.0));
		m_urv->SetAttribute("Max", DoubleValue(1000.0));

		m_leaderMac = Mac64Address::ConvertFrom(netDevice->GetAddress());
	}

	UwbModuleNdleApp::~UwbModuleNdleApp()
	{
		NS_LOG_FUNCTION(this);

	}

	void UwbModuleNdleApp::Receive(Ptr<Packet> packet)
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
			m_endPhase = Simulator::Schedule(m_expPhase, &UwbModuleNdleApp::EndPhase, this);
		}

	}

	void UwbModuleNdleApp::Start()
	{
		NS_LOG_FUNCTION(this);
		Time startTime = m_urv->GetInteger()*(m_pingInterval / 1000.0);
		NS_LOG_INFO("Start time" << startTime);

		m_pingPhase = Simulator::Schedule(startTime, &UwbModuleNdleApp::PingPacket, this);
		m_endPhase = Simulator::Schedule(m_expPhase, &UwbModuleNdleApp::EndPhase, this);
	}

	const std::set<Mac64Address> & UwbModuleNdleApp::GetNeighbors() const
	{
		NS_LOG_FUNCTION(this);

		return m_neighbors;
	}

	Mac64Address UwbModuleNdleApp::GetLeader() const
	{
		NS_LOG_FUNCTION(this);

		return m_leaderMac;
	}

	void UwbModuleNdleApp::EndPhase()
	{
		NS_LOG_FUNCTION(this);

		if (m_pingPhase.IsExpired())
		{
			return;
		}

		m_pingPhase.Cancel();
		NS_LOG_INFO(this << "End Le Phase" << Simulator::Now());
	}

	void UwbModuleNdleApp::PingPacket()
	{

		NS_LOG_FUNCTION(this);
		Mac64Address mac;

		Ptr<Packet> p = m_ndleProtocol.GeneratePingPacket(mac.ConvertFrom(m_netDevice->GetAddress()),m_leaderMac);
		m_netDevice->Send(p, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 10);

		Time offset = (m_urv->GetInteger())* (m_pingInterval / 1000.0);
		NS_LOG_INFO("Next packet" << offset);

		m_pingPhase = Simulator::Schedule(m_pingInterval + offset, &UwbModuleNdleApp::PingPacket, this);
	}


}