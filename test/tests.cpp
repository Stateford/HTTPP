#include "../src/network/url.h"
#include <gtest/gtest.h>
#include <string>

TEST(UrlTest, Valid) {
    const std::string fullUrl = "http://test.com/foo";
    Network::URL url(fullUrl);
    ASSERT_EQ(url.getHost(), "test.com");
}

TEST(UrlTest, Invalid) {
    const std::string fullUrl = "rtmp://test.com/foo";
    Network::URL url(fullUrl);
    ASSERT_EQ(url.getHost(), "test.com");
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
