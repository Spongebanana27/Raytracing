#include "rt.h"

#include <iostream>
#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main(){

	// World
	hittableList world;

	auto materialGround = make_shared<lambertian>(color(0.8, 0.8, 0.2));
	auto materialCenter = make_shared<metal>(color(0.1, 0.2, 0.4), .2);
	auto materialLeft = make_shared<metal>(color(0.1, 0.8, 0.4), .8);
	auto materialRight = make_shared<metal>(color(0.8, 0.2, 0.1), .8);

    world.add(make_shared<sphere>(point3( 0.0, -100.6, -3.0), 100.0, materialGround));
    world.add(make_shared<sphere>(point3( 0.0,    -.1, -3.2),   0.5, materialCenter));
    world.add(make_shared<sphere>(point3(-1.0,    -.1, -3.0),   0.5, materialLeft));
    world.add(make_shared<sphere>(point3( 1.0,    -.1, -3.0),   0.5, materialRight));

	camera cam;

	cam.aspectRatio = 16.0 / 9.0;
	cam.imageWidth = 1920;
	cam.samplesPerPixel = 1000;
	cam.maxDepth = 50;

	cam.render(world);

}
