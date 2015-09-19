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

#ifndef UWB_MODULE_PHY_H
#define UWB_MODULE_PHY_H

#include <ns3/spectrum-phy.h>
#include <ns3/channel.h>

#include <ns3/uwb-module-spectrum-signal-parameters.h>
#include <ns3/event-id.h>
#include <ns3/traced-callback.h>
#include <ns3/antenna-model.h>
#include <ns3/spectrum-model.h>
#include <ns3/node.h>

namespace ns3
{

	class UwbModuleNetDevice;

	class UwbModulePhy : public SpectrumPhy
	{
	public:

		static TypeId GetTypeId(void);

		/**
		* Set the mobility model associated with this device.
		*
		* @param m the mobility model
		*/
		virtual void SetMobility(Ptr<MobilityModel> m);

		/**
		* get the associated MobilityModel instance
		*
		* @return a Ptr to the associated MobilityModel instance
		*/
		virtual Ptr<MobilityModel> GetMobility();
		/**
		* set the associated NetDevice instance
		*
		* @param d the NetDevice instance
		*/
		virtual void SetDevice(Ptr<NetDevice> d);

		/**
		* get the associated NetDevice instance
		*
		* @return a Ptr to the associated NetDevice instance
		*/
		virtual Ptr<NetDevice> GetDevice();

		/**
		* set the associated Channel
		*
		* @param c the Spectrum Channel
		*/
		virtual void SetChannel(Ptr<SpectrumChannel> c);

		/**
		* get the associated Channel
		*
		* @return a Ptr to the associated NetDevice instance
		*/
		virtual Ptr<SpectrumChannel> GetChannel() const;

		/**
		*
		* @return returns the SpectrumModel that this SpectrumPhy expects to be used
		* for all SpectrumValues that are passed to StartRx. If 0 is
		* returned, it means that any model will be accepted.
		*/
		virtual Ptr<const SpectrumModel> GetRxSpectrumModel() const;

		/**
		* get the AntennaModel used by the NetDevice for reception
		*
		* @return a Ptr to the AntennaModel used by the NetDevice for reception
		*/
		virtual Ptr<AntennaModel> GetRxAntenna();

		/**
		* Notify the SpectrumPhy instance of an incoming signal
		*
		* @param params the parameters of the signals being received
		*/

		void SetAntenna(Ptr<AntennaModel> a);

		//Transmission
		void StartRx(Ptr<SpectrumSignalParameters> params);
		void EndRx(Ptr<SpectrumSignalParameters> params);

		void StartTx(Ptr<UwbModuleSpectrumSignalParameters> params);
		void EndTx(Ptr<UwbModuleSpectrumSignalParameters> params);
	protected:

		virtual void DoDispose(void);
		virtual void DoInitialize(void);
		

	private:

		Ptr<SpectrumChannel> m_channel;
		Ptr<NetDevice> m_netDevice;

		//trace
		TracedCallback<Ptr<const Packet> > m_phyRxBeginTrace;
		TracedCallback<Ptr<const Packet> > m_phyRxDropTrace;
		TracedCallback<Ptr<const Packet> > m_phyRxEndTrace;
		TracedCallback<Ptr<const Packet> > m_phyTxDropTrace;
		TracedCallback<Ptr<const Packet> > m_phyTxEndTrace;
		TracedCallback<Ptr<const Packet> > m_phyTxBeginTrace;

		Ptr<AntennaModel> m_antenna;
		EventId m_busy;
		

	};
}

#endif