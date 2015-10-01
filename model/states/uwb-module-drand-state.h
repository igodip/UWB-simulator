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
#include <ns3/uwb-module-abs-drand-state.h>
#include <ns3/uwb-module-manager.h>
#include <ns3/mac64-address.h>

#include <set>
#include <map>

namespace ns3
{
	class UwbModuleDrandState : public UwbModuleAbstractState
	{
	public:

		UwbModuleDrandState(Ptr<UwbModuleManager> state);
		~UwbModuleDrandState();

		static TypeId GetTypeId();

		virtual void Start();
		virtual void Receive(Ptr<Packet> p);

		void SetState(Ptr<UwbModuleAbsDrandState> state);
		Ptr<UwbModuleAbsDrandState> GetState() const;

		void SetNeighbors(const std::set<Mac64Address> addresses);
		const std::set<Mac64Address> & GetNeighbors() const;

		const std::map<uint32_t, Mac64Address> getTurns() const;
		void setTurn(uint32_t turn, Mac64Address address);

		Ptr<UwbModuleManager> GetManager() const;
		void SetManager(Ptr<UwbModuleManager> manager);

		uint32_t GetTurn() const;
		void SetTurn(uint32_t turn);

	protected:

		Ptr<UwbModuleAbsDrandState> m_state;
		Ptr<UwbModuleManager> m_manager;

		std::set<Mac64Address> m_addresses;
		std::map<uint32_t,Mac64Address> m_turns;

		uint32_t m_myTurn;

	};
}


#endif