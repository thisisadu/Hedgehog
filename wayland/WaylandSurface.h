#pragma once

#include "../main/Surface2D.h"
#include "../main/utils.h"
#include "WaylandServer.h"

#include <wayland-server-core.h>

class WaylandSurface
{
public:
	WaylandSurface(wl_client * client, uint32_t id);
	static WaylandSurface getFrom(wl_resource * resource);
	//static void makeWlShellSurface(wl_client * client, uint32_t id, wl_resource * surface);
	static void makeXdgShellV6Surface(wl_client * client, uint32_t id, wl_resource * surface);
	
private:
	struct Impl;
	WaylandSurface(weak_ptr<Impl> implIn) {impl = implIn;}
	weak_ptr<Impl> impl;
};

