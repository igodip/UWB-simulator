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

#ifndef UWB_MODULE_GRANT_STATE_H
#define UWB_MODULE_GRANT_STATE_H

#include "uwb-module-abs-drand-state.h"
#include <ns3/uwb-module-drand-state.h>
#include <ns3/event-id.h>
#include <ns3/nstime.h>

namespace ns3
{
	class UwbModuleGrantState : public UwbModuleAbsDrandState
	{
	public:

		UwbModuleGrantState(Ptr<UwbModuleDrandState> state);
		virtual ~UwbModuleGrantState();

		static TypeId GetTypeId();

		virtual void Start();
		virtual void Receive(Ptr<Packet> p);

		virtual void Grant(Ptr<const Packet> p);
		virtual void Fail(Ptr<const Packet> p);
		virtual void Request(Ptr<const Packet> p);
		virtual void Release(Ptr<const Packet> p);
		virtual void Reject(Ptr<const Packet> p);

		void SendGrant(Ptr<const Packet> p);

	protected:

		Ptr<UwbModuleDrandState> m_drand;

		void Timeout();
		
		void SendReject(Ptr<const Packet> p);

		std::set<Mac64Address> m_answers;

		EventId m_timeout;
		static Time m_waitTime;

	};
}

#endif