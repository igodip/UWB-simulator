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
#include <ns3/uwb-module-drand-protocol.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleDrandState");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleDrandState);

	TypeId UwbModuleDrandState::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleDrandState")
			.SetParent<UwbModuleAbstractState>();

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

		UwbModuleDrandPacketType packetType = UwbModuleDrandProtocol::Get().GetPacketType(p);

		NS_LOG_INFO(packetType);

		switch (packetType)
		{
		case UWB_MODULE_DRAND_REQUEST:
			m_state->Request(p);
			break;
			
		case UWB_MODULE_DRAND_FAIL:
			m_state->Fail(p);
			break;

		case UWB_MODULE_DRAND_GRANT:
			m_state->Grant(p);
			break;

		case UWB_MODULE_DRAND_REJECT:
			m_state->Reject(p);
			break;

		case UWB_MODULE_DRAND_RELEASE:
			m_state->Release(p);
			break;

		default:

			break;
		}

	}

	void UwbModuleDrandState::SetState(Ptr<UwbModuleAbsDrandState> state)
	{
		NS_LOG_FUNCTION(this << state);

		m_state = state;
	}

	Ptr<UwbModuleAbsDrandState> UwbModuleDrandState::GetState() const
	{
		NS_LOG_FUNCTION(this);

		return m_state;
	}

	void UwbModuleDrandState::SetNeighbors(const std::set<Mac64Address> addresses)
	{
		NS_LOG_FUNCTION(this);

		m_addresses = addresses;
	}

	const std::set<Mac64Address> & UwbModuleDrandState::GetNeighbors() const
	{
		NS_LOG_FUNCTION(this);

		return m_addresses;
	}


	const std::map<uint32_t, Mac64Address> UwbModuleDrandState::getTurns() const
	{
		NS_LOG_FUNCTION(this);

		return m_turns;
	}

	void UwbModuleDrandState::setTurn(uint32_t turn, Mac64Address address)
	{
		NS_LOG_FUNCTION(this);

		//m_turns.insert(turn, address);
	}

	Ptr<UwbModuleManager> UwbModuleDrandState::GetManager() const
	{
		NS_LOG_FUNCTION(this);

		return m_manager;
	}

	void UwbModuleDrandState::SetManager(Ptr<UwbModuleManager> manager)
	{
		NS_LOG_FUNCTION(this<< manager);

		m_manager = manager;
	}

}