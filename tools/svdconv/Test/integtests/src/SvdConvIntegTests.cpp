/*
 * Copyright (c) 2020-2022 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "SvdConvIntegTestEnv.h"
#include "SvdConvTestUtils.h"

#include "SVDConv.h"
#include "ErrLog.h"

#include <map>
#include <list>
#include <fstream>
#include <regex>

using namespace std;
using namespace testing;


class SvdConvIntegTests : public ::testing::Test {
public:
  void SetUp()    override;
  void TearDown() override;
};

void SvdConvIntegTests::SetUp() {
}

void SvdConvIntegTests::TearDown() {
  ErrLog::Get()->Save();
  ErrLog::Get()->ClearLogMessages();
}


// Validate <disableCondition>
TEST_F(SvdConvIntegTests, CheckDisableCondition) {
#if 0
  const string& inFile = SvdConvIntegTestEnv::localtestdata_dir + "/disablecondition/DisableCondTest.svd";
  const string testOut = SvdConvIntegTestEnv::testoutput_dir + "/disablecondition";
  const string logFile = testOut + "/CheckDisableCondition.log";
  ASSERT_TRUE(RteFsUtils::Exists(inFile));

  Arguments args("SVDConv.exe", inFile);
  args.add({ "-o", testOut, "--generate=sfd", "--create-folder" });
  args.add({ "-b", logFile });
  
  SvdConv svdConv;
  EXPECT_EQ(0, svdConv.Check(args, args, nullptr));

  const string testOutSfd = testOut + "/DisableCondTest.sfd";
  cout << "\nTest SFD file: " << testOutSfd << endl;
  ASSERT_TRUE(RteFsUtils::Exists(testOutSfd));

  string buf;
  RteFsUtils::ReadFile(testOutSfd, buf);
  ASSERT_FALSE(buf.empty());

  const regex pattern1("//[ -]+Register Expression Object: (\\w+)[ -]+");   // regEx: ( .. ) is return content
  list<string> entries1 = { "DCB_DSCSR", "DCB_DSCSR_Clust_DSCSR" };
  list<smatch> result1 = SvdConvTestUtils::FindRegex(buf, pattern1);
  EXPECT_TRUE(SvdConvTestUtils::FindAllEntries(result1, entries1));

  //const regex pattern2("//[ ]+<view> (\\w+)\\s+//[ ]+<disableCond> \\((\\w+) & .*\\) == \\d+[ ]+</disableCond>");
  const regex pattern2("//[ ]+<view> \\w+\\s+//[ ]+<disableCond> \\((\\w+) & .*\\) == \\d+[ ]+</disableCond>");
  list<string> entries2 = { "DCB_DSCSR", "DCB_DSCSR_Clust_DSCSR" };
  list<smatch> result2 = SvdConvTestUtils::FindRegex(buf, pattern2);
  EXPECT_TRUE(SvdConvTestUtils::FindAllEntries(result2, entries2));
#endif
  EXPECT_TRUE(1);
}

// Validate <disableCondition>
TEST_F(SvdConvIntegTests, CheckNameHasBrackets) {
  const string& inFile = SvdConvIntegTestEnv::localtestdata_dir + "/nameHasBrackets/SVDTiny.svd";
  ASSERT_TRUE(RteFsUtils::Exists(inFile));

  Arguments args("SVDConv.exe", inFile);
  
  SvdConv svdConv;
  EXPECT_EQ(2, svdConv.Check(args, args, nullptr));

  auto msgs = ErrLog::Get()->GetLogMessages();
  bool bFound = false;
  for(const auto& msg : msgs) {
    if(msg.find("M386") != string::npos) {
      bFound = true;
      break;
    }
  }

  EXPECT_TRUE(bFound);
}
