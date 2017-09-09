#include "WaylandServer.h"
#include <wayland-server-core.h>
#include <unordered_map>

#pragma once

// these macros are convenient and allow for proper file/line num if assert fails
#define GET_IMPL shared_ptr<Impl> impl = this->impl.lock(); assert(impl);
#define GET_IMPL_ELSE shared_ptr<Impl> impl = this->impl.lock(); if (!impl)
#define GET_IMPL_FROM(resource) shared_ptr<Impl> impl = WaylandObject::get<Impl>(resource); assert(impl);

// WaylandObjects manage their own memory. You should always hold weak pointers to them.

class WaylandObject: public std::enable_shared_from_this<WaylandObject>
{
public:
	
	wl_resource * wlObjMake(wl_client * client, uint32_t id, const wl_interface * interface, int version, const void * implStruct);
	
	static shared_ptr<WaylandObject> getWaylandObject(wl_resource * resource);
	
	template<typename T>
	inline static shared_ptr<T> get(wl_resource * resource)
	{
		return std::static_pointer_cast<T>(getWaylandObject(resource));
	}
	
	//wl_resource * getResource() {return resource;}
	
	static void wlObjDestroy(wl_resource * resource);
	
private:
};
/*
template<typename T>
class Resource
{
public:
	
	void setup(shared_ptr<T> data, wl_client * client, uint32_t id, const wl_interface * interface, int version, const void * implStruct)
	{
		resource = wl_resource_create(client, interface, version, id);
		wl_resource_set_implementation(resource, implStruct, nullptr, destroyWaylandObject2);
		assert(waylandObjectMap.find(resource) == waylandObjectMap.end());
		waylandObjectMap[resource] = data;
	}
	
	void destroy()
	{
		wl_resource_destroy(resource);
		resource = nullptr;
	}
	
	static shared_ptr<T> get(wl_resource * resource)
	{
		assert(resource != nullptr);
		auto iter = waylandObjectMap.find(resource);
		if (iter == waylandObjectMap.end())
		{
			warning(FUNC + " called on WaylandObject not in map");
			return shared_ptr<T>(nullptr);
		}
		return iter->second;
	}
	
	wl_resource * getResource() {return resource;}
	
private:
	wl_resource * resource = nullptr;
	static std::unordered_map<wl_resource *, shared_ptr<T>> waylandObjectMap;
	
	static void destroyWaylandObject2(wl_resource * resource)
	{
		auto iter = waylandObjectMap.find(resource);
		if (iter == waylandObjectMap.end())
		{
			warning(FUNC + " called with resource not in map");
			return;
		}
		waylandObjectMap.erase(iter);
	}
};

template<typename T>
std::unordered_map<wl_resource *, shared_ptr<T>> WaylandObject2<T>::waylandObjectMap;
*/
