#define BOOST_TEST_MODULE backburner_await_silly
#include <boost/test/unit_test.hpp>

#include <unistd.h>

extern "C" {
#include "backburner/macro.h"
BACKBURNER_DERIVE(int, int);
}

static int expensive(void *arg) {
  int *seconds = (int *)arg;
  sleep(*seconds);
  return *seconds;
}

BOOST_AUTO_TEST_CASE(await_silly) {
  int seconds = 5;
  BOOST_TEST(seconds == await_int(async_int(expensive, (void *)&seconds)));
  BOOST_TEST(seconds == await_int(async_int(expensive, (void *)&seconds)));
  BOOST_TEST(seconds == await_int(async_int(expensive, (void *)&seconds)));
  BOOST_TEST(seconds == await_int(async_int(expensive, (void *)&seconds)));
  BOOST_TEST(seconds == await_int(async_int(expensive, (void *)&seconds)));
}
