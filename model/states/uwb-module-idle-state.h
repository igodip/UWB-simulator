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

#ifndef UWB_MODULE_IDLE_STATE_H
#define UWB_MODULE_IDLE_STATE_H

#include <ns3/uwb-module-drand-state.h>
#include <ns3/event-id.h>
#include <ns3/random-variable-stream.h>
#include <ns3/nstime.h>
#include <ns3/uwb-module-net-device.h>

namespace ns3
{
	
	class UwbModuleIdleState : public UwbModuleAbstractState
	{
	public:

		UwbModuleIdleState(Ptr<UwbModuleDrandState> state);

		static TypeId GetTypeId();

		virtual void Start();
		virtual void Receive(Ptr<Packet> p);
	
	protected:
		
		void TryRequest();

	private:

		Ptr<UwbModuleDrandState> m_state;
		EventId m_event;

		Ptr<UniformRandomVariable> m_urv;

		static Time m_waitTime;
		static double m_threshold;
	};

}

#endif