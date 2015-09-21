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
#include <ns3/uwb-module-phy-stat-helper.h>


#include <iostream>
#include <fstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("UwbModuleNdExample");

uint32_t sent_p = 0, receiv_p = 0, dropped_p = 0;

void collision(Ptr<const Packet> p)
{
	
	++dropped_p ;
}

void received(Ptr<const Packet> p)
{
	++receiv_p;
}

void sent(Ptr<const Packet> p)
{
	++sent_p;
}

int main(int argc, char ** argv)
{
	LogComponentEnable("UwbModuleNdExample",LOG_LEVEL_ALL);

	//LogComponentEnable("UwbModulePhyStatHelper", LOG_LEVEL_ALL);
	//LogComponentEnable("UwbModuleNodeApp", LOG_LEVEL_INFO);

	// Creating nodes
	
	Config::SetDefault("ns3::UwbModuleNodeApp::PingInterval", TimeValue(MilliSeconds(5.0)));
	Config::SetDefault("ns3::UwbModuleNodeApp::EndPhase", TimeValue(MilliSeconds(300.0)));

	//File 
	std::ofstream myfile;
	myfile.open("example.csv");
	
	uint32_t max_rounds = 20;

	for (uint32_t k = 1; k <= max_rounds; ++k)
	{

		NS_LOG_INFO("Round " << k << " of " << max_rounds);
		NS_LOG_INFO("Creating nodes");
		NodeContainer nodeContainer;
		nodeContainer.Create(121);


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

		NS_LOG_INFO("Installing node managers");
		UwbModuleHelper uwbModuleHelper;
		uwbModuleHelper.InstallNodes(nodeContainer);

		UwbModulePhyStatHelper uwbModulePhyStatHelper;
		uwbModulePhyStatHelper.attach();

		//Ptr<UwbModuleNetDevice> netDevice1 = DynamicCast<UwbModuleNetDevice>(nodeContainer.Get(12)->GetDevice(0));
		//Ptr<UwbModuleNodeApp> nodeApp1 = DynamicCast<UwbModuleNodeApp>(netDevice1->GetManager());

		//netDevice1->GetPhy()->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&collision));
		//netDevice1->GetPhy()->TraceConnectWithoutContext("PhyRxEnd", MakeCallback(&received));
		//netDevice1->GetPhy()->TraceConnectWithoutContext("PhyTxEnd", MakeCallback(&sent));

		//nodeApp1;

		for (uint32_t i = 0; i < nodeContainer.GetN(); ++i)
		{
			Ptr<UwbModuleNetDevice> netDevice = DynamicCast<UwbModuleNetDevice>(nodeContainer.Get(i)->GetDevice(0));
			Ptr<UwbModuleNodeApp> nodeApp = DynamicCast<UwbModuleNodeApp>(netDevice->GetManager());
			
			netDevice->GetPhy()->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&collision));
			netDevice->GetPhy()->TraceConnectWithoutContext("PhyRxEnd", MakeCallback(&received));
			netDevice->GetPhy()->TraceConnectWithoutContext("PhyTxEnd", MakeCallback(&sent));

			nodeApp->SetAttribute("PingInterval",TimeValue(MilliSeconds(2.0*k)));

		}

		//Running the simulation
		NS_LOG_INFO("Running the simulation");
		Simulator::Run();

		for (uint32_t i = 0; i < nodeContainer.GetN(); ++i)
		{
			Ptr<Node> n = nodeContainer.Get(i);
			Ptr<UwbModuleNetDevice> netDevice = DynamicCast<UwbModuleNetDevice>(n->GetDevice(0));
			Ptr<UwbModuleNodeApp> nodeApp = DynamicCast<UwbModuleNodeApp>(netDevice->GetManager());
			std::set<Mac64Address> addresses = nodeApp->GetNeighbors();

			std::cout << n->GetId() << " ";
			std::cout << n->GetObject<MobilityModel>()->GetPosition() << "  \t" << nodeApp->GetNeighbors().size() << std::endl;

			myfile << nodeApp->GetNeighbors().size() << ",";

			std::set<Mac64Address>::iterator j = addresses.begin();

			for (; j != addresses.end(); ++j)
			{
				//std::cout << *j << " ";
			}
			
		}

		std::cout << " Simulation ended at:" << Simulator::Now() << std::endl;


		myfile << sent_p << "," << dropped_p << "," << receiv_p << Simulator::Now();
		myfile << std::endl;
		
		Simulator::Destroy();

		std::cout << " Packets trasmitted: " << sent_p << std::endl;
		std::cout << " Dropped packets due to collision: " << dropped_p << std::endl;
		std::cout << " Packets received: " << receiv_p << std::endl;
		
		sent_p = 0, receiv_p = 0, dropped_p = 0;
		
		
	}

	myfile.close();

	



}