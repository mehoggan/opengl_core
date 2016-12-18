/* Copyright (C)
 *
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writting, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef OPENGL_CORE_CONCURRENT_QUEUE_H_INCLUDED
#define OPENGL_CORE_CONCURRENT_QUEUE_H_INCLUDED

#include "opengl_core/core/non_copyable.h"

#include <condition_variable>
#include <queue>
#include <thread>

namespace opengl_core
{
  template<typename T>
  class concurrent_queue : public non_copyable
  {
  private:
     std::queue<T> m_queue;
     mutable std::mutex m_mutex;
     std::condition_variable m_condition;

  public:
    void push(const T &data)
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_queue.push(data);
      m_condition.notify_all();
    }

    bool empty() const
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_queue.empty();
    }

    void clear()
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      std::queue<T> empty;
      std::swap(m_queue, empty);
      m_condition.notify_all();
    }

    bool try_pop(T &value)
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      if(m_queue.empty()) {
        return false;
      }

      value = m_queue.front();
      m_queue.pop();
      return true;
    }

    void wait_and_pop(T &value)
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_condition.wait(lock, queue_not_empty(m_queue));
      if (!m_queue.empty()) {
        value = m_queue.front();
        m_queue.pop();
      }
    }

    template <typename D>
    bool timed_wait_and_pop(T &Value, const D &wait_for)
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      if(!m_condition.timed_wait(lock, wait_for, queue_not_empty(m_queue))) {
        return false;
      }

      value = m_queue.front();
      m_queue.pop();
      return true;
    }

    struct queue_not_empty
    {
      std::queue<T> &m_queue;

      queue_not_empty(std::queue<T> &queue)
        : m_queue(queue)
      {}

      bool operator()() const
      {
        return !m_queue.empty();
      }
    };
  };
}

#endif

