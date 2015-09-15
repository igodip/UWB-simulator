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

		UwbModuleSpectrumSignalParameters psdHelper;

		Ptr<UwbModuleSpectrumSignalParameters> uwbRxParams = DynamicCast<UwbModuleSpectrumSignalParameters>(params);

		// It isn't an our packet
		if (uwbRxParams == 0)
		{
			m_receiveOn = Simulator::Schedule(params->duration, &UwbModulePhy::EndRx, this, params);
			return;
		}

		Ptr<Packet> p = (uwbRxParams->packetBurst->GetPackets()).front();
		m_phyRxBeginTrace(p);

		Time duration;

		m_receiveOn = Simulator::Schedule(params->duration, &UwbModulePhy::EndRx, this, params);
	}

	void UwbModulePhy::EndRx(Ptr<SpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
	}

	void UwbModulePhy::StartTx(Ptr<UwbModuleSpectrumSignalParameters> params)
	{
		NS_LOG_FUNCTION(this << params);
		
		m_channel->StartTx(params);

		Simulator::Schedule(params->duration, &UwbModulePhy::EndTx, this, params);
	}

	void UwbModulePhy::EndTx(Ptr<UwbModuleSpectrumSignalParameters> params)
	{

	}

	void UwbModulePhy::SetMobility(Ptr<MobilityModel> m)
	{

	}


	Ptr<MobilityModel> UwbModulePhy::GetMobility()
	{
		NS_LOG_FUNCTION(this);
		return (DynamicCast<UwbModuleNetDevice>(m_netDevice))->GetNode()->GetObject<MobilityModel>();
	}


	Ptr<const SpectrumModel> UwbModulePhy::GetRxSpectrumModel() const
	{
		return NULL;
	}

	/**
	* set the associated NetDevice instance
	*
	* @param d the NetDevice instance
	*/
	void UwbModulePhy::SetDevice(Ptr<NetDevice> d)
	{
		m_netDevice = d;
	}

	/**
	* get the associated NetDevice instance
	*
	* @return a Ptr to the associated NetDevice instance
	*/
	Ptr<NetDevice> UwbModulePhy::GetDevice()
	{
		return m_netDevice;
	}
}