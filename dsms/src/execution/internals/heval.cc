//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#include "../../../include/execution/internals/heval.h"
#include "../../../include/common/debug.h"

using namespace Execution;

HEval::HEval ()
{
    roles = 0;
    numInstrs = 0;
}

HEval::~HEval () {}

int HEval::setEvalContext (EvalContext *evalContext)
{
    ASSERT (evalContext);

    this -> roles = evalContext -> roles;
    return 0;
}

int HEval::addInstr (HInstr instr)
{
    ASSERT (numInstrs <= MAX_INSTRS);

    if (numInstrs == MAX_INSTRS)
        return -1;

    instrs [numInstrs ++] = instr;
    return 0;
}