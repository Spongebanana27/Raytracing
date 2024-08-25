#include "rt.h"

#include <iostream>
#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"

color rayColor(const ray& r, const hittable& world){

	hitRecord rec;
	if(world.hit(r, 0, infinity, rec)){
		return .5 * (rec.normal + color(1,1,1));
	}

	vec3 unit_direction = unitVector(r.direction());
	auto a = 0.5*(unit_direction.y() + 1.0);
	return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);

}

int main(){

	// Image

	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;

	int imageHeight = int(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;


	// World
	hittableList world;

	world.add(make_shared<sphere>(point3(0,0,-1), .5));
	world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

	// Camera
	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
	auto cameraCenter = point3(0,0,0);

	// Vectors accross horizontal and vertical viewport edges
	auto viewportU = vec3(viewportWidth, 0, 0);
	auto viewportV = vec3(0, -viewportHeight, 0);

	// Horizontal and vertical deltas from pixel to pixel
	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	// Location of upper left pixel
	auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLength) - viewportU/2 - viewportV/2;
	auto pixel00Location = viewportUpperLeft + .5 * (pixelDeltaU + pixelDeltaV);


	// Render

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for(int j = 0; j < imageHeight; j++){
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for(int i = 0; i < imageWidth; i++){
			auto pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;
			ray r(cameraCenter, rayDirection);

			color pixelColor = rayColor(r, world);

			write_color(std::cout, pixelColor);
		}
	}

	std::clog << "\rDone.                                         \n";

}
