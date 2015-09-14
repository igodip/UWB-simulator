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

#include <ns3/log.h>
#include <ns3/node.h>
#include <ns3/mobility-helper.h>
#include <ns3/uwb-module-helper.h>

using namespace ns3;

int main(int argc, char ** argv)
{

	Ptr<Node> n1, n2;
	n1 = CreateObject<Node>();
	n2 = CreateObject<Node>();

	NodeContainer nodeContainer(n1, n2);

	UwbModuleHelper uwbModuleHelper;
	uwbModuleHelper.Install(nodeContainer);



	return 0;
}