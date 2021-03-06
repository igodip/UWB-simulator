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
#include "uwb-module-helper.h"
#include <ns3/uwb-module-net-device.h>
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/log.h"

#include <ns3/single-model-spectrum-channel.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/propagation-delay-model.h>
#include <ns3/double.h>
#include <ns3/uwb-module-node-app.h>
#include <ns3/uwb-module-le-app.h>
#include <ns3/uwb-module-ndle-app.h>
#include <ns3/uwb-module-drand-app.h>
/**
Ghassemzadeh, Saeed S., et al. "A statistical path loss model for in-home UWB channels."
Ultra Wideband Systems and Technologies, 2002. 
Digest of Papers. 2002 IEEE Conference on. IEEE, 2002.
*/

namespace ns3 {
	
	NS_LOG_COMPONENT_DEFINE("UwbModuleHelper");

	UwbModuleHelper::UwbModuleHelper()
	{
		NS_LOG_FUNCTION(this);

		m_channel = CreateObject<SingleModelSpectrumChannel>();
		m_channel->SetAttribute("MaxLossDb", DoubleValue(70));

		Ptr<LogDistancePropagationLossModel> propagationModel = CreateObject<LogDistancePropagationLossModel>();
		propagationModel->SetAttribute("Exponent", DoubleValue(1.7));
		m_channel->AddPropagationLossModel(propagationModel);

		Ptr<ConstantSpeedPropagationDelayModel> delayModel = CreateObject<ConstantSpeedPropagationDelayModel>();

		m_channel->SetPropagationDelayModel(delayModel);
		m_deviceFactory.SetTypeId("ns3::UwbModuleNetDevice");

	}

	NetDeviceContainer UwbModuleHelper::InstallNodes(NodeContainer c)
	{
		NS_LOG_FUNCTION(this);

		NetDeviceContainer devs;

		for (uint32_t i = 0; i < c.GetN(); ++i)
		{
			
			Ptr<Node> node = c.Get(i);
			NS_LOG_LOGIC("Installing node netDevice on node " << node->GetId());
			
			Ptr<UwbModuleNetDevice> dev = Create<UwbModuleNetDevice>();
			Ptr<UwbModuleNodeApp> nodeApp = CreateObject<UwbModuleNodeApp>(dev);
			
			devs.Add(dev);
			node->AddDevice(dev);
			dev->SetNode(node);

			//NetDevice::ReceiveCallback receiveCallback = MakeCallback<

			dev->SetChannel(m_channel);
			dev->SetManager(nodeApp);
			
			nodeApp->Start();
			
		}

		return devs;
	}


	NetDeviceContainer UwbModuleHelper::InstallLeNodes(NodeContainer c)
	{
		NS_LOG_FUNCTION(this);

		NetDeviceContainer devs;

		for (uint32_t i = 0; i < c.GetN(); ++i)
		{

			Ptr<Node> node = c.Get(i);
			NS_LOG_LOGIC("Installing node netDevice on node " << node->GetId());

			Ptr<UwbModuleNetDevice> dev = Create<UwbModuleNetDevice>();
			Ptr<UwbModuleLeApp> nodeApp = CreateObject<UwbModuleLeApp>(dev);

			devs.Add(dev);
			node->AddDevice(dev);
			dev->SetNode(node);

			//NetDevice::ReceiveCallback receiveCallback = MakeCallback<

			dev->SetChannel(m_channel);
			dev->SetManager(nodeApp);

			nodeApp->Start();

		}

		return devs;
	}


	NetDeviceContainer UwbModuleHelper::InstallTargets(NodeContainer c)
	{
		NS_LOG_FUNCTION(this);

		NetDeviceContainer devs;

		for (uint32_t i = 0; i < c.GetN(); ++i)
		{

			Ptr<Node> node = c.Get(i);
			NS_LOG_LOGIC("Installing netDevice on node " << node->GetId());

			Ptr<UwbModuleNetDevice> dev = Create<UwbModuleNetDevice>();

			devs.Add(dev);
			node->AddDevice(dev);
			dev->SetChannel(m_channel);


		}

		return devs;
	}

	NetDeviceContainer UwbModuleHelper::InstallNdleNodes(NodeContainer c)
	{
		NS_LOG_FUNCTION(this);

		NetDeviceContainer devs;


		for (uint32_t i = 0; i < c.GetN(); ++i)
		{

			Ptr<Node> node = c.Get(i);
			NS_LOG_LOGIC("Installing node netDevice on node " << node->GetId());

			Ptr<UwbModuleNetDevice> dev = Create<UwbModuleNetDevice>();
			Ptr<UwbModuleNdleApp> nodeApp = CreateObject<UwbModuleNdleApp>(dev);

			devs.Add(dev);
			node->AddDevice(dev);
			dev->SetNode(node);

			//NetDevice::ReceiveCallback receiveCallback = MakeCallback<

			dev->SetChannel(m_channel);
			dev->SetManager(nodeApp);

			nodeApp->Start();

		}

		return devs;
	}


	NetDeviceContainer UwbModuleHelper::InstallDrandNodes(NodeContainer c)
	{
		NS_LOG_FUNCTION(this);

		NetDeviceContainer devs;


		for (uint32_t i = 0; i < c.GetN(); ++i)
		{

			Ptr<Node> node = c.Get(i);
			NS_LOG_LOGIC("Installing node netDevice on node " << node->GetId());

			Ptr<UwbModuleNetDevice> dev = Create<UwbModuleNetDevice>();
			Ptr<UwbModuleDrandApp> nodeApp = CreateObject<UwbModuleDrandApp>(dev);

			devs.Add(dev);
			node->AddDevice(dev);
			dev->SetNode(node);

			//NetDevice::ReceiveCallback receiveCallback = MakeCallback<

			dev->SetChannel(m_channel);
			dev->SetManager(nodeApp);

			nodeApp->Start();

		}

		return devs;
	}

	int64_t UwbModuleHelper::AssignStreams(NetDeviceContainer c, int64_t stream)
	{
		NS_LOG_FUNCTION(this);

		return 0;
	}


}

