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

#ifndef UWB_MODULE_ELECTION_STATE_H
#define UWB_MODULE_ELECTION_STATE_H

#include "uwb-module-abstract-state.h"

namespace ns3
{
	class UwbModuleElectionState : public UwbModuleAbstractState
	{
	public:

		UwbModuleElectionState();
		virtual ~UwbModuleElectionState();

		static TypeId GetTypeId();

		void Start();
		void Receive(Ptr<Packet> p);

	private:

	};
}

#endif
