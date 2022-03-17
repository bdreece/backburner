/**
 * @file	macro.h
 * @brief 	Future type definition and function macros
 * @author	Brian Reece
 * @version 0.1
 * @date	03/15/2022
 */

#ifndef BACKBURNER_MACRO_H
#define BACKBURNER_MACRO_H

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#define BACKBURNER_DECLARE(T, name)                                            \
  typedef struct {                                                             \
    bool ready;                                                                \
    pthread_t id;                                                              \
    T *data;                                                                   \
  } name##_future_t;                                                           \
                                                                               \
  typedef struct {                                                             \
    T (*fn)(void *);                                                           \
    void *arg;                                                                 \
    bool *ready;                                                               \
  } name##_functor_t;                                                          \
                                                                               \
  void *exec_##name(void *);                                                   \
  name##_future_t async_##name(T (*)(void *), void *);                         \
  T await_##name(name##_future_t);                                             \
  bool poll_##name(name##_future_t);

#define BACKBURNER_DEFINE(T, name)                                             \
  void *exec_##name(void *arg) {                                               \
    name##_functor_t *functor = (name##_functor_t *)arg;                       \
    T *retval = (T *)malloc(sizeof(T));                                        \
    *retval = functor->fn(functor->arg);                                       \
    *functor->ready = true;                                                    \
    free(functor);                                                             \
    return (void *)retval;                                                     \
  }                                                                            \
                                                                               \
  name##_future_t async_##name(T (*fn)(void *), void *arg) {                   \
    name##_future_t future;                                                    \
    future.ready = false;                                                      \
    name##_functor_t *functor =                                                \
        (name##_functor_t *)malloc(sizeof(name##_functor_t));                  \
    functor->fn = fn;                                                          \
    functor->arg = arg;                                                        \
    functor->ready = &future.ready;                                            \
    assert(pthread_create(&future.id, NULL, &exec_##name, (void *)functor) ==  \
           0);                                                                 \
    return future;                                                             \
  }                                                                            \
                                                                               \
  T await_##name(name##_future_t future) {                                     \
    T data;                                                                    \
    assert(pthread_join(future.id, (void **)&future.data) == 0);               \
    data = *future.data;                                                       \
    free(future.data);                                                         \
    return data;                                                               \
  }                                                                            \
                                                                               \
  bool poll_##name(name##_future_t future) { return future.ready; }

#define BACKBURNER_DERIVE(T, name)                                             \
  BACKBURNER_DECLARE(T, name)                                                  \
  BACKBURNER_DEFINE(T, name)

#endif // BACKBURNER_MACRO_H
