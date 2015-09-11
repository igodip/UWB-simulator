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
*
*
*
*/

#include "uwb-module-net-device.h"
#include <ns3/node.h>
#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleNetDevice");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleNetDevice);

	UwbModuleNetDevice::UwbModuleNetDevice() :
		m_configComplete(false)
	{
		NS_LOG_FUNCTION_NOARGS();

		m_linkup = true;
		m_macAddress = Mac64Address::Allocate();
	}

	UwbModuleNetDevice::~UwbModuleNetDevice()
	{
		NS_LOG_FUNCTION_NOARGS();

	}

	TypeId UwbModuleNetDevice::GetTypeId(void)
	{
		NS_LOG_FUNCTION_NOARGS();

		static TypeId tid = TypeId("ns3::UwbModuleNetDevice");

		return tid;
	}

	void UwbModuleNetDevice::DoInitialize(void)
	{
		NS_LOG_FUNCTION(this);

		NetDevice::DoInitialize();
	}

	void UwbModuleNetDevice::DoDispose(void)
	{
		m_node = 0;
	}

	void UwbModuleNetDevice::SetReceiveCallback(NetDevice::ReceiveCallback cb) 
	{
		
	}

	void UwbModuleNetDevice::SetPromiscReceiveCallback(PromiscReceiveCallback cb)
	{
		return;
	}
	
	bool UwbModuleNetDevice::SupportsSendFrom() const
	{
		return true;
	}


	Ptr<Channel> UwbModuleNetDevice::GetChannel(void) const
	{
		NS_LOG_FUNCTION_NOARGS();
		return m_channel;
	}

	void UwbModuleNetDevice::SetChannel(Ptr<SpectrumChannel> c)
	{
		NS_LOG_FUNCTION_NOARGS();
		m_channel = c;
	}

	bool UwbModuleNetDevice::Send(Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber)
	{
		NS_LOG_FUNCTION_NOARGS();
		return true;
	}

	void UwbModuleNetDevice::SetIfIndex(const uint32_t index)
	{
		NS_LOG_FUNCTION(this << index);
		m_ifIndex = index;
	}

	uint32_t UwbModuleNetDevice::GetIfIndex(void) const
	{
		NS_LOG_FUNCTION_NOARGS();
		return m_ifIndex;
	}

	Address UwbModuleNetDevice::GetAddress(void) const
	{
		NS_LOG_FUNCTION_NOARGS();
		return m_macAddress;
	}

	bool UwbModuleNetDevice::SetMtu(const uint16_t mtu)
	{
		NS_LOG_FUNCTION(this << mtu);
		return false;
	}
	uint16_t UwbModuleNetDevice::GetMtu(void) const
	{
		NS_LOG_FUNCTION_NOARGS();
		return 128;
	}

	bool UwbModuleNetDevice::IsLinkUp(void) const
	{
		NS_LOG_FUNCTION_NOARGS();
		return m_linkup;
	}

	void UwbModuleNetDevice::SetAddress(Address address)
	{

	}


	void UwbModuleNetDevice::AddLinkChangeCallback(Callback<void> callback)
	{
		NS_LOG_FUNCTION(this);
	}
	
	bool UwbModuleNetDevice::IsBroadcast(void) const
	{
		NS_LOG_FUNCTION_NOARGS();
		return false;
	}

	Address UwbModuleNetDevice::GetBroadcast(void) const
	{
		NS_LOG_FUNCTION_NOARGS();
		return Mac64Address("FF:FF:FF:FF:FF:FF:FF:FF");
	}

	bool UwbModuleNetDevice::IsMulticast(void) const
	{
		return false;
	}

	Address UwbModuleNetDevice::GetMulticast(Ipv4Address multicastGroup) const
	{
		return Mac64Address();
	}

	Address UwbModuleNetDevice::GetMulticast(Ipv6Address addr) const
	{
		return Mac64Address();
	}

	bool UwbModuleNetDevice::IsBridge(void) const
	{
		return false;
	}

	bool UwbModuleNetDevice::IsPointToPoint(void) const
	{
		return false;
	}

	bool UwbModuleNetDevice::SendFrom(Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber)
	{
		return false;
	}

	Ptr<Node> UwbModuleNetDevice::GetNode(void) const
	{
		return m_node;
	}

	void UwbModuleNetDevice::SetNode(Ptr<Node> node)
	{
		m_node = node;
	}

	bool UwbModuleNetDevice::NeedsArp(void) const
	{
		return false;
	}

}