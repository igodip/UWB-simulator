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

#ifndef UWB_MODULE_DRAND_APP_H
#define UWB_MODULE_DRAND_APP_H

#include "uwb-module-manager.h"
#include <ns3/uwb-module-abstract-state.h>
#include <ns3/uwb-module-net-device.h>

namespace ns3
{
	class UwbModuleDrandApp : public UwbModuleManager
	{
	public:

		UwbModuleDrandApp(Ptr<UwbModuleNetDevice> netDevice);

		static TypeId GetTypeId();

		virtual void Receive(Ptr<Packet> packet);
		virtual void Start();

		void SetState(Ptr<UwbModuleAbstractState> state);
		Ptr<UwbModuleNetDevice> GetNetDevice() const;

	protected:

	private:

		Ptr<UwbModuleAbstractState> m_state;
		Ptr<UwbModuleNetDevice> m_netDevice;

	};
}

#endif