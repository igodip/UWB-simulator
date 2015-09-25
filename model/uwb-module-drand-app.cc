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

#include "uwb-module-drand-app.h"
#include "states/uwb-module-neighbor-discovery-state.h"
#include <ns3/log.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("UwbModuleDrandApp");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleDrandApp);

	TypeId UwbModuleDrandApp::GetTypeId()
	{
		static TypeId tid = TypeId("ns3::UwbModuleDrandApp")
			.SetParent<UwbModuleManager>();

		return tid;
	}

	UwbModuleDrandApp::UwbModuleDrandApp(Ptr<UwbModuleNetDevice> netDevice)
	{
		NS_LOG_FUNCTION(this);

		m_netDevice = netDevice;
		m_state = CreateObject<UwbModuleNeighborDiscoveryState>(this);

	}

	void UwbModuleDrandApp::Receive(Ptr<Packet> packet)
	{
		NS_LOG_FUNCTION(this);
		m_state->Receive(packet);
	}

	void UwbModuleDrandApp::Start()
	{
		NS_LOG_FUNCTION(this);
		m_state->Start();
	}

	void UwbModuleDrandApp::SetState(Ptr<UwbModuleAbstractState> state)
	{
		m_state = state;
	}

	Ptr<UwbModuleNetDevice> UwbModuleDrandApp::GetNetDevice() const
	{
		return m_netDevice;
	}
}