//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _OP_MONITOR_
#define _OP_MONITOR_

#include <dsms/include/execution/monitors/property_monitor.h>
#include <dsms/include/execution/monitors/timer.h>
#include <dsms/include/common/types.h>

namespace Monitor {

    /**
     * A generic monitor for operators.  Currently keeps track of the time
     * used by an operator.
     */

    class OperatorMonitor : public PropertyMonitor {
    private:
        Timer timer;
        Timestamp outTs;

        /// The number of joined output tuples
        long numJoined;

        /// The number of input tuples seen (inner and outer)
        long numInput;

    public:
        OperatorMonitor ();
        virtual ~OperatorMonitor();

        void startTimer ();
        void stopTimer ();
        void logOutTs (Timestamp ts);

        void logJoin () {
            numJoined ++;
        }

        void logInput () {
            numInput ++;
        }

        virtual int getDoubleProperty (int property, double &val);
        virtual int getIntProperty (int property, int &val);
    };
}
#endif //_OP_MONITOR_
