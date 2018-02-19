//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//

#ifndef _WIN_SYN_IMPL_
#define _WIN_SYN_IMPL_

#ifndef _WIN_SYN_
#include <dsms/include/execution/synopses/win_syn.h>
#endif

#ifndef _WIN_STORE_
#include <dsms/include/execution/stores/win_store.h>
#endif

#include <ostream>
namespace Execution {
    class WindowSynopsisImpl : public WindowSynopsis {
    private:
        unsigned int           id;

        /// System log
        std::ostream          &LOG;

        unsigned int           stubId;
        WinStore *store;

    public:
        WindowSynopsisImpl (unsigned int id, std::ostream& LOG);
        ~WindowSynopsisImpl();

        int setStore (WinStore *store, unsigned int stubId);

        int insertTuple (Tuple tuple, Timestamp timestamp);
        bool isEmpty() const;
        int getOldestTuple (Tuple& tuple, Timestamp& timestamp);
        int deleteOldestTuple();
    };
}

#endif //_WIN_SYN_IMPL_
