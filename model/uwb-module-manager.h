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

#ifndef UWB_MODULE_MANAGER
#define UWB_MODULE_MANAGER

#include <ns3/object.h>
#include <ns3/packet.h>

namespace ns3
{
	class UwbModuleManager : public Object
	{
	public:
		virtual void Receive(Ptr<Packet> packet) = 0;
		virtual void Start() = 0;
	};
}

#endif