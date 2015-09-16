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
#include <ns3/uwb-module.h>
#include <ns3/uwb-module-nd-protocol.h>

// An essential include is test.h
#include "ns3/test.h"

// Do not put your test classes in namespace ns3.  You may find it useful
// to use the using directive to access the ns3 namespace directly
using namespace ns3;

// This is an example TestCase.
class UwbModuleTestCase1 : public TestCase
{
public:
  UwbModuleTestCase1 ();
  virtual ~UwbModuleTestCase1 ();

private:
  virtual void DoRun (void);
};

// Add some help text to this case to describe what it is intended to test
UwbModuleTestCase1::UwbModuleTestCase1 ()
  : TestCase ("UwbModule Nd Protocol Test Case")
{
}

// This destructor does nothing but we include it as a reminder that
// the test case should clean up after itself
UwbModuleTestCase1::~UwbModuleTestCase1 ()
{
}

//
// This method is the pure virtual method from class TestCase that every
// TestCase must implement
//
void
UwbModuleTestCase1::DoRun (void)
{
	// A wide variety of test macros are available in src/core/test.h
	//NS_TEST_ASSERT_MSG_EQ (true, true, "true doesn't equal true for some reason");
	// Use this one for floating point comparisons
	//NS_TEST_ASSERT_MSG_EQ_TOL (0.01, 0.01, 0.001, "Numbers are not equal within tolerance");

	UwbModuleNdProtocol uwbModuleNdProtocol;
	Mac64Address address("12:34:56:78:90:AB:CD:EF");

	Ptr<Packet> packet = uwbModuleNdProtocol.GeneratePingPacket(address);

	Mac64Address result = uwbModuleNdProtocol.GetSenderAddress(packet);
	
	NS_TEST_ASSERT_MSG_EQ(address, result, "Address not equal");
  
}

// The TestSuite class names the TestSuite, identifies what type of TestSuite,
// and enables the TestCases to be run.  Typically, only the constructor for
// this class must be defined
//
class UwbModuleTestSuite : public TestSuite
{
public:
  UwbModuleTestSuite ();
};

UwbModuleTestSuite::UwbModuleTestSuite ()
  : TestSuite ("uwb-module", UNIT)
{
  // TestDuration for TestCase can be QUICK, EXTENSIVE or TAKES_FOREVER
  AddTestCase (new UwbModuleTestCase1, TestCase::QUICK);
}

// Do not forget to allocate an instance of this TestSuite
static UwbModuleTestSuite uwbModuleTestSuite;

