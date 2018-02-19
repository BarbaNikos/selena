//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _EVAL_CONTEXT_
#define _EVAL_CONTEXT_

#include "execution/internals/tuple.h"

#define ILOC(c,o) (*(((int *)roles[(c)]) + (o)))
#define FLOC(c,o) (*(((float *)roles[(c)]) + (o)))
#define BLOC(c,o) (*((roles[(c)]) + (o)))
#define CLOC(c,o) ((roles[(c)]) + (o))

namespace Execution {
    struct EvalContext {
        static const unsigned int MAX_ROLES = 10;
        char *roles [MAX_ROLES];
        void bind (Tuple tuple, unsigned int roleId);
    };
}

#endif //_EVAL_CONTEXT_
