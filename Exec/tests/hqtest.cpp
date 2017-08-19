
#include <algorithm>

#include "../src/HashQueue.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"


TEST(hashqueue, push_test) {
    HashQueue<int> hq;
    hq.push(1);
    hq.push(2);
    hq.push(3);
    hq.push(4);
    EXPECT_EQ(hq.size(), 4);
    std::vector<int> hq_elements = hq.get_all_elements();
    ASSERT_THAT(hq_elements, testing::ElementsAre(1,2,3,4));

}

TEST(hashqueue, pop_test) {

    HashQueue<int> hq;
    hq.push(1);
    hq.push(2);
    hq.push(3);
    hq.push(4);
    EXPECT_EQ(hq.size(), 4);
    std::vector<int> hq_elements = hq.get_all_elements();
    ASSERT_THAT(hq_elements, testing::ElementsAre(1,2,3,4));
    hq.pop();
    hq.pop();
    EXPECT_EQ(hq.size(), 2);
    hq_elements = hq.get_all_elements();
    ASSERT_THAT(hq_elements, testing::ElementsAre(3,4));
    hq.pop();
    hq.pop();
    EXPECT_EQ(hq.size(), 0);
    EXPECT_EQ(hq.is_empty(), true);
    ASSERT_THAT(hq_elements, testing::ElementsAre());

}

