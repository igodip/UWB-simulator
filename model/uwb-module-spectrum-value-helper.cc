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

#include "uwb-module-spectrum-value-helper.h"

#include <ns3/log.h>
#include <ns3/assert.h>
#include <ns3/uwb-module-spectrum-model-factory.h>

#include <cmath>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleSpectrumValueHelper");

	UwbModuleSpectrumValueHelper::UwbModuleSpectrumValueHelper()
	{
		NS_LOG_FUNCTION(this);
		m_noiseFactor = 1.0;
	}

	UwbModuleSpectrumValueHelper::~UwbModuleSpectrumValueHelper()
	{
		NS_LOG_FUNCTION(this);
	}

	Ptr<SpectrumValue> UwbModuleSpectrumValueHelper::CreateTxPowerSpectralDensity(double txPower, uint32_t channel) {

		NS_LOG_FUNCTION(this << txPower << channel);

		//ALL WRONG
		Ptr<SpectrumValue> txPsd = Create<SpectrumValue>(UwbModuleSpectrumModelFactory::getInstance().getSpectrumModel());

		//txPower is expressed in dBm. We must convert it into natural unit (W).
		txPower = pow(10, (txPower / 10));

		//The effective occupied bandwidth of the signal is modelled to be 2.16 Ghz.
		double txPowerDensity = txPower / 2.160e9;

		// 4 channels
		// 1 58.320 centered 2.16 GHz large
		// 2 60.480 centered 2.16 GHz large
		// 3 62.640 centered 2.16 GHz large
		// 4 64.800 centered 2.16 GHz large

		NS_ASSERT_MSG((channel >= 1 && channel <= 4), "Invalid channel number");

		for (int i = 0; i < 720; ++i)
		{
			(*txPsd)[720 * (channel - 1) + i] = txPowerDensity;
		}

		return txPsd;
	}

	Ptr<SpectrumValue> UwbModuleSpectrumValueHelper::CreateNoisePowerSpectralDensity(uint32_t channel) {

		NS_LOG_FUNCTION(this);
		Ptr<SpectrumValue> noisePsd = Create<SpectrumValue>(UwbModuleSpectrumModelFactory::getInstance().getSpectrumModel());

		//static const double BOLTZMANN = 1.3803e-23;
		// Nt  is the power of thermal noise in W
		//double Nt = BOLTZMANN * 290.0;
		// noise Floor (W) which accounts for thermal noise and non-idealities of the receiver
		//double noisePowerDensity = m_noiseFactor * Nt;

		NS_ASSERT_MSG((channel >= 1 && channel <= 4), "Invalid channel number");

		return noisePsd;

	}

	double UwbModuleSpectrumValueHelper::TotalAvgPower(Ptr<const SpectrumValue> psd, uint32_t channel)
	{


		NS_ASSERT_MSG((channel >= 1 && channel <= 4), "Invalid channel number");

		double totalAvgPower = 0.0;

		NS_ASSERT(psd->GetSpectrumModel() == UwbModuleSpectrumModelFactory::getInstance().getSpectrumModel());

		//Numerically integrate

		for (int i = 0; i < 720; ++i)
		{
			totalAvgPower += (*psd)[720 * (channel - 1) + i];
		}

		totalAvgPower *= 3.0e6;

		totalAvgPower = 10 * log10(totalAvgPower);

		return totalAvgPower;
	}
}