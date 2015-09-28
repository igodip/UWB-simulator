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

#include "uwb-module-mac-trailer.h"
#include <ns3/log.h>

namespace ns3
{
	NS_LOG_COMPONENT_DEFINE("UwbModuleMacTrailer");

	UwbModuleMacTrailer::UwbModuleMacTrailer()
	{
		NS_LOG_FUNCTION(this);
	}

	UwbModuleMacTrailer::~UwbModuleMacTrailer()
	{
		NS_LOG_FUNCTION(this);
	}



	TypeId UwbModuleMacTrailer::GetTypeId(void)
	{
		NS_LOG_FUNCTION_NOARGS();
		TypeId tid = TypeId("ns3::UwbModuleMacTrailer")
			.SetParent<Trailer>();

		return tid;
	}

	void UwbModuleMacTrailer::Serialize(Buffer::Iterator start) const
	{
		NS_LOG_FUNCTION(this);
	}

	uint32_t UwbModuleMacTrailer::GetSerializedSize(void) const
	{
		NS_LOG_FUNCTION(this);
		return 0;
	}

	uint32_t UwbModuleMacTrailer::Deserialize(Buffer::Iterator start)
	{
		NS_LOG_FUNCTION(this);
		return 0;
	}

	void UwbModuleMacTrailer::Print(std::ostream &os) const
	{
		NS_LOG_FUNCTION(this);
	}
}

