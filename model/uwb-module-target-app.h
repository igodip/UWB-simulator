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

#ifndef UWB_MODULE_TARGET_APP_H
#define UWB_MODULE_TARGET_APP_H

#include "uwb-module-manager.h"


namespace ns3
{
	class UwbModuleTargetApp : public UwbModuleManager
	{
	public:

		virtual void Receive(Ptr<Packet> packet);
		virtual void Start();

	protected:



	};
}


#endif