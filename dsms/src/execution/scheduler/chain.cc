//
// Created by Nikos R. Katsipoulakis on 2/18/18.
//
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cfloat>
#include <string>

#include <map>
#include <list>
#include <utility>

#ifndef _DEBUG_
#include <dsms/include/common/debug.h>
#endif

#ifndef _CHAIN_
#include <dsms/include/execution/scheduler/chain.h>
#endif

#include <cmath>
#include <algorithm>
#include <dsms/include/execution/operators/select.h>

static const TimeSlice timeSlice = 10;

Execution::ChainScheduler::ChainScheduler(std::ostream &LOG) : LOG(LOG) {
    numOps = 0;
    bStop = false;
}

Execution::ChainScheduler::~ChainScheduler() {}

int Execution::ChainScheduler::addOperator(Operator *op) {
    if (numOps == MAX_OPS)
        return -1;
    ops[numOps++] = (Select*) op;
}

int Execution::ChainScheduler::run(long long int numTimeUnits) {
    int val;
    Monitor::Timer myTime;
    // TO-DO: Complete Chain
}