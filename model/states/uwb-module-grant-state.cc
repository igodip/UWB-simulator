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

#include "uwb-module-grant-state.h"
#include <ns3/log.h>
#include <ns3/uwb-module-drand-app.h>
#include <ns3/uwb-module-drand-protocol.h>
#include <ns3/uwb-module-mac-header.h>
#include <ns3/simulator.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleGrantState");
	
	NS_OBJECT_ENSURE_REGISTERED(UwbModuleGrantState);

	Time UwbModuleGrantState::m_waitTime = MilliSeconds(10.0);

	TypeId UwbModuleGrantState::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleGrantState")
			.SetParent<UwbModuleAbsDrandState>();

		return tid;
	}

	void UwbModuleGrantState::Start()
	{
		NS_LOG_FUNCTION(this);

		m_timeout = Simulator::Schedule(m_waitTime,&UwbModuleGrantState::)
	}

	void UwbModuleGrantState::Receive(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this);
	}

	UwbModuleGrantState::UwbModuleGrantState(Ptr<UwbModuleDrandState> state)
	{
		NS_LOG_FUNCTION(this);

		m_drand = state;
	}

	UwbModuleGrantState::~UwbModuleGrantState()
	{
		NS_LOG_FUNCTION(this);
	}


	void UwbModuleGrantState::Grant(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);
	}

	void UwbModuleGrantState::Fail(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);
	}

	void UwbModuleGrantState::Request(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		SendReject(p);
	}

	void UwbModuleGrantState::Release(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);
	}

	void UwbModuleGrantState::Reject(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);
	}

	void UwbModuleGrantState::SendGrant(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		Ptr<UwbModuleDrandApp> app = DynamicCast<UwbModuleDrandApp>(m_drand->GetManager());

		Address address = app->GetNetDevice()->GetAddress();
		Mac64Address srcAddress = Mac64Address::ConvertFrom(address);

		UwbModuleMacHeader macHeader;
		p->PeekHeader(macHeader);

		Ptr<Packet> packet = UwbModuleDrandProtocol::Get().GenerateReject(srcAddress,macHeader.GetSenderEuid());

		app->GetNetDevice()->Send(p, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 17);
	}

	void UwbModuleGrantState::SendReject(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		Ptr<UwbModuleDrandApp> app = DynamicCast<UwbModuleDrandApp>(m_drand->GetManager());

		Address address = app->GetNetDevice()->GetAddress();
		Mac64Address srcAddress = Mac64Address::ConvertFrom(address);

		UwbModuleMacHeader macHeader;
		p->PeekHeader(macHeader);

		Ptr<Packet> packet = UwbModuleDrandProtocol::Get().GenerateReject(srcAddress, macHeader.GetSenderEuid());

		app->GetNetDevice()->Send(packet, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 17);

	}

	void UwbModuleGrantState::Timeout()
	{
		NS_LOG_FUNCTION(this);

	}
}