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

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include <ns3/uwb-module-helper.h>
#include "ns3/log.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("UwbModuleExample");

// Micron example

void sendPacket(Ptr<Node> n1)
{
	Ptr<Packet> p = Create<Packet>();

	n1->GetDevice(0)->Send(p, Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"), 1);

}

int main(int argc, char** argv)
{
	//LogComponentEnable("UwbModuleExample", LOG_LEVEL_ALL);
	//LogComponentEnable("UwbModulePhy", LOG_LEVEL_ALL);
	
	Time::SetResolution(Time::NS);

	NodeContainer nodesContainer;
	NodeContainer targetsContainer;

	nodesContainer.Create(200);
	targetsContainer.Create(2000);

	UwbModuleHelper uwbModuleHelper;
	uwbModuleHelper.Install(nodesContainer);
	uwbModuleHelper.Install(targetsContainer);

	// Nodes mobility

	MobilityHelper nodesMobility;

	nodesMobility.SetPositionAllocator("ns3::GridPositionAllocator",
		"MinX", DoubleValue(-100.0),
		"MinY", DoubleValue(-100.0),
		"DeltaX", DoubleValue(5.0),
		"DeltaY", DoubleValue(20.0),
		"GridWidth", UintegerValue(40),
		"LayoutType", StringValue("RowFirst"));

	nodesMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

	nodesMobility.Install(nodesContainer);

	// Targets mobility

	MobilityHelper targetsMobility;

	targetsMobility.SetPositionAllocator("ns3::RandomRectanglePositionAllocator",
		"X", StringValue("ns3::UniformRandomVariable[Min=-100.0|Max=100.0]"),
		"Y", StringValue("ns3::UniformRandomVariable[Min=-100.0|Max=100.0]"));

	targetsMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

	AsciiTraceHelper asciiTraceHelper;
	//ascii
	//uwbModuleHelper.EnableAsciiAll(ascii.CreateFileStream("trace.tr"));

	Simulator::Stop(Seconds(20.0));
	for (uint32_t i = 0; i < 10; ++i)
	{
		Simulator::Schedule(Seconds(10.0), &sendPacket, nodesContainer.Get(i));
	}

	Simulator::Run();

	Simulator::Destroy();

	return 0;
}