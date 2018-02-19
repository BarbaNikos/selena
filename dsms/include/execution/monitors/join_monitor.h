//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _JOIN_MONITOR_
#define _JOIN_MONITOR_

#include <dsms/include/execution/monitors/property_monitor.h>

namespace Monitor {

    class JoinMonitor : public PropertyMonitor {
    private:
        /// The number of joined output tuples
        long numJoined;

        /// The number of input tuples seen (inner and outer)
        long numInput;

    public:
        JoinMonitor () {
            numJoined = 0;
            numInput = 0;
        }

        virtual ~JoinMonitor () { }

        void logJoin () {
            numJoined ++;
        }

        void logInput () {
            numInput ++;
        }

        virtual int getIntProperty (int property, int&val);
    };
}
#endif //_JOIN_MONITOR_
