find_package(
  Boost
  COMPONENTS unit_test_framework
  REQUIRED)

enable_testing()
add_executable(backburner_await_one await_one.cpp)
target_include_directories(backburner_await_one PUBLIC ../inc)
target_link_libraries(backburner_await_one
                      PUBLIC pthread ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME await_one
         COMMAND ./backburner_await_one
                 --logger=HRF,message,backburner_tests.log -r detailed)

add_executable(backburner_await_silly await_silly.cpp)
target_include_directories(backburner_await_silly PUBLIC ../inc)
target_link_libraries(backburner_await_silly
                      PUBLIC pthread ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME await_silly
         COMMAND ./backburner_await_silly
                 --logger=HRF,message,backburner_tests.log -r detailed)

add_executable(backburner_await_all await_all.cpp)
target_include_directories(backburner_await_all PUBLIC ../inc)
target_link_libraries(backburner_await_all
                      PUBLIC pthread ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME await_all
         COMMAND ./backburner_await_all
                 --logger=HRF,message,backburner_tests.log -r detailed)

add_executable(backburner_poll_one poll_one.cpp)
target_include_directories(backburner_poll_one PUBLIC ../inc)
target_link_libraries(backburner_poll_one
                      PUBLIC pthread ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME poll_one
         COMMAND ./backburner_poll_one
                 --logger=HRF,message,backburner_tests.log -r detailed)
