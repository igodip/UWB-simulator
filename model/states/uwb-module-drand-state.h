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

#ifndef UWB_MODULE_DRAND_STATE_H
#define UWB_MODULE_DRAND_STATE_H

#include <ns3/uwb-module-abstract-state.h>
#include <ns3/uwb-module-manager.h>

namespace ns3
{
	class UwbModuleDrandState : public UwbModuleAbstractState
	{
	public:

		UwbModuleDrandState(Ptr<UwbModuleManager> state);
		~UwbModuleDrandState();

		static TypeId GetTypeId();

		virtual void Start();
		virtual void Receive(Ptr<Packet> p) ;

		void SetState(Ptr<UwbModuleAbstractState> state);
		
	protected:
		Ptr<UwbModuleAbstractState> m_state;
		Ptr<UwbModuleManager> m_manager;
	};
}


#endif