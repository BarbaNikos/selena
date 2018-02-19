//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//

#ifndef _SHARED_QUEUE_READER_
#define _SHARED_QUEUE_READER_

#include "execution/queues/queue.h"
#include "execution/queues/shared_queue_writer.h"

namespace Execution {
    class SharedQueueReader : public Queue {
        /// System-wide unique id
        unsigned int id;

        /// System log
        std::ostream &LOG;

        /// shared writer queue from which we read dequeues
        SharedQueueWriter *writer;

        /// The Id by which we identify ourselves to the writer
        unsigned int readerId;

    public:
        SharedQueueReader (unsigned int id, std::ostream& LOG);
        virtual ~SharedQueueReader ();

        //------------------------------------------------------------
        // Initialization routines
        //------------------------------------------------------------
        int setWriter (SharedQueueWriter *writer);
        int setReaderId (unsigned int readerId);

        //------------------------------------------------------------
        // Inherited from Queue
        //------------------------------------------------------------
        bool enqueue (Element element); // not implemented
        bool dequeue (Element &element);
        bool peek (Element &element) const;
        bool isFull () const;
        bool isEmpty () const;
    };
}

#endif //_SHARED_QUEUE_READER_
