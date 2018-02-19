//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#include "../../../include/execution/internals/eval_context.h"
#include "../../../include/execution/internals/beval.h"
#include "../../../include/execution/internals/filter_iter.h"
#include "../../../include/common/debug.h"

using namespace Execution;

FilterIterator::FilterIterator (EvalContext *evalContext,
                                BEval *pred)
{
    ASSERT (pred);
    ASSERT (evalContext);

    this -> evalContext = evalContext;
    this -> pred = pred;
}

FilterIterator::~FilterIterator () {}

int FilterIterator::initialize (TupleIterator *source)
{
    ASSERT (source);
    this -> source = source;
    return 0;
}

bool FilterIterator::getNext (Tuple &tuple)
{
    while (true) {
        if (!source -> getNext (tuple))
            return false;

        evalContext -> bind (tuple, FI_SCAN_ROLE);

        if (pred -> eval())
            return true;
    }

    // never comes
    return false;
}