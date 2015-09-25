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

#include "uwb-module-drand-state.h"
#include "uwb-module-idle-state.h"
#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleDrandState");

	TypeId UwbModuleDrandState::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleDrandState")
			.SetParent<UwbModuleAbstractState>();

		m_

			return tid;
	}

	UwbModuleDrandState::UwbModuleDrandState(Ptr<UwbModuleManager> manager)
	{
		NS_LOG_FUNCTION(this);

		m_state = CreateObject<UwbModuleIdleState>(this);
		m_manager = manager;

	}

	UwbModuleDrandState::~UwbModuleDrandState()
	{
		NS_LOG_FUNCTION(this);
		m_state->Dispose();
	}

	void  UwbModuleDrandState::Start()
	{
		NS_LOG_FUNCTION(this);
		m_state->Start();
	}

	void UwbModuleDrandState::Receive(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this);
		m_state->Receive(p);
	}

	void UwbModuleDrandState::SetState(Ptr<UwbModuleAbstractState> state)
	{
		NS_LOG_FUNCTION(this << state);
		m_state = state;
	}

	Ptr<UwbModuleAbstractState> UwbModuleDrandState::GetState() const
	{
		NS_LOG_FUNCTION(this);
		return m_state;
	}

	void UwbModuleDrandState::SetNeighbors(const std::set<Mac64Address> addresses)
	{
		m_addresses = addresses;
	}

	const std::set<Mac64Address> & UwbModuleDrandState::GetNeighbors() const
	{
		return m_addresses;
	}


	const std::map<uint32_t, Mac64Address> UwbModuleDrandState::getTurns() const
	{
		return m_turns;
	}

	void UwbModuleDrandState::setTurn(uint32_t turn, Mac64Address address)
	{
		//m_turns.insert(turn, address);
	}

	uint32_t UwbModuleDrandState::getFirstTurn() const
	{
		return m_firstTurn;
	}

}