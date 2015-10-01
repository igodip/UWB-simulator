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

#ifndef UWB_MODULE_MAC_HEADER_H
#define UWB_MODULE_MAC_HEADER_H

#include <ns3/header.h>
#include <ns3/mac64-address.h>

// DEFAULT ADDRESS SETTINGS //
#define DEFAULT_PAN_ID 0xDECA

// BLINK MESSAGE //
#define LOCATION_BLINK_FC	0xC5
namespace ns3
{
	class UwbModuleMacHeader : public Header
	{
	public:

		static TypeId GetTypeId(void);
		virtual TypeId GetInstanceTypeId(void) const;
		virtual ~UwbModuleMacHeader();

		void SetSenderEuid(const Mac64Address & euid);
		void SetReceiverEuid(const Mac64Address & euid);

		Mac64Address GetSenderEuid() const;
		Mac64Address GetReceiverEuid() const;

		virtual void Serialize(Buffer::Iterator start) const ;
		virtual uint32_t GetSerializedSize(void) const;
		virtual uint32_t Deserialize(Buffer::Iterator start);
		virtual void Print(std::ostream &os) const;

	protected:

		uint8_t frameCtrl[2] = { DATA_FC0, DATA_FC1 };
		uint8_t seqNumber;
		uint16_t panId;

		Mac64Address m_senderEuid;
		Mac64Address m_receiverEuid;


	};
}


#endif