//
// Created by Nikos R. Katsipoulakis on 2/12/18.
//
#include "gtest/gtest.h"

#include <generic_client/include/generic_client.h>

class StreamDsmsTest : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
    GenericClient client;
};

TEST_F(StreamDsmsTest, TestOne) {
    ASSERT_EQ(0, 0);
}