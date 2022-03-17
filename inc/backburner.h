/**
 * @file	backburner.h
 * @brief 	Future type definition and function macros
 * @author	Brian Reece
 * @version 0.1
 * @date	03/15/2022
 */

#ifndef BACKBURNER_H
#define BACKBURNER_H

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#define BACKBURNER_DEFINE(T, name)                                             \
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
  void *name##_exec(void *arg) {                                               \
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
    assert(pthread_create(&future.id, NULL, &name##_exec, (void *)actor) ==    \
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

#ifdef BACKBURNER_PRIMITIVES
BACKBURNER_DEFINE(char, char);
BACKBURNER_DEFINE(short, short);
BACKBURNER_DEFINE(int, int);
BACKBURNER_DEFINE(long, long);
BACKBURNER_DEFINE(long long, long_long);
BACKBURNER_DEFINE(bool, bool);
#endif // BACKBURNER_PRIMITIVES

#ifdef BACKBURNER_INTS
#include <stddef.h>
#include <stdint.h>
BACKBURNER_DEFINE(uint8_t, u8)
BACKBURNER_DEFINE(uint16_t, u16)
BACKBURNER_DEFINE(uint32_t, u32)
BACKBURNER_DEFINE(uint64_t, u64)
BACKBURNER_DEFINE(int8_t, i8)
BACKBURNER_DEFINE(int16_t, i16)
BACKBURNER_DEFINE(int32_t, i32)
BACKBURNER_DEFINE(size_t, usize)
BACKBURNER_DEFINE(uintptr_t, uintptr)
BACKBURNER_DEFINE(ptrdiff_t, ptrdiff)
#endif // BACKBURNER_INTS

#ifdef BACKBURNER_POINTERS
BACKBURNER_DEFINE(char *, char_ptr);
BACKBURNER_DEFINE(short *, short_ptr);
BACKBURNER_DEFINE(int *, int_ptr);
BACKBURNER_DEFINE(long *, long_ptr);
BACKBURNER_DEFINE(long long *, long_long_ptr);
BACKBURNER_DEFINE(bool *, bool_ptr);
BACKBURNER_DEFINE(void *, void_ptr);
#endif // BACKBURNER_POINTERS

#endif // FUTURE_H
