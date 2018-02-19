//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//
/**
 * @file       round_robin.cc
 * @brief      Implementation of the round robin scheduler
 */
#include <iostream>
using namespace std;

#ifndef _DEBUG_
#include <dsms/include/common/debug.h>
#endif

#ifndef _ROUND_ROBIN_
#include <dsms/include/execution/scheduler/round_robin.h>
#endif

using namespace Execution;

static const TimeSlice timeSlice = 100000;

RoundRobinScheduler::RoundRobinScheduler()
{
    this -> numOps = 0;
    bStop = false;
}

RoundRobinScheduler::~RoundRobinScheduler() {}

int RoundRobinScheduler::addOperator (Operator *op)
{
    if (numOps == MAX_OPS)
        return -1;
    ops [numOps ++] = op;

    return 0;
}

int RoundRobinScheduler::run (long long int numTimeUnits)
{
    int rc;

    // numtimeunits == 0 signal for scheduler to run forever (until stopped)
    if (numTimeUnits == 0) {
        while (!bStop) {
            for (unsigned int o = 0 ; o < numOps ; o++) {
                if ((rc = ops [o] -> run(timeSlice)) != 0) {
                    return rc;
                }
            }
        }
    }

    else {
        for (long long int t = 0 ; (t < numTimeUnits) && !bStop ; t++) {
            for (unsigned int o = 0 ; o < numOps ; o++) {
                if ((rc = ops [o] -> run(timeSlice)) != 0) {
                    return rc;
                }
            }
        }
    }

    return 0;
}



int RoundRobinScheduler::stop ()
{
    bStop = true;
    return 0;
}

int RoundRobinScheduler::resume ()
{
    bStop = false;
    return 0;
}
