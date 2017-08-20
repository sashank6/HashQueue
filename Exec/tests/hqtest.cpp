
#include <algorithm>

#include "../src/HashQueue.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"


TEST(hashqueue, push_test) {
    double arr[] = {1.5,2.5,3.5,4.5,5.5,1.5,2.4,8.9,3.5,1.2};
    HashQueue<double> hq;
    size_t arr_len = sizeof(arr)/sizeof(*arr);
    for(int i=0;i<arr_len;i++) {
        hq.push(arr[i]);
    }
    ASSERT_THAT(hq.get_all_elements(),testing::ElementsAreArray(arr));
    EXPECT_EQ(hq.size(), arr_len);
    EXPECT_EQ(hq.is_empty(), false);
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
    hq_elements = hq.get_all_elements();
    ASSERT_THAT(hq_elements, testing::ElementsAre());

}

TEST(hashqueue, get_count_test) {
    HashQueue<double> hq;
    hq.push(3.5);
    hq.push(3.513);
    hq.push(4.5);
    hq.push(3.5);
    EXPECT_EQ(hq.get_count(3.5), 2);
    EXPECT_EQ(hq.get_count(3.513), 1);
    EXPECT_EQ(hq.get_count(4.5), 1);
    EXPECT_EQ(hq.get_count(6.12), 0);
}

TEST(hashqueue, has_key_test) {
    double arr[] = {1.5,2.5,3.5,4.5,5.5,1.5,2.4,8.9,3.5,1.2};
    HashQueue<double> hq;
    size_t arr_len = sizeof(arr)/sizeof(*arr);
    for(int i=0;i<arr_len;i++) {
        hq.push(arr[i]);
    }
    for(int i=0;i<arr_len;i++) {
        EXPECT_EQ(hq.has_key(arr[i]), true);
    }

    EXPECT_EQ(hq.has_key(12), false);
    EXPECT_EQ(hq.has_key(-1), false);
}

