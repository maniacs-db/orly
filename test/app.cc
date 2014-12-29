/* <test/app.cc>

   Implements <test/app.h>.

   Copyright 2010-2014 OrlyAtomics, Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

#include <test/app.h>

#include <cstdlib>

#include <cmd/main.h>
#include <cmd/parser.h>
#include <test/options.h>
#include <test/fixture.h>

using namespace std;
using namespace Base;
using namespace Test;


void TApp::OnRunnerDtor(const TRunner *runner) {
  assert(this);
  assert(runner);
  ++(*runner ? PassCount : FailCount);
}

void RunFixtures() {
  for(const TFixture *fixture: GetFixtures()) {
    //TODO(cmaloney): Stack based logging singleton?
    // A context captures failures that occur with in it. A single failure causes all previous
    // log messages to be flushed out. And all future log messages at that context to be written
    // straight to the output.
    Logger::TContext context(fixture->Name);
    // On construction initializes the log with
    // TLog() << "begin " << Name;
    // On destruction finishes it off with:
    // TLog() << "end " << Name << "; " << FailureCount ? "fail" : "pass" << '\n';

    fixture->Func();
  }
}

int Main(int argc, char *argv[]) {
  TParser parser;
  parser.Attach(GetArgs(), GetOptionsNonConst());

  // Set the target to be std::cout when we're printing all the test.
  // This makes it so that we don't buffer the results at all.
  //
  // In regular operation results are buffered (Fixture begin/end), test results
  // until there is a failure at which point we print out all the context
  // which leads to the failure (what fixture it was in), as well as the failure
  // itself.
  if (PrintTests) {
    TLogger::SetTarget(std::cout);
  }

  // True == pass, False == fail.
  bool unit_test_result = true;

  // Hoisted out of loop for performance.
  chrono::time_point<chrono::system_clock> start, stop;
  ostringstream out;

  RunFixtures();

  const TContext &root_ctx = Context::GetRoot();

  bool success = root_ctx.FailCount;
  TLog(!success) << "passed" << root_ctx.PassCount << ", failed " << root_ctx.FailCount << "\n";
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
