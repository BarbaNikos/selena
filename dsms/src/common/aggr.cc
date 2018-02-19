//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//
#ifndef _AGGR_
#include "../../include/common/aggr.h"
#endif
Type getOutputType(AggrFn fn, Type inputType) {
    return (fn == AVG)? FLOAT : inputType;
}
