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
#include <ns3/node.h>
#include <ns3/mobility-helper.h>
#include <ns3/uwb-module-helper.h>
#include <ns3/simulator.h>
#include <ns3/packet.h>
#include <ns3/mac64-address.h>
#include <ns3/mobility-model.h>
#include <ns3/uwb-module-net-device.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("UwbModulePhyExample");



void sendPacket(Ptr<Node> n1)
{
	Ptr<Packet> p = Create<Packet>();

	n1->GetDevice(0)->Send(p,Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF"),1);

}

int main(int argc, char ** argv)
{

	LogComponentEnable("UwbModuleNetDevice", LOG_LEVEL_ALL);
	LogComponentEnable("UwbModulePhy", LOG_LEVEL_ALL);
	LogComponentEnable("SingleModelSpectrumChannel", LOG_LEVEL_ALL);
	LogComponentEnable("UwbModulePhyExample",LOG_LEVEL_ALL);

	Ptr<Node> n1, n2;
	n1 = CreateObject<Node>();
	n2 = CreateObject<Node>();

	NodeContainer nodeContainer(n1, n2);

	UwbModuleHelper uwbModuleHelper;
	NetDeviceContainer netDeviceContainer = uwbModuleHelper.InstallNodes(nodeContainer);

	MobilityHelper mobilityHelper;

	Ptr<ListPositionAllocator> listPositionAllocator = CreateObject<ListPositionAllocator>();
	listPositionAllocator->Add(Vector(0, 0, 0));
	listPositionAllocator->Add(Vector(1, 1, 1));

	mobilityHelper.SetPositionAllocator(listPositionAllocator);
	mobilityHelper.SetMobilityModel("ns3::ConstantPositionMobilityModel");

	mobilityHelper.Install(nodeContainer);


	//Simulator
	Time::SetResolution(Time::NS);

	Simulator::Schedule(Seconds(10.0),&sendPacket,n1);
	Simulator::Schedule(Seconds(15.0),&sendPacket, n1);

	Simulator::Stop(Seconds(20.0));

	Simulator::Run();

	Simulator::Destroy();

	return 0;
}