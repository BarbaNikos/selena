//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//

#ifndef _INDEX_
#define _INDEX_
/**
 * The index interface.
 */
#include <dsms/include/execution/internals/tuple.h>
#include <dsms/include/execution/internals/tuple_iter.h>
#include <dsms/include/execution/monitors/property_monitor.h>

namespace Execution {

#ifdef _MONITOR_
    class Index : public Monitor::PropertyMonitor {
	public:
		Index () {}
		virtual ~Index() {}
		virtual int insertTuple (Tuple tuple) = 0;
		virtual int deleteTuple (Tuple tuple) = 0;
		virtual int getScan (TupleIterator *& iter) = 0;
		virtual int releaseScan (TupleIterator *iter) = 0;
	};
#else
    class Index {
    public:
        Index () {}
        virtual ~Index() {}
        virtual int insertTuple (Tuple tuple) = 0;
        virtual int deleteTuple (Tuple tuple) = 0;
        virtual int getScan (TupleIterator *& iter) = 0;
        virtual int releaseScan (TupleIterator *iter) = 0;
    };
#endif

}

#endif //_INDEX_
