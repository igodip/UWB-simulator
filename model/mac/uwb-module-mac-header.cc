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

#include "uwb-module-mac-header.h"
#include <ns3/log.h>
#include <ns3/address-utils.h>

namespace ns3
{

	NS_LOG_COMPONENT_DEFINE("UwbModuleMacHeader");

	NS_OBJECT_ENSURE_REGISTERED(UwbModuleMacHeader);

	void UwbModuleMacHeader::SetSenderEuid(const Mac64Address & euid)
	{
		NS_LOG_FUNCTION(this << euid);
		m_senderEuid = euid;
	}

	void UwbModuleMacHeader::SetReceiverEuid(const Mac64Address & euid)
	{
		NS_LOG_FUNCTION(this << euid);
		m_receiverEuid = euid;
	}

	Mac64Address UwbModuleMacHeader::GetSenderEuid() const
	{
		NS_LOG_FUNCTION(this);
		return m_senderEuid;
	}

	Mac64Address UwbModuleMacHeader::GetReceiverEuid() const
	{
		NS_LOG_FUNCTION(this);
		return m_receiverEuid;
	}

	TypeId UwbModuleMacHeader::GetTypeId(void)
	{
		NS_LOG_FUNCTION_NOARGS();

		TypeId tid = TypeId("ns3::UwbModuleMacHeader")
			.SetParent<Header>();

		return tid;
	}

	UwbModuleMacHeader::~UwbModuleMacHeader()
	{
		NS_LOG_FUNCTION(this);
	}

	void UwbModuleMacHeader::Serialize(Buffer::Iterator start) const
	{
		NS_LOG_FUNCTION(this);

		Buffer::Iterator i = start;
		
		WriteTo(i, GetSenderEuid());
		WriteTo(i, GetReceiverEuid());
	}

	uint32_t UwbModuleMacHeader::GetSerializedSize(void) const
	{
		NS_LOG_FUNCTION(this);
		return sizeof(Mac64Address) * 2;
	}

	uint32_t UwbModuleMacHeader::Deserialize(Buffer::Iterator start)
	{
		NS_LOG_FUNCTION(this);

		Buffer::Iterator i = start;

		Address receiver, sender;

		ReadFrom(i, receiver, 8);
		ReadFrom(i, sender, 8);

		SetReceiverEuid(Mac64Address::ConvertFrom(receiver));
		SetSenderEuid(Mac64Address::ConvertFrom(sender));

		return i.GetDistanceFrom(start);
		//return 0;
	}

	void UwbModuleMacHeader::Print(std::ostream &os) const
	{
		NS_LOG_FUNCTION(this);
	}

}