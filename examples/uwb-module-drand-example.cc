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

#include <ns3/log.h>
#include <ns3/mobility-helper.h>
#include <ns3/node-container.h>
#include <ns3/string.h>
#include <ns3/double.h>
#include <ns3/uinteger.h>
#include <ns3/simulator.h>
#include <ns3/uwb-module-helper.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("UwbModuleDrandExample");

int main(int argc, char** argv)
{
	LogComponentEnable("UwbModuleDrandExample", LOG_LEVEL_ALL);
	LogComponentEnable("UwbModuleDrandApp", LOG_LEVEL_ALL);
	LogComponentEnable("UwbModuleIdleState", LOG_LEVEL_ALL);
	LogComponentEnable("UwbModuleDrandState", LOG_LEVEL_ALL);
	LogComponentEnable("UwbModuleRequestState", LOG_LEVEL_ALL);

	NS_LOG_INFO("Creating nodes");
	NodeContainer nodeContainer;
	nodeContainer.Create(2);

	NS_LOG_INFO("Placing nodes");
	MobilityHelper mobilityHelper;
	mobilityHelper.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityHelper.SetPositionAllocator("ns3::GridPositionAllocator",
		"MinX", DoubleValue(-50.0),
		"MinY", DoubleValue(-50.0),
		"DeltaX", DoubleValue(10.0),
		"DeltaY", DoubleValue(10.0),
		"GridWidth", UintegerValue(11),
		"LayoutType", StringValue("RowFirst"));
	
	mobilityHelper.Install(nodeContainer);

	NS_LOG_INFO("Install drand on nodes");
	UwbModuleHelper uwbModuleHelper;
	uwbModuleHelper.InstallDrandNodes(nodeContainer);

	NS_LOG_INFO("Running the simulation");
	Simulator::Run();

	Simulator::Destroy();

}