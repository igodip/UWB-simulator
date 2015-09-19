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

#ifndef UWB_MODULE_REQUEST_STATE_H
#define UWB_MODULE_REQUEST_STATE_H

#include <ns3/uwb-module-drand-state.h>
#include <ns3/random-variable-stream.h>
#include <ns3/event-id.h>

namespace ns3
{
	class UwbModuleRequestState : public UwbModuleAbstractState
	{
	public:
		
		UwbModuleRequestState(Ptr<UwbModuleDrandState> state);
		virtual ~UwbModuleRequestState();

		static TypeId GetTypeId();

		virtual void Start();
		virtual void Receive(Ptr<Packet> p);

	protected:
		Ptr<UniformRandomVariable> m_rand;
		Ptr<UwbModuleDrandState> m_drand;
		EventId m_evt;

		void SendRequest();
	};
}

#endif