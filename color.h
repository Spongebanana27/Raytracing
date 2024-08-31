#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline double linearToGamma(double linearComponent){
	if(linearComponent > 0){
		return std::sqrt(linearComponent);
	}
	return 0;
}
	
void writeColor(std::ostream& out, const color& pixelColor) {
    
	auto r = pixelColor.x();
    auto g = pixelColor.y();
	auto b = pixelColor.z();

	// Linear to gamme transform for gamma 2
	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

    // Translate the [0,1] component values to the byte range [0,255].
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
   	int gbyte = int(256 * intensity.clamp(g));
   	int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}

#endif
