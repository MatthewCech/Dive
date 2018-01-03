#include "MapPoint.hpp"

bool MapPoint::operator==(const MapPoint &rhs) const
{
  return X == rhs.X && Y == rhs.Y;
}
