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
#include <ns3/log.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("UwBModuleRangingExample");

int main(int argc, char** argv)
{

	Ptr<Node> node = CreateObject<Node>();
	Ptr<Node> target = CreateObject<Node>();

	NodeContainer nodesContainer(node);
	NodeContainer targetsContainer(target);

	MobilityHelper nodeMobility;
	nodeMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	//nodeMobility.SetPositionAllocator()

	nodeMobility.Install(nodesContainer);

	MobilityHelper targetMobility;
	//targetMobility.SetMobilityModel()
	//targetMobility.SetPositionAllocator();

	//Simulation
	Time::SetResolution(Time::NS);
	Simulator::Stop(Seconds(20.0));

	Simulator::Run();

	Simulator::Destroy();

	return 0;
}