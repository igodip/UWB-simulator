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

#include <ns3/uwb-module-le-app.h>
#include <ns3/log.h>
#include <ns3/nstime.h>
#include <ns3/double.h>
#include <ns3/simulator.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleLeApp");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleLeApp);

	TypeId UwbModuleLeApp::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleLeApp")
			.SetParent<UwbModuleManager>()
			.AddAttribute("PingInterval", "The Ping Interval",
			TimeValue(MilliSeconds(10.0)),
			MakeTimeAccessor(&UwbModuleLeApp::m_pingInterval),
			MakeTimeChecker())
			.AddAttribute("EndPhase", "Timeout for the endphase",
			TimeValue(MilliSeconds(500.0)),
			MakeTimeAccessor(&UwbModuleLeApp::m_expLePhase),
			MakeTimeChecker());

		return tid;
	}

	UwbModuleLeApp::UwbModuleLeApp(Ptr<UwbModuleNetDevice> netDevice)
	{
		NS_LOG_FUNCTION(this);

		m_netDevice = netDevice;

		m_urv = CreateObject<UniformRandomVariable>();
		m_urv->SetAttribute("Min", DoubleValue(0.0));
		m_urv->SetAttribute("Max", DoubleValue(1000.0));

		m_leaderMac = Mac64Address::ConvertFrom(netDevice->GetAddress());

	}

	UwbModuleLeApp::~UwbModuleLeApp()
	{
		NS_LOG_FUNCTION(this);

	}

	void UwbModuleLeApp::Receive(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);


		// Aggiorno il set
		Mac64Address mac = m_electionProtocol.GetAddress(packet);
		NS_LOG_INFO(mac);
		
		if ((m_leaderMac < mac))
		{
			m_endPhase.Cancel();
			m_endPhase = Simulator::Schedule(m_expLePhase, &UwbModuleLeApp::EndLePhase,this);
			m_leaderMac = mac;
		}


	}

	void UwbModuleLeApp::Start()
	{
		NS_LOG_FUNCTION(this);

		Time startTime = m_urv->GetInteger()*(m_pingInterval / 1000.0);
		NS_LOG_INFO("Start time" << startTime);

		m_broadcastPhase = Simulator::Schedule(startTime, &UwbModuleLeApp::BroadcastLePacket, this);
		m_endPhase = Simulator::Schedule(m_expLePhase, &UwbModuleLeApp::EndLePhase, this);

	}

	void UwbModuleLeApp::EndLePhase()
	{
		NS_LOG_FUNCTION(this);

		//Resetto il timer di broadcastPing
		if (m_broadcastPhase.IsExpired())
		{
			return;
		}

		m_broadcastPhase.Cancel();
		NS_LOG_INFO(this << "End Le Phase" << Simulator::Now());

	}

	void UwbModuleLeApp::BroadcastLePacket()
	{
		NS_LOG_FUNCTION(this);

		Ptr<Packet> p = m_electionProtocol.GeneratePingPacket(m_leaderMac);
		m_netDevice->Send(p, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 10);

		Time offset = (m_urv->GetInteger())* (m_pingInterval / 1000.0);
		NS_LOG_INFO("Next packet" << offset);

		m_broadcastPhase = Simulator::Schedule(m_pingInterval + offset, &UwbModuleLeApp::BroadcastLePacket, this);



	}

	Mac64Address UwbModuleLeApp::GetLeader() const
	{
		return m_leaderMac;
	}

}