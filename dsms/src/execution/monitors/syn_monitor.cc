//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#include <dsms/include/execution/monitors/syn_monitor.h>
#include <dsms/include/common/debug.h>
#include <dsms/include/execution/monitors/property.h>

using namespace Monitor;

SynMonitor::SynMonitor ()
{
    numTuples = 0;
    maxTuples = 0;
}

SynMonitor::~SynMonitor () {}

void SynMonitor::logIns ()
{
    ASSERT (numTuples >= 0);
    ASSERT (maxTuples >= 0);

    if (++numTuples > maxTuples)
        maxTuples = numTuples;
}

void SynMonitor::logDel ()
{
    numTuples --;

    ASSERT (numTuples >= 0);
}

int SynMonitor::getIntProperty (int property, int &val)
{
    if (property == SYN_MAX_TUPLES) {
        val = maxTuples;
        return 0;
    }

    if (property == SYN_NUM_TUPLES) {
        val = numTuples;
        return 0;
    }

    return PropertyMonitor::getIntProperty (property, val);
}
