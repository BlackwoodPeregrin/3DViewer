#ifndef MEMENTO_H
#define MEMENTO_H

#include "state.h"

namespace s21_3DViewer
{
class Memento
{
public:
  Memento() = default;
  ~Memento() = default;

  Memento(Memento const&) = delete;
  Memento(Memento&&) = delete;

  Memento& operator=(Memento const&) = delete;
  Memento& operator=(Memento&&) = delete;

  State* statePrev()
  {
    if (m_prev.isEmpty())
      return nullptr;

    State s = m_prev.back();
    m_prev.pop_back();
    return &s;
  }

  State* stateNext()
  {
    if (m_next.isEmpty())
      return nullptr;

    State s = m_next.back();
    m_next.pop_back();
    return &s;
  }

  void backupPrev(const State& s)
  {
    m_prev.push_back(s);
  }

  void backupNext(const State& s)
  {
    m_next.push_back(s);
  }

private:
  QVector<State> m_prev;
  QVector<State> m_next;
};

}  // namespace s21_3DViewer

#endif  // MEMENTO_H
