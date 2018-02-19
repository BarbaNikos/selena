//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _SYN_MONITOR_
#define _SYN_MONITOR_

#include <dsms/include/execution/monitors/property_monitor.h>

namespace Monitor {

    /**
     * A generic monitor for synopses
     */
    class SynMonitor : public PropertyMonitor {
    private:
        /// Size of synopsis
        int numTuples;

        /// Max size of synopsis
        int maxTuples;

    public:
        SynMonitor ();
        virtual ~SynMonitor ();

        void logIns ();
        void logDel ();
        virtual int getIntProperty (int property, int &val);
    };
}
#endif //_SYN_MONITOR_
