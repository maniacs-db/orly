/* <orly/rt/mutate.h>

   TODO

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

#pragma once

#include <orly/var/impl.h>
#include <orly/shared_enum.h>

namespace Orly {

  /* Forward declaration */
  namespace Var {

    class TVar;

  }  // Var

  namespace Rt {

    Var::TVar Mutate(const Var::TVar &lhs, TMutator mutator, const Var::TVar &rhs);

  }  // Rt

}  // Orly
