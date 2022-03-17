#define BOOST_TEST_MODULE backburner_tests
#include <boost/test/unit_test.hpp>

#include <unistd.h>

extern "C" {
#define BACKBURNER_PRIMITIVES
#include "backburner.h"
}

static int expensive(void *arg) {
  int *seconds = (int *)arg;
  sleep(*seconds);
  return *seconds;
}

BOOST_AUTO_TEST_CASE(poll_one) {
  int seconds = 5;
  int_future_t future = future_int(expensive, (void *)&seconds);
  BOOST_TEST(poll_int(future) == false);
  sleep(6);
  BOOST_TEST(poll_int(future) == true);
}
