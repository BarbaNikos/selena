//
// Created by Nikos R. Katsipoulakis on 2/8/18.
//
#pragma once
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>

#ifndef _TABLE_SOURCE_
#include <dsms/include/interface/table_source.h>
#endif // !_TABLE_SOURCE_

#ifndef _CONSTANTS_
#include <dsms/include/common/constants.h>
#endif // !_CONSTANTS_

#ifdef _DM_
#include <cassert>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) {}
#endif

#ifndef _MEMORY_SOURCE_
#define _MEMORY_SOURCE_
namespace Client {

    class MemoryTuple {
    public:
        virtual ~MemoryTuple() {}
        virtual char* serialize() const { return nullptr; }
    };

    class SampleTuple : MemoryTuple {
    private:
        int timestamp;
        char location[8];
        float cost;
    public:
        SampleTuple(const int ts, const std::string& loc,
                    const float cost_) : timestamp(ts), cost(cost_) {
            const char* l_ = loc.c_str();
            ASSERT(strlen(l_) <= 8);
            memcpy(location, l_, 8 * sizeof(char));
        }

        char* serialize() const override {
            size_t len = sizeof(int) + 8 * sizeof(char) + sizeof(float);
            char* buffer = new char[len];
            memcpy(buffer, &timestamp, sizeof(int));
            memcpy(buffer + sizeof(int), location, 8 * sizeof(char));
            memcpy(buffer + sizeof(int) + 8 * sizeof(char), &cost, sizeof(float));
            std::cout << buffer << "\n";
            return buffer;
        }

        void deserialize(char* &buffer) {
            memcpy(&timestamp, buffer, sizeof(int));
            memcpy(location, buffer + sizeof(int), 8 * sizeof(char));
            location[8] = '\0';
            memcpy(&cost, buffer + sizeof(int) + 8 * sizeof(char), sizeof(float));
            delete[] buffer;
            buffer = nullptr;
        }
    };

    class MemorySource : public Interface::TableSource {
    private:
        std::vector<MemoryTuple> input;

        std::vector<MemoryTuple>::const_iterator input_itr;

        static const unsigned int MAX_TUPLE_SIZE = 256;

        char tupleBuffer_[MAX_TUPLE_SIZE];

        enum Type {
            INT, FLOAT, CHAR, BYTE
        };

        Type attrTypes_[MAX_ATTRS];

        size_t attrLen_[MAX_ATTRS];

        size_t offset_[MAX_ATTRS];

        size_t numAttrs_;

        size_t tupleLen_;

    public:
        MemorySource(const std::string& schema,
                     const std::vector<MemoryTuple>& source) : input(source) {}

        ~MemorySource() {}

        int start() {
            int rc;
            if (input.size() == 0)
                return -1;
            //if ((rc = parseSchema(schema)) != 0)
            //return rc;
            //if ((rc = computeOffsets()) != 0)
            //return rc;
            input_itr = input.cbegin();
            return 0;
        }

        int getNext(char *&tuple, unsigned int &len, bool &isHeartbeat) {
            int rc;
            isHeartbeat = false;
            len = tupleLen_;
            if (input_itr != input.cbegin()) {
                // push it upwards and store it to buffer
                tuple = input_itr->serialize();
            } else if (input_itr == input.cbegin()) {
                tuple = 0;
                len = 0;
            } else {
                return -1;
            }
            return 0;
        }

        int end() {
            return 0;
        }

    private:
        /*
        int parseSchema(char** ptr) {
          numAttrs_ = 0;
          while (*ptr && numAttrs_ < MAX_ATTRS) {
            switch (*ptr++) {
              case 'i':
                attrTypes_[numAttrs_++] = INT;
                break;
              case 'f':
                attrTypes_[numAttrs_++] = FLOAT;
                break;
              case 'b':
                attrTypes_[numAttrs_++] = BYTE;
                break;
              case 'c':
                attrTypes_[numAttrs_++] = CHAR;
                attrLen_[numAttrs] = strtol(*ptr, ptr, 10);
                if (attrLen_[numAttrs] <= 0)
                  return -1;
                numAttrs++;
                break;
              default:
                return -1;
            }
            if (*ptr && *ptr != ',')
              return -1;
            if (*ptr == ',')
              ptr++;
          }
          return 0;
        }
        */
/*
    int computeOffsets() {
      int offset = 0;
      for (size_t a = 0; a < numAttrs_; a++) {
        offset_[a] = offset;
        switch (attrTypes_[a]) {
          case INT:
            offset += sizeof(int);
            break;
          case FLOAT:
            offset += sizeof(float);
          case CHAR:
            offset += attrLen_[a];
            break;
          case BYTE:
            offset += 1;
            break;
          default:
            return -1;
        }
      }
      tupleLen_ = offset;
      return 0;
    }
*/
    };
}

#endif //_MEMORY_SOURCE_
