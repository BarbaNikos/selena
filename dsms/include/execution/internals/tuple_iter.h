//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _TUPLE_ITER_
#define _TUPLE_ITER_

#include "execution/internals/tuple.h"

namespace Execution {
    class TupleIterator {
    public:
        virtual ~TupleIterator () {}

        /**
         * Get the next tuple in this iteration
         *
         * @param   tuple   (output) next tuple
         * @return           true if next tuple present,
         *                   false if we reached the end.
         */
        virtual bool getNext (Tuple& tuple) = 0;
    };
}

#endif //_TUPLE_ITER_
