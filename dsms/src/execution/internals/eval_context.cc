//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#include "../../../include/execution/internals/tuple.h"
#include "../../../include/execution/internals/eval_context.h"
#include "../../../include/common/debug.h"

using namespace Execution;

void EvalContext::bind (Tuple tuple, unsigned int role)
{
    ASSERT (role < MAX_ROLES);

    roles [role] = tuple;
}