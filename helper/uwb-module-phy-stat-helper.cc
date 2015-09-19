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

#include "uwb-module-phy-stat-helper.h"
#include <ns3/log.h>
#include <ns3/config.h>
#include <ns3/callback.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("UwbModulePhyStatHelper");

	UwbModulePhyStatHelper::UwbModulePhyStatHelper()
	{
		NS_LOG_FUNCTION(this);

		reset();
	}

	void UwbModulePhyStatHelper::reset()
	{
		NS_LOG_FUNCTION(this);

		m_txBegin = 0;
		m_rxBegin = 0;
		m_txDrop = 0;
		m_rxDrop = 0;
		m_rxEnd = 0;
		m_txEnd = 0;
	}

	void UwbModulePhyStatHelper::attach()
	{

		NS_LOG_FUNCTION(this);

		Config::Connect("/NodeList/*/DeviceList/*/$ns3::UwbModuleNetDevice/Phy/PhyRxBegin",
			MakeCallback(&UwbModulePhyStatHelper::incRxBegin, this));

		Config::Connect("/NodeList/*/DeviceList/*/$ns3::UwbModuleNetDevice/Phy/PhyRxEnd",
			MakeCallback(&UwbModulePhyStatHelper::incRxEnd, this));

		Config::Connect("/NodeList/*/DeviceList/*/$ns3::UwbModuleNetDevice/Phy/PhyRxDrop",
			MakeCallback(&UwbModulePhyStatHelper::incRxDrop, this));

		Config::Connect("/NodeList/*/DeviceList/*/$ns3::UwbModuleNetDevice/Phy/PhyTxBegin",
			MakeCallback(&UwbModulePhyStatHelper::incTxBegin, this));

		Config::Connect("/NodeList/*/DeviceList/*/$ns3::UwbModuleNetDevice/Phy/PhyTxDrop",
			MakeCallback(&UwbModulePhyStatHelper::incTxDrop, this));

		Config::Connect("/NodeList/*/DeviceList/*/$ns3::UwbModuleNetDevice/Phy/PhyTxEnd",
			MakeCallback(&UwbModulePhyStatHelper::incTxEnd, this));
	}

	uint64_t UwbModulePhyStatHelper::getTxBegin() const
	{
		NS_LOG_FUNCTION(this);
		return m_rxBegin;
	}

	uint64_t UwbModulePhyStatHelper::getRxBegin() const
	{
		NS_LOG_FUNCTION(this);
		return m_rxDrop;
	}

	uint64_t UwbModulePhyStatHelper::getTxDrop() const
	{
		NS_LOG_FUNCTION(this);
		return m_txDrop;
	}

	uint64_t UwbModulePhyStatHelper::getRxDrop() const
	{
		NS_LOG_FUNCTION(this);
		return m_rxDrop;
	}

	uint64_t UwbModulePhyStatHelper::getTxEnd() const
	{
		NS_LOG_FUNCTION(this);
		return m_txEnd;
	}

	uint64_t UwbModulePhyStatHelper::getRxEnd() const
	{
		NS_LOG_FUNCTION(this);
		return m_rxEnd;
	}


	void UwbModulePhyStatHelper::incRxBegin(std::string str, Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << str << p);
		++m_rxBegin;
	}

	void UwbModulePhyStatHelper::incRxDrop(std::string str, Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << str << p);
		++m_rxDrop;
	}

	void UwbModulePhyStatHelper::incRxEnd(std::string str, Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << str << p);
		++m_rxEnd;
	}

	void UwbModulePhyStatHelper::incTxBegin(std::string str, Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << str << p);
		++m_txBegin;
	}

	void UwbModulePhyStatHelper::incTxDrop(std::string str, Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << str << p);
		++m_txDrop;
	}
	void UwbModulePhyStatHelper::incTxEnd(std::string str, Ptr<const Packet> p)
	{
		NS_LOG_FUNCTION(this << str << p);
		++m_txEnd;
	}
}