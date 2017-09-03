#pragma once

#include "WaylandSurface.h"

class WlRegion
{
public:
	WlRegion(wl_client * client, uint32_t id);
	
private:
	struct Impl;
	weak_ptr<Impl> impl;
};