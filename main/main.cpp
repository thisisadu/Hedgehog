#include <unistd.h>
#include <iostream>
 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../opengl/Texture.h"
#include "../backend/Backend.h"
#include "../wayland/WaylandServer.h"
#include "../scene/Scene.h"

// change to toggle debug statements on and off
#define debug debug_on

unique_ptr<Backend> Backend::instance;

int main (int argc, char ** argv)
{
	debug("setting up backend");
	//auto backend = Backend::makeGLX(V2i(800, 800));
	Backend::setup(V2i(800, 800));
	ASSERT_ELSE(Backend::instance, exit(1));
	
	glewInit();
	
	auto texture = Texture();
	texture.loadFromImage("assets/hedgehog.jpg");
	
	debug("setting up wayland server");
	
	WaylandServer::setup();
	
	Scene scene;
	scene.setup();
	Backend::instance->setInputInterface(scene.getInputInterface());
	
	debug("starting main loop");
	while (Backend::instance)
	{
		texture.draw();
		WaylandServer::iteration();
		scene.draw();
		Backend::instance->swapBuffer();
		sleepForSeconds(0.01667);
		Backend::instance->checkEvents();
	}
	
	debug("shutting down wayland server");
	WaylandServer::shutdown();
	
	debug("exiting");
}