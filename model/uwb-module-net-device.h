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

#ifndef UWB_MODULE_NET_DEVICE_H
#define UWB_MODULE_NET_DEVICE_H

#include <ns3/net-device.h>
#include <ns3/spectrum-channel.h>
#include <ns3/mac64-address.h>

namespace ns3
{
	class UwbModuleNetDevice : public NetDevice
	{
	public:
		static TypeId GetTypeId(void);

		UwbModuleNetDevice(void);
		virtual ~UwbModuleNetDevice(void);

		void SetChannel(Ptr<SpectrumChannel> channel);
		void Receive(Ptr<Packet> p, const Address & address);

		//From NetDevice
		virtual void SetIfIndex(const uint32_t index);
		virtual uint32_t GetIfIndex(void) const;
		virtual Ptr<Channel> GetChannel(void) const;
		virtual void SetAddress(Address address);
		virtual Address GetAddress(void) const;
		virtual bool SetMtu(const uint16_t mtu);
		virtual uint16_t GetMtu(void) const;
		virtual bool IsLinkUp(void) const;
		virtual void AddLinkChangeCallback(Callback<void> callback);
		virtual bool IsBroadcast(void) const;
		virtual Address GetBroadcast(void) const;
		virtual bool IsMulticast(void) const;
		virtual Address GetMulticast(Ipv4Address multicastGroup) const;
		virtual Address GetMulticast(Ipv6Address addr) const;
		virtual bool IsBridge(void) const;
		virtual bool IsPointToPoint(void) const;
		virtual bool Send(Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);
		virtual bool SendFrom(Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber);
		virtual Ptr<Node> GetNode(void) const;
		virtual void SetNode(Ptr<Node> node);
		virtual bool NeedsArp(void) const;

		virtual void SetReceiveCallback(NetDevice::ReceiveCallback cb);
		virtual void SetPromiscReceiveCallback(PromiscReceiveCallback cb);
		virtual bool SupportsSendFrom(void) const;

		

	protected:

		virtual void DoDispose(void);
		virtual void DoInitialize(void);

		void LinkUp(void);
		void LinkDown(void);

		void CompleteConfig(void);
	private:

		bool m_configComplete;
		bool m_linkup;

		uint32_t m_ifIndex;
		Ptr<Channel> m_channel;
		Mac64Address m_macAddress;
		Ptr<Node> m_node;

	};
}

#endif