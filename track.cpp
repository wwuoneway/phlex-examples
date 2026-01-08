#include "track.hpp"

namespace examples {
  track::track(ROOT::Math::XYZTVector const& start, ROOT::Math::XYZTVector const& end):
    m_start_position(start),
    m_end_position(end)
  {
  }

  ROOT::Math::XYZTVector const& track::start() const
  {
    return m_start_position;
  }

  ROOT::Math::XYZTVector const& track::end() const
  {
    return m_end_position;
  }

  ROOT::Math::XYZVector track::direction() const
  {
    return (m_end_position.Vect() - m_start_position.Vect()).Unit();
  }

  double track::length() const
  {
    return sqrt((m_end_position.Vect() - m_start_position.Vect()).mag2());
  }

  double track::delta_t() const
  {
    return m_end_position.T() - m_start_position.T();
  }
}
