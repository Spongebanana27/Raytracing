#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
	public:
		sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}

		bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const override {
			vec3 oc = center - r.origin();
			auto a = r.direction().lengthSquared();
			auto h = dot(r.direction(), oc);
			auto c = oc.lengthSquared() - radius*radius;

			auto discriminant = h*h - a*c;
			if (discriminant < 0) return false;

			auto sqrtd = std::sqrt(discriminant);

			// Find the nearest root that lies in the acceptable range
			auto root = (h - sqrtd) / a;
			if(root <= rayTMin || rayTMax <= root){
				root = (h + sqrtd) / a;
				if(root <= rayTMin || rayTMax <= root){
					return false;
				}
			}
			
			rec.t = root;
			rec.p = r.at(rec.t);
			vec3 outwardNormal = (rec.p - center) / radius;
			rec.setFaceNormal(r, outwardNormal);
		
			return true;
		}

	private:
		point3 center;
		double radius;
};

#endif
