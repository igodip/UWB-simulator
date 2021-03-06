/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2015 KTH
*
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
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* Authors:
*  Igor Di Paolo <igor.di.paolo@gmail.com>
*/

#ifndef UWB_MODULE_PHY_STAT_HELPER_H
#define UWB_MODULE_PHY_STAT_HELPER_H

#include <ns3/ptr.h>
#include <ns3/packet.h>

namespace ns3
{
	class UwbModulePhyStatHelper
	{
	public:

		UwbModulePhyStatHelper();

		void reset();
		void attach();

		uint64_t getTxBegin() const;
		uint64_t getRxBegin() const;
		uint64_t getTxDrop() const;
		uint64_t getRxDrop() const;
		uint64_t getTxEnd() const;
		uint64_t getRxEnd() const;

	protected:

		void incRxBegin(std::string str,Ptr<const Packet> p);
		void incRxDrop(std::string str, Ptr<const Packet> p);
		void incRxEnd(std::string str, Ptr<const Packet> p);

		void incTxBegin(std::string str, Ptr<const Packet> p);
		void incTxDrop(std::string str, Ptr<const Packet> p);
		void incTxEnd(std::string str, Ptr<const Packet> p);

		uint64_t m_txBegin;
		uint64_t m_rxBegin;
		uint64_t m_txDrop;
		uint64_t m_rxDrop;
		uint64_t m_rxEnd;
		uint64_t m_txEnd;


	};

} // namespace ns3

#endif //HR_WPAN_PHY_STAT_HELPER_H