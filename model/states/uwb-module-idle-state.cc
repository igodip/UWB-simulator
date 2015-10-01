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

#include "uwb-module-idle-state.h"
#include <ns3/log.h>
#include <ns3/simulator.h>
#include <ns3/random-variable-stream.h>
#include <ns3/double.h>
#include <ns3/uwb-module-request-state.h>
#include <ns3/uwb-module-drand-state.h>
#include <ns3/uwb-module-grant-state.h>
#include <ns3/abort.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleIdleState");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleIdleState);

	Time UwbModuleIdleState::m_waitTime = MilliSeconds(10.0);
	double UwbModuleIdleState::m_threshold = 0.7;

	UwbModuleIdleState::UwbModuleIdleState(Ptr<UwbModuleDrandState> state)
	{
		NS_LOG_FUNCTION(this << state);

		m_state = state;

		m_urv = CreateObject<UniformRandomVariable>();
		m_urv->SetAttribute("Min", DoubleValue(0.0));
		m_urv->SetAttribute("Max", DoubleValue(1.0));

	}

	TypeId UwbModuleIdleState::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleIdleState")
			.SetParent<UwbModuleAbsDrandState>();


		return tid;
	}

	void UwbModuleIdleState::Start()
	{
		NS_LOG_FUNCTION(this);

		m_event = Simulator::Schedule(m_waitTime, &UwbModuleIdleState::TryRequest, this);


	}

	void UwbModuleIdleState::Receive(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this);

		NS_ABORT_MSG("Not implemented!");

	}

	void UwbModuleIdleState::TryRequest()
	{
		NS_LOG_FUNCTION(this);

		if (m_urv->GetValue() <= m_threshold)
		{
			m_event = Simulator::Schedule(m_waitTime, &UwbModuleIdleState::TryRequest, this);
			return;
		}

		m_state->SetState(CreateObject<UwbModuleRequestState>(m_state));
		m_state->GetState()->Start();

	}

	void UwbModuleIdleState::Request(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		Ptr<UwbModuleGrantState> state = CreateObject<UwbModuleGrantState>(m_state);

		m_state->SetState(state);
		m_state->GetState()->Start();

		state->SendGrant(p);
		
	}

	void UwbModuleIdleState::Release(Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this);

		
		

	}
}