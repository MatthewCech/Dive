#pragma once


struct MapPoint
{
  MapPoint() : X(0), Y(0) { }
  MapPoint(int x, int y) : X(x), Y(y) { }
  int X;
  int Y;
};
