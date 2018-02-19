//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _ELEMENT_
#define _ELEMENT_

#include "execution/internals/tuple.h"
#include "common/types.h"

namespace Execution {
    enum ElementKind {
        E_PLUS, E_MINUS, E_HEARTBEAT
    };

    struct Element {
        ElementKind  kind;
        Tuple        tuple;
        Timestamp    timestamp;

        Element () : kind (E_PLUS), tuple (0), timestamp (0) {}

        Element (ElementKind _k, Tuple _t, Timestamp _ts)
                : kind (_k), tuple (_t), timestamp (_ts) {}

        static Element Heartbeat (Timestamp _tstamp) {
            Element e;

            e.kind = E_HEARTBEAT;
            e.timestamp = _tstamp;

            return e;
        }
    };
}

#endif //_ELEMENT_
