#pragma once
#include <functional> // std::hash



struct MapPoint
{
  // Constructors
  MapPoint() : X(0), Y(0) { }
  MapPoint(int x, int y) : X(x), Y(y) { }

  // Operator Overloads
  bool operator==(const MapPoint &rhs) const;

  // Public Data
  int X;
  int Y;
};

struct MapPointHash
{
  size_t operator()(const MapPoint &m) const noexcept
  {
    // Calcualte hashes with appropraite functors
    size_t h1 = std::hash<int>{}(m.X);
    size_t h2 = std::hash<int>{}(m.Y);

    // combine hashes.
    return h1 ^ (h2 << 1); 
  }
};
