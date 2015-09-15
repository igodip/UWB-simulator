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
#include <ns3/uwb-module-phy.h>
#include <ns3/isotropic-antenna-model.h>
#include <ns3/packet.h>
#include <ns3/spectrum-value.h>

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
		m_phy = CreateObject<UwbModulePhy>();

		Ptr<AntennaModel> antenna = CreateObject<IsotropicAntennaModel>();
		//antenna->SetAttribute()
		
		m_phy->SetAntenna(antenna);
		m_phy->SetDevice(this);
	}

	UwbModuleNetDevice::~UwbModuleNetDevice()
	{
		NS_LOG_FUNCTION_NOARGS();

	}

	TypeId UwbModuleNetDevice::GetTypeId(void)
	{
		NS_LOG_FUNCTION_NOARGS();

		static TypeId tid = TypeId("ns3::UwbModuleNetDevice").
			AddConstructor<UwbModuleNetDevice>();

		return tid;
	}

	void UwbModuleNetDevice::DoInitialize(void)
	{
		NS_LOG_FUNCTION(this);

		NetDevice::DoInitialize();
	}

	void UwbModuleNetDevice::DoDispose(void)
	{
		m_phy->Dispose();
		
		m_node = 0;
		m_phy = 0;
		

	}

	void UwbModuleNetDevice::SetReceiveCallback(NetDevice::ReceiveCallback cb) 
	{
		return;
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
		return m_phy->GetChannel();
	}

	void UwbModuleNetDevice::SetChannel(Ptr<SpectrumChannel> c)
	{
		NS_LOG_FUNCTION(this << c);

		m_phy->SetChannel(c);
		c->AddRx(m_phy);
	}

	bool UwbModuleNetDevice::Send(Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber)
	{
		NS_LOG_FUNCTION(this << &packet << dest << protocolNumber);

		Ptr<UwbModuleSpectrumSignalParameters> spectrumSignalParameters = Create<UwbModuleSpectrumSignalParameters>();

		spectrumSignalParameters->duration = MicroSeconds(200.0);
		spectrumSignalParameters->psd = m_spectrumValueHelper.CreateTxPowerSpectralDensity(0, 1);
		spectrumSignalParameters->packetBurst = CreateObject<PacketBurst>();
		spectrumSignalParameters->packetBurst->AddPacket(packet);
		spectrumSignalParameters->txAntenna = m_phy->GetRxAntenna();
		spectrumSignalParameters->txPhy = m_phy;

		m_phy->StartTx(spectrumSignalParameters);

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
		//Mac64Address mac64Address = dynamic_cast
		//Verify cast
	}


	void UwbModuleNetDevice::AddLinkChangeCallback(Callback<void> callback)
	{
		NS_LOG_FUNCTION(this);
	}
	
	bool UwbModuleNetDevice::IsBroadcast(void) const
	{
		NS_LOG_FUNCTION(this);
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

	void UwbModuleNetDevice::SetPhy(Ptr<UwbModulePhy> phy)
	{
		m_phy = phy;
	}
	
	Ptr<UwbModulePhy> UwbModuleNetDevice::GetPhy() const
	{
		return m_phy;
	}

}