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

#include "uwb-module-release-state.h"
#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleReleaseState");
	UwbModuleReleaseState::UwbModuleReleaseState(Ptr<UwbModuleDrandState> state)
	{
		NS_LOG_FUNCTION(this << state);
	}

	TypeId UwbModuleReleaseState::GetTypeId()
	{
		NS_LOG_FUNCTION_NOARGS();

		static TypeId tid = TypeId("ns3::UwbModuleReleaseState")
			.SetParent<UwbModuleAbstractState>();

		return tid;
	}

	void UwbModuleReleaseState::Start()
	{
		NS_LOG_FUNCTION(this);

		//Send release packet

	}

	void UwbModuleReleaseState::Receive(Ptr<Packet> p)
	{
		NS_LOG_FUNCTION(this << p);

		// Wait for receive packets
	}

}