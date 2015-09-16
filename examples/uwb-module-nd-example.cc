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

#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/applications-module.h>
#include <ns3/mobility-module.h>
#include <ns3/uwb-module-helper.h>
#include <ns3/node-container.h>
#include <ns3/uwb-module-net-device.h>
#include <ns3/log.h>
#include <ns3/uwb-module-node-app.h>

#include <iostream>

using namespace ns3;

int main(int argc, char ** argv)
{

	//LogComponentEnable("UwbModuleNodeApp", LOG_LEVEL_INFO);
	//LogComponentEnable("UwbModulePhy", LOG_LEVEL_INFO);

	// Creating nodes
	NodeContainer nodeContainer;
	nodeContainer.Create(25);

	MobilityHelper mobilityHelper;
	mobilityHelper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityHelper.SetPositionAllocator("ns3::GridPositionAllocator",
		"MinX", DoubleValue(-20.0),
		"MinY", DoubleValue(-20.0),
		"DeltaX", DoubleValue(10.0),
		"DeltaY", DoubleValue(10.0),
		"GridWidth", UintegerValue(5),
		"LayoutType", StringValue("RowFirst"));
	mobilityHelper.Install(nodeContainer);

	UwbModuleHelper uwbModuleHelper;
	uwbModuleHelper.InstallNodes(nodeContainer);

	//Running the simulation
	Simulator::Run();

	for (uint32_t i = 0; i < nodeContainer.GetN(); ++i)
	{
		Ptr<Node> n = nodeContainer.Get(i);
		Ptr<UwbModuleNetDevice> netDevice = DynamicCast<UwbModuleNetDevice>(n->GetDevice(0));
		Ptr<UwbModuleNodeApp> nodeApp = DynamicCast<UwbModuleNodeApp>(netDevice->GetManager());

		std::cout <<n->GetObject<MobilityModel>()->GetPosition()<<"  \t" <<nodeApp->GetNeighbors().size() << std::endl;

	}

	Simulator::Destroy();



}