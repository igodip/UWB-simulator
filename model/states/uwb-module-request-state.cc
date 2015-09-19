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


namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleRequestState");

	TypeId UwbModuleRequestState::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleReleaseState")
			.SetParent<UwbModuleAbstractState>();

		return tid;
	}


	void UwbModuleRequestState::Start()
	{
		NS_LOG_FUNCTION(this);

	}

	void UwbModuleRequestState::Receive(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

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



	}

}