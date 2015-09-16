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

// Include a header file from your module to test.
#include "ns3/uwb-module.h"

// An essential include is test.h
#include "ns3/test.h"

// Do not put your test classes in namespace ns3.  You may find it useful
// to use the using directive to access the ns3 namespace directly
using namespace ns3;

// This is an example TestCase.
// This is an example TestCase.
class UwbModuleTestCase1 : public TestCase
{
public:
	UwbModuleTestCase1();
	virtual ~UwbModuleTestCase1();

private:
	virtual void DoRun(void);
};

// Add some help text to this case to describe what it is intended to test
UwbModuleTestCase1::UwbModuleTestCase1()
	: TestCase("UwbModule test case (does nothing)")
{
}

// This destructor does nothing but we include it as a reminder that
// the test case should clean up after itself
UwbModuleTestCase1::~UwbModuleTestCase1()
{
}
