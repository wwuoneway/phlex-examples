//An examples::track is the result of a fit to a collection of points.  It represents energy deposits
//from a single particle starting at a position and time, moving in a single direction, and ending
//after some distance travelled.
#ifndef TRACK_HPP
#define TRACK_HPP

#include "Math/LorentzVector.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"

namespace examples {
  class track {
    public:
      track(ROOT::Math::XYZTVector const& start, ROOT::Math::XYZTVector const& end);
      track() = default;

      ROOT::Math::XYZTVector const& start() const;
      ROOT::Math::XYZTVector const& end() const;
      ROOT::Math::XYZVector direction() const;
      double length() const;
      double delta_t() const;

    private:
      ROOT::Math::XYZTVector m_start_position;
      ROOT::Math::XYZTVector m_end_position;
  };
}

#endif //TRACK_HPP
