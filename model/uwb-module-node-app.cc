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

#include "uwb-module-node-app.h"

#include <ns3/log.h>
#include <ns3/simulator.h>
#include <ns3/random-variable-stream.h>
#include <ns3/double.h>
#include <ns3/nstime.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleNodeApp");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleNodeApp);

	TypeId UwbModuleNodeApp::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleNodeApp")
			.SetParent<UwbModuleManager>()
			.AddAttribute("PingInterval", "The Ping Interval",
			TimeValue(MilliSeconds(10.0)),
			MakeTimeAccessor(&UwbModuleNodeApp::m_pingInterval),
			MakeTimeChecker())
			.AddAttribute("EndPhase", "Timeout for the endphase",
			TimeValue(MilliSeconds(500.0)),
			MakeTimeAccessor(&UwbModuleNodeApp::m_expNdPhase),
			MakeTimeChecker());

		return tid;
	}

	UwbModuleNodeApp::UwbModuleNodeApp(Ptr<UwbModuleNetDevice> netDevice)
	{
		NS_LOG_FUNCTION(this << netDevice);
		m_netDevice = netDevice;

		m_urv = CreateObject<UniformRandomVariable>();
		m_urv->SetAttribute("Min", DoubleValue(0.0));
		m_urv->SetAttribute("Max", DoubleValue(1000.0));
	}

	UwbModuleNodeApp::~UwbModuleNodeApp()
	{
		NS_LOG_FUNCTION_NOARGS();
	}

	void UwbModuleNodeApp::Receive(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this << packet);

		
		// Aggiorno il set
		Mac64Address mac = m_ndProtocol.GetSenderAddress(packet);
		// Controllo se il numero dei vicini è aumentato o no.
		uint32_t size = m_neighbors.size();

		m_neighbors.insert(mac);
		// Se il numero dei vicini è aumentato, resetto il timer di stop

		if (m_neighbors.size() > size)
		{
			m_endPhase.Cancel();
			m_endPhase = Simulator::Schedule(m_expNdPhase, &UwbModuleNodeApp::EndNdPhase, this);
			//NS_LOG_INFO(this << " Vicino aggiunto " << size << " : " << Simulator::Now());
		}
		
	}

	void UwbModuleNodeApp::Start()
	{
		
		NS_LOG_FUNCTION(this);

		Time startTime = m_urv->GetInteger()*(m_pingInterval/1000.0);
		NS_LOG_INFO("Start time" << startTime);

		m_broadcastPhase = Simulator::Schedule(startTime, &UwbModuleNodeApp::BroadcastPingPacket, this);
		m_endPhase = Simulator::Schedule(m_expNdPhase, &UwbModuleNodeApp::EndNdPhase, this);

		//Attivo anche il timer di stop

	}

	void UwbModuleNodeApp::EndNdPhase()
	{
		NS_LOG_FUNCTION(this);

		//Resetto il timer di broadcastPing
		if (m_broadcastPhase.IsExpired())
		{
			return;
		}

		m_broadcastPhase.Cancel();
		NS_LOG_INFO(this << "End Nd Phase" << Simulator::Now());

		//Passo alla fase successiva


	}

	void UwbModuleNodeApp::BroadcastPingPacket()
	{
		NS_LOG_FUNCTION(this);

		Mac64Address mac;

		Ptr<Packet> p = m_ndProtocol.GeneratePingPacket(mac.ConvertFrom(m_netDevice->GetAddress()));
		m_netDevice->Send(p,Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"),10);

		Time offset = (m_urv->GetInteger())* (m_pingInterval / 1000.0);
		NS_LOG_INFO("Next packet" << offset);

		m_broadcastPhase = Simulator::Schedule(m_pingInterval+offset, &UwbModuleNodeApp::BroadcastPingPacket, this);
		
	}

	const std::set<Mac64Address> & UwbModuleNodeApp::GetNeighbors() const
	{
		return m_neighbors;
	}


}