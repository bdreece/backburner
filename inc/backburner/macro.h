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
  } name##_actor_t;                                                            \
                                                                               \
  void *name##_exec(void *);                                                   \
  name##_future_t future_##name(T (*)(void *), void *);                        \
  T await_##name(name##_future_t);                                             \
  void awaitall_##name(T *, name##_future_t *, size_t);                        \
  bool poll_##name(name##_future_t);

#define BACKBURNER_DEFINE(T, name)                                             \
  void *exec_##name(void *arg) {                                               \
    name##_actor_t *actor = (name##_actor_t *)arg;                             \
    T *retval = (T *)malloc(sizeof(T));                                        \
    *retval = actor->fn(actor->arg);                                           \
    *actor->ready = true;                                                      \
    free(actor);                                                               \
    return (void *)retval;                                                     \
  }                                                                            \
                                                                               \
  name##_future_t future_##name(T (*fn)(void *), void *arg) {                  \
    name##_future_t future;                                                    \
    future.ready = false;                                                      \
    name##_actor_t *actor = (name##_actor_t *)malloc(sizeof(name##_actor_t));  \
    actor->fn = fn;                                                            \
    actor->arg = arg;                                                          \
    actor->ready = &future.ready;                                              \
    assert(pthread_create(&future.id, NULL, &exec_##name, (void *)actor) ==    \
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
  void awaitall_##name(T *outputs, name##_future_t *futures, size_t n) {       \
    for (int i = 0; i < n; i++) {                                              \
      outputs[i] = await_##name(futures[i]);                                   \
    }                                                                          \
  }                                                                            \
                                                                               \
  bool poll_##name(name##_future_t future) { return future.ready; }

#define BACKBURNER_DERIVE(T, name)                                             \
  BACKBURNER_DECLARE(T, name)                                                  \
  BACKBURNER_DEFINE(T, name)

#endif // BACKBURNER_MACRO_H
