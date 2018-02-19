//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _AGGR_
#define _AGGR_

#ifndef  _TYPES_
#include "types.h"
#endif

enum AggrFn {
    COUNT, SUM, AVG, MAX, MIN
};

Type getOutputType(AggrFn fn, Type inputType);

#endif //_AGGR_
