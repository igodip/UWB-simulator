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

#ifndef UWB_MODULE_SPECTRUM_SIGNAL_PARAMETERS_H
#define UWB_MODULE_SPECTRUM_SIGNAL_PARAMETERS_H

#include <ns3/spectrum-signal-parameters.h>
#include <ns3/packet-burst.h>

namespace ns3
{
	class UwbModuleSpectrumSignalParameters : public SpectrumSignalParameters
	{
	public:

		// inherited from SpectrumSignalParameters
		virtual Ptr<SpectrumSignalParameters> Copy(void);

		/**
		* default constructor
		*/
		UwbModuleSpectrumSignalParameters(void);

		/**
		* copy constructor
		*/
		UwbModuleSpectrumSignalParameters(const UwbModuleSpectrumSignalParameters& p);

		/**
		* The packet burst being transmitted with this signal
		*/
		Ptr<PacketBurst> packetBurst;
	};
}

#endif