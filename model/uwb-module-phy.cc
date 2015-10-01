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

#include "uwb-module-phy.h"

#include <ns3/log.h>
#include <ns3/simulator.h>
#include <ns3/uwb-module-net-device.h>
#include <ns3/packet.h>
#include <ns3/mobility-model.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("UwbModulePhy");

	NS_OBJECT_ENSURE_REGISTERED(UwbModulePhy);

	void UwbModulePhy::DoDispose(void)
	{
		NS_LOG_FUNCTION(this);
	}

	void UwbModulePhy::DoInitialize()
	{
		NS_LOG_FUNCTION(this);
		//
	}

	TypeId UwbModulePhy::GetTypeId(void)
	{

		static TypeId tid = TypeId("ns3::UwbModulePhy")
			.SetParent<SpectrumPhy>()
			.AddConstructor<UwbModulePhy>().
			AddTraceSource("PhyRxBegin",
			"Trace source indicating a packet has begun"
			"being received from the channel medium by the device",
			MakeTraceSourceAccessor(&UwbModulePhy::m_phyRxBeginTrace),
			"ns3::Packet::TracedCallback").
			AddTraceSource("PhyRxEnd",
			"Trace source indicating a packet has been "
			"completely received from the channel medium"
			"by the device",
			MakeTraceSourceAccessor(&UwbModulePhy::m_phyRxEndTrace),
			"ns3::Packet::TracedCallback").
			AddTraceSource("PhyTxBegin",
			"Trace source indicating a packet has begun "
			"being sent to the channel medium"
			"by the device",
			MakeTraceSourceAccessor(&UwbModulePhy::m_phyTxBeginTrace),
			"ns3::Packet::TracedCallback").
			AddTraceSource("PhyTxEnd",
			"Trace source indicating a packet has been"
			"completely sent to the channel medium"
			"by the device",
			MakeTraceSourceAccessor(&UwbModulePhy::m_phyTxEndTrace),
			"ns3::Packet::TracedCallback").
			AddTraceSource("PhyTxDrop",
			"Trace source indicating a packet has been"
			"dropped by the device during transmission",
			MakeTraceSourceAccessor(&UwbModulePhy::m_phyTxDropTrace),
			"ns3::Packet::TracedCallback").
			AddTraceSource("PhyRxDrop",
			"Trace source indicating a packet has been"
			"dropped by the device during reception",
			MakeTraceSourceAccessor(&UwbModulePhy::m_phyRxDropTrace),
			"ns3::Packet::TracedCallback");;

		return tid;
	}


	void UwbModulePhy::SetChannel(Ptr<SpectrumChannel> c)
	{
		NS_LOG_FUNCTION(this << &c);
		m_channel = c;
	}

	Ptr<SpectrumChannel> UwbModulePhy::GetChannel() const
	{
		NS_LOG_FUNCTION(this);
		return m_channel;
	}

	Ptr<AntennaModel> UwbModulePhy::GetRxAntenna()
	{
		NS_LOG_FUNCTION(this);
		return m_antenna;
	}

	void UwbModulePhy::SetAntenna(Ptr<AntennaModel> a)
	{
		NS_LOG_FUNCTION(this << a);
		m_antenna = a;
	}

	void UwbModulePhy::StartRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		Ptr<UwbModuleSpectrumSignalParameters> uwbRxParams = DynamicCast<UwbModuleSpectrumSignalParameters>(params);

		// If is busy receiving discard a packet
		if (m_busy.IsRunning())
		{
			NS_LOG_INFO("Busy receiving another packet, packet discarded");
			m_phyRxDropTrace(uwbRxParams->packetBurst->GetPackets().front());
			return;
		}

		// It isn't an our packet
		if (uwbRxParams == 0)
		{
			m_busy = Simulator::Schedule(params->duration, &UwbModulePhy::EndRx, this, params);
			return;
		}


			

		UwbModuleSpectrumSignalParameters psdHelper;

		Ptr<Packet> p = (uwbRxParams->packetBurst->GetPackets()).front();
		m_phyRxBeginTrace(p);

		m_busy = Simulator::Schedule(params->duration, &UwbModulePhy::EndRx, this, params);
	}

	void UwbModulePhy::EndRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);

		Ptr<UwbModuleSpectrumSignalParameters> uwbRxParams = DynamicCast<UwbModuleSpectrumSignalParameters>(params);
		
		if (uwbRxParams == 0)
		{
			return;
		}
		Ptr<Packet> p = (uwbRxParams->packetBurst->GetPackets()).front();
		m_phyRxEndTrace(p);

		Ptr < UwbModuleNetDevice > netDevice = DynamicCast<UwbModuleNetDevice>(m_netDevice);
		netDevice->Receive(uwbRxParams->packetBurst->GetPackets().front(), Mac64Address());
	}

	void UwbModulePhy::StartTx(Ptr<UwbModuleSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
		
		if (m_busy.IsRunning())
		{
			NS_LOG_INFO("Busy receiving / trasmitting");
		}

		m_channel->StartTx(params);
		Ptr<Packet> p = (params->packetBurst->GetPackets()).front();
		m_phyTxBeginTrace(p);

		m_busy = Simulator::Schedule(params->duration, &UwbModulePhy::EndTx, this, params);
	}

	void UwbModulePhy::EndTx(Ptr<UwbModuleSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
		Ptr<Packet> p = (params->packetBurst->GetPackets()).front();
		m_phyTxEndTrace(p);
	}

	void UwbModulePhy::SetMobility(Ptr<MobilityModel> m)
	{
		NS_LOG_FUNCTION(this << m);
		//(DynamicCast<UwbModuleNetDevice>(m_netDevice))->GetNode()->AggregateObject<Mobili
	}


	Ptr<MobilityModel> UwbModulePhy::GetMobility()
	{
		NS_LOG_FUNCTION_NOARGS();
		return (DynamicCast<UwbModuleNetDevice>(m_netDevice))->GetNode()->GetObject<MobilityModel>();
	}


	Ptr<const SpectrumModel> UwbModulePhy::GetRxSpectrumModel() const
	{
		NS_LOG_FUNCTION_NOARGS();
		return NULL;
	}

	/**
	* set the associated NetDevice instance
	*
	* @param d the NetDevice instance
	*/
	void UwbModulePhy::SetDevice(Ptr<NetDevice> d)
	{
		NS_LOG_FUNCTION(this << d);
		m_netDevice = d;
	}

	/**
	* get the associated NetDevice instance
	*
	* @return a Ptr to the associated NetDevice instance
	*/
	Ptr<NetDevice> UwbModulePhy::GetDevice()
	{
		NS_LOG_FUNCTION_NOARGS();
		return m_netDevice;
	}
}