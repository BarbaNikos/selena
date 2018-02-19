//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//
#ifndef _OPERATOR_
#include "execution/operators/operator.h"
#endif

#ifndef _SCHEDULER_
#define _SCHEDULER_

namespace Execution {
    class Scheduler {
    public:
        virtual ~Scheduler() {}
        /**
         * Add a new operator to schedule
         */
        virtual int addOperator (Operator *op) = 0;

        /**
         * Schedule the operators for a prescribed set of time units.
         */
        virtual int run(long long int numTimeUnits) = 0;

        virtual int stop () = 0;
        virtual int resume () = 0;
    };
}

#endif //_SCHEDULER_
