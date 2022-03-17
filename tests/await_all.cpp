#define BOOST_TEST_MODULE backburner_await_all
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

BOOST_AUTO_TEST_CASE(await_all) {
  int seconds = 5;
  int_future_t futures[5] = {
      future_int(expensive, (void *)&seconds),
      future_int(expensive, (void *)&seconds),
      future_int(expensive, (void *)&seconds),
      future_int(expensive, (void *)&seconds),
      future_int(expensive, (void *)&seconds),
  };

  int output[5];
  awaitall_int(output, futures, 5);
  for (int i = 0; i < 5; i++) {
    BOOST_TEST(output[i] == seconds);
  }
}
