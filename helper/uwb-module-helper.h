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
#ifndef UWB_MODULE_HELPER_H
#define UWB_MODULE_HELPER_H

#include <ns3/net-device-container.h>
#include <ns3/object-factory.h>
#include <ns3/node-container.h>
#include <ns3/spectrum-channel.h>

namespace ns3 {

	class UwbModuleHelper
	{
	public:
		/**
		*/
		UwbModuleHelper();
		/**
		*/
		NetDeviceContainer InstallNodes(NodeContainer c);
		/**
		*/
		NetDeviceContainer InstallTargets(NodeContainer c);
		/**
		*/
		int64_t AssignStreams(NetDeviceContainer c, int64_t stream);
	private:

		ObjectFactory m_deviceFactory; //!< Object factory

		Ptr<SpectrumChannel> m_channel;

	};

}

#endif /* UWB_MODULE_HELPER_H */

