//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//

#ifndef _DEBUG_
#include "../../../include/common/debug.h"
#include "../../../include/execution/queues/shared_queue_reader.h"

#endif

using namespace Execution;
using namespace std;

SharedQueueReader::SharedQueueReader (unsigned int id, ostream& _LOG)
        : LOG (_LOG)
{
    this -> id = id;
    this -> writer = 0;
}

SharedQueueReader::~SharedQueueReader () {}

int SharedQueueReader::setWriter (SharedQueueWriter *writer)
{
    ASSERT (writer);

    this -> writer = writer;
    return 0;
}

int SharedQueueReader::setReaderId (unsigned int readerId)
{
    this -> readerId = readerId;
    return 0;
}

bool SharedQueueReader::enqueue (Element element)
{
    // should never be called
    ASSERT (0);

    return -1;
}

bool SharedQueueReader::dequeue (Element &element)
{
    return writer -> dequeue (element, readerId);
}

bool SharedQueueReader::peek (Element &element) const
{
    return writer -> peek (element, readerId);
}

bool SharedQueueReader::isFull () const
{
    return writer -> isFull (readerId);
}

bool SharedQueueReader::isEmpty () const
{
    return writer -> isEmpty (readerId);
}
