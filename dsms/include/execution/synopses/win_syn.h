//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//

#ifndef _WIN_SYN_
#define _WIN_SYN_
/**
 * @file            win_syn.h
 * @brief           A window synopsis interface.
 */
#ifndef _TUPLE_
#include <dsms/include/execution/internals/tuple.h>
#endif

#ifndef _TYPES_
#include <dsms/include/common/types.h>
#endif

#ifndef _SYN_MONITOR_
#include <dsms/include/execution/monitors/syn_monitor.h>
#endif

#ifdef _MONITOR_
#endif
namespace Execution {
#ifdef _MONITOR_
    class WindowSynopsis : public Monitor::SynMonitor {
	public:
		virtual ~WindowSynopsis() {}

		virtual int insertTuple (Tuple tuple,
								 Timestamp timestamp) = 0;

		virtual bool isEmpty() const = 0;

		virtual int getOldestTuple (Tuple& tuple,
									Timestamp& timestamp) = 0;

		virtual int deleteOldestTuple () = 0;
	};
#else
    class WindowSynopsis : public Monitor::SynMonitor {
    public:
        virtual ~WindowSynopsis() {}

        virtual int insertTuple (Tuple tuple,
                                 Timestamp timestamp) = 0;

        virtual bool isEmpty() const = 0;

        virtual int getOldestTuple (Tuple& tuple,
                                    Timestamp& timestamp) = 0;

        virtual int deleteOldestTuple () = 0;
    };
#endif
}

#endif //_WIN_SYN_
