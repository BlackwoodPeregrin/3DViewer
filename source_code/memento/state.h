#ifndef STATE_H
#define STATE_H

#include <QVector>

#include "../view/camera3D.h"
#include "../model/object3D.h"
#include "../model/settings/groupSetting.h"

namespace s21_3DViewer
{
class State
{
public:
  State(const GroupSettings& gS, const Camera3D& c, const Object3D& o)
  {
    m_gS = gS;
    m_c = c;
    m_o = o;
  }

  State(const State& other)
  {
    *this = other;
  }

  State& operator=(const State& other)
  {
    m_gS = other.m_gS;
    m_c = other.m_c;
    m_o = other.m_o;
  }

  const GroupSettings& groupSetting() const
  {
    return m_gS;
  }

  const Camera3D& camera() const
  {
    return m_c;
  }

  const Object3D& object() const
  {
    return m_o;
  }

private:
  GroupSettings m_gS;
  Camera3D m_c;
  Object3D m_o;
};
}  // namespace s21_3DViewer

#endif  // STATE_H
