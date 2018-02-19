//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#include <dsms/include/execution/monitors/queue_monitor.h>
#include <dsms/include/execution/monitors/property.h>

using namespace Monitor;

int QueueMonitor::getIntProperty (int property, int&val) {

    if (property == QUEUE_NUM_ELEM) {
        val = numElements;
        return 0;
    }

    if (property == QUEUE_LAST_TS) {
        val = (int)lastTs;
        return 0;
    }

    return PropertyMonitor::getIntProperty (property, val);
}