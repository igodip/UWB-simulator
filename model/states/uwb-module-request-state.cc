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

#include "uwb-module-request-state.h"
#include <ns3/double.h>
#include <ns3/log.h>
#include <ns3/simulator.h>
#include <ns3/uwb-module-drand-app.h>
#include <ns3/uwb-module-drand-protocol.h>
#include <ns3/uwb-module-idle-state.h>
#include <ns3/nstime.h>
#include <ns3/uwb-module-mac-header.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleRequestState");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleRequestState);

	Time UwbModuleRequestState::m_waiting = MilliSeconds(10.0);

	TypeId UwbModuleRequestState::GetTypeId()
	{
		NS_LOG_FUNCTION_NOARGS();

		static TypeId tid = TypeId("ns3::UwbModuleReleaseState")
			.SetParent<UwbModuleAbsDrandState>();

		return tid;
	}


	void UwbModuleRequestState::Start()
	{
		NS_LOG_FUNCTION(this);

		//Mando la richiesta
		SendRequest();

	}

	void UwbModuleRequestState::Receive(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		//


	}

	UwbModuleRequestState::UwbModuleRequestState(Ptr<UwbModuleDrandState> state)
	{
		NS_LOG_FUNCTION(this);

		m_rand = CreateObject<UniformRandomVariable>();
		m_rand->SetAttribute("Min", DoubleValue(0.0));
		m_rand->SetAttribute("Max", DoubleValue(1.0));

		m_drand = state;

	}

	UwbModuleRequestState::~UwbModuleRequestState()
	{
		NS_LOG_FUNCTION(this);



	}

	void UwbModuleRequestState::SendRequest()
	{
		NS_LOG_FUNCTION(this);

		Ptr<UwbModuleDrandApp> app = DynamicCast<UwbModuleDrandApp>(m_drand->GetManager());

		Address address = app->GetNetDevice()->GetAddress();
		Mac64Address srcAddress = Mac64Address::ConvertFrom(address);

		Ptr<Packet> packet = UwbModuleDrandProtocol::Get().GenerateRequest(srcAddress);

		app->GetNetDevice()->Send(packet, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"),17);

		m_evt =  Simulator::Schedule(m_waiting, &UwbModuleRequestState::Timeout, this);

	}


	void UwbModuleRequestState::Reject(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this);

		//Reject

		//Stop timeout

	}

	void UwbModuleRequestState::Grant(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this);

		//Grant

		//Reset Time out every

	}

	void UwbModuleRequestState::Request(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this);


	}

	void UwbModuleRequestState::Timeout(void)
	{
		NS_LOG_FUNCTION(this);

		SendFail();

		Ptr<UwbModuleAbsDrandState> state = CreateObject<UwbModuleIdleState>(m_drand);

		m_drand->SetState(state);
		state->Start();

	}

	void UwbModuleRequestState::SendFail()
	{
		NS_LOG_FUNCTION(this);

		Ptr<UwbModuleDrandApp> app = DynamicCast<UwbModuleDrandApp>(m_drand->GetManager());

		Address address = app->GetNetDevice()->GetAddress();
		Mac64Address srcAddress = Mac64Address::ConvertFrom(address);

		Ptr<Packet> packet = UwbModuleDrandProtocol::Get().GenerateFail(srcAddress);

		app->GetNetDevice()->Send(packet, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 17);

	}

	void UwbModuleRequestState::SendReject(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		Ptr<UwbModuleDrandApp> app = DynamicCast<UwbModuleDrandApp>(m_drand->GetManager());

		Address address = app->GetNetDevice()->GetAddress();
		Mac64Address srcAddress = Mac64Address::ConvertFrom(address);

		UwbModuleMacHeader macHeader;
		p->PeekHeader(macHeader);

		Ptr<Packet> packet = UwbModuleDrandProtocol::Get().GenerateReject(srcAddress,);

		app->GetNetDevice()->Send(packet, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 17);
	}



}