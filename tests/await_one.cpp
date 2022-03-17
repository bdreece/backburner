#include <sys/cdefs.h>
#define BOOST_TEST_MODULE backburner_await_one
#include <boost/test/unit_test.hpp>

#include <unistd.h>

extern "C" {
#include "backburner/macro.h"
BACKBURNER_DERIVE(int, int)
}

__attribute_noinline__ int expensive(void *arg) {
  int seconds = *(int *)arg;
  sleep(seconds);
  return seconds;
}

BOOST_AUTO_TEST_CASE(await_one) {
  int seconds = 5;
  BOOST_TEST(seconds == await_int(async_int(expensive, (void *)&seconds)));
}
