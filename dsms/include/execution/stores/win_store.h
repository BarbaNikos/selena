//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//

#ifndef _WIN_STORE_
#define _WIN_STORE_
/**
 * @file         win_syn_store.h
 * @brief        Store that supports window synopsis interface
 */
#include "execution/internals/tuple.h"
#include "common/types.h"

namespace Execution {

    class WinStore {
    public:

        virtual int insertTuple_w (Tuple tuple, Timestamp timestamp,
                                   unsigned int stubId) = 0;

        virtual bool isEmpty_w (unsigned int stubId) const = 0;

        virtual int getOldestTuple_w (Tuple &tuple,
                                      Timestamp &timestamp,
                                      unsigned int stubId) const = 0;

        virtual int deleteOldestTuple_w (unsigned int stubId) = 0;
    };
}

#endif //_WIN_STORE_
