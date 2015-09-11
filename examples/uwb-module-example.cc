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
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/log.h"
#include "ns3/lr-wpan-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("PROTO_SIM_COMPONENT");

int main(int argc, char** argv)
{



	Time::SetResolution(Time::NS);

	NodeContainer nodesContainer;
	NodeContainer targetsContainer;

	nodesContainer.Create(400);
	targetsContainer.Create(8000);

	LrWpanHelper lrWpanHelper;

	lrWpanHelper.Install(nodesContainer);

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
		"X", StringValue("ns3::UniformRandomVariable[Min=-100.0|Max=100]"),
		"Y", StringValue("ns3::UniformRandomVariable[Min=-100|Max=100]"));

	targetsMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

	AsciiTraceHelper ascii;
	lrWpanHelper.EnableAsciiAll(ascii.CreateFileStream("trace.tr"));

	Simulator::Stop(Seconds(20.0));

	Simulator::Run();

	Simulator::Destroy();

	return 0;
}