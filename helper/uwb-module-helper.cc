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
#include "ns3/uwb-module-helper.h"
#include "ns3/uwb-module-net-device.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/log.h"


namespace ns3 {
	
	NS_LOG_COMPONENT_DEFINE("UwbModuleHelper");

	UwbModuleHelper::UwbModuleHelper()
	{

	}

	NetDeviceContainer UwbModuleHelper::Install(NodeContainer c)
	{
		NS_LOG_FUNCTION(this);

		NetDeviceContainer devs;

		for (uint32_t i = 0; i < c.GetN(); ++i)
		{
			

			Ptr<Node> node = c.Get(i);
			NS_LOG_LOGIC("**** Install 6LoWPAN on node " << node->GetId());

			Ptr<UwbModuleNetDevice> dev = m_deviceFactory.Create<UwbModuleNetDevice>();
			devs.Add(dev);
			node->AddDevice(dev);
			
		}
		return devs;
	}

	int64_t AssignStreams(NetDeviceContainer c, int64_t stream)
	{
		return 0;
	}


}

