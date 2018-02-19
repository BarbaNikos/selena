//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#include <dsms/include/execution/monitors/join_monitor.h>
#include <dsms/include/execution/monitors/property.h>

using namespace Monitor;

#include <iostream>
using namespace std;

int JoinMonitor::getIntProperty (int property, int &val)
{
    if (property == JOIN_NINPUT) {
        val = numInput;
        return 0;
    }

    if (property == JOIN_NOUTPUT) {
        val = numJoined;
        return 0;
    }

    return PropertyMonitor::getIntProperty (property, val);
}