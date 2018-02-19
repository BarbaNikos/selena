//
// Created by Nikos R. Katsipoulakis on 2/18/18.
//

#ifndef _CHAIN_
#define _CHAIN_

#ifndef _SCHEDULER_
#include <dsms/include/execution/scheduler/scheduler.h>
#include <ostream>

#endif
namespace Execution {
    class ChainScheduler : public Scheduler {
    private:
        /*
         * maximum number of operators that are going to be scheduled
         */
        static const unsigned int MAX_OPS = 100;
        Operator *ops[MAX_OPS];
        unsigned int numOps;
        bool bStop;
        std::ostream &LOG;
    public:
        ChainScheduler(std::ostream& LOG);
        virtual ~ChainScheduler();
        int addOperator(Operator *op);
        int run(long long int numTimeUnits);
        int stop();
        int resume();
        unsigned int getOperatorInputQueueSize(Operator *op);
        unsigned int isRelationalOperator(Operator *op);
        std::string getOperatorName(Operator *op);
        void calculateMemoryConsumption();
    };
}
#endif //_CHAIN_
