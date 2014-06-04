#pragma once

#include "pos.hxx"

// For convenience...
WorldPos map2world(const MapPos &p);
WorldPos window2world(const WindowPos &p, int floor);
MapPos window2map(const WindowPos &p, int floor);
MapPos world2map(const WorldPos &p);
WindowPos map2window(const MapPos &p);
WindowPos world2window(const WorldPos &p);

