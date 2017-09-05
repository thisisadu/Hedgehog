#pragma once

#include "WaylandServer.h"
#include <wayland-server-core.h>

class WlSeat
{
public:
	WlSeat() {}
	WlSeat(wl_client * client, uint32_t id);
	void pointerMove(V2d position, wl_resource * surface);
	void pointerLeave(wl_resource * surface); // call this before pointerMove on the new surface
	static WlSeat getFromClient(wl_client * client);
	
private:
	struct Impl;
	weak_ptr<Impl> impl;
};
