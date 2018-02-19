//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//

#ifndef _SHARED_QUEUE_WRITER_
#define _SHARED_QUEUE_WRITER_

#include "execution/queues/queue.h"
#include "execution/memory/memory_mgr.h"
#include "execution/stores/store_alloc.h"

namespace Execution {
    class SharedQueueWriter : public Queue {
        /// System-wide unique id
        unsigned int id;

        /// System log
        std::ostream &LOG;

        /// System memory manager
        MemoryManager *memMgr;

        /// Size of pages allocated by memory manager
        unsigned int pageSize;

        /// Number of page I am allowed to allocate
        unsigned int numPages;

        /// Offset of the next page pointer from the start of the page
        unsigned int nextPtrOffset;

        /// The offset of the next page pointer from the last element of a
        /// page
        unsigned int nextPtrOffset_le;

        /// Number of elements that can be stored per page
        unsigned int numElementsPerPage;

        /// Maximum number of elements I can hold
        unsigned int maxElements;

        /// Maximum number of readers we allow
        static const unsigned int MAX_READERS = 10;

        /// Number of readers
        unsigned int numReaders;

        /// Pointer to an element in the queue: contains the true pointer
        /// and the position of the element within the page
        struct EPtr {
            Element *element;
            unsigned int posInPage;
        };

        /// The next dequeue element for each reader
        EPtr nextDequeue [MAX_READERS];

        /// The position where the next element is enqueued
        EPtr nextEnqueue;

        /// Total number of dequeues by a reader
        unsigned int totalDequeued [MAX_READERS];

        /// Total number of enqueues
        unsigned int totalEnqueued;

        /// The reader who lags behind the most
        unsigned int slowestReader;

        /// Storage allocated who alloced tuples passing through us
        StorageAlloc *store;

    public:
        SharedQueueWriter (unsigned int id, std::ostream &LOG);
        virtual ~SharedQueueWriter ();

        //------------------------------------------------------------
        // Initialization routines
        //------------------------------------------------------------

        int setNumPages (unsigned int numPages);
        int setMemoryManager (MemoryManager *memMgr);
        int setNumReaders (unsigned int numReaders);
        int setStore (StorageAlloc *store);
        int initialize ();

        //------------------------------------------------------------
        // Inherited from Queue
        //------------------------------------------------------------
        bool enqueue (Element element);
        bool dequeue (Element &element); // not implemented
        bool peek (Element &element) const; // not implemented
        bool isFull () const;
        bool isEmpty () const; // not implemented

        //------------------------------------------------------------
        // Called by the reader
        //------------------------------------------------------------
        bool dequeue (Element &element, unsigned int readerId);
        bool peek (Element &element, unsigned int readerId) const;
        bool isFull (unsigned int readerId) const;
        bool isEmpty (unsigned int readerId) const;

    private:
        int computePageLayout ();
        int initState ();
    };
}

#endif //_SHARED_QUEUE_WRITER_
