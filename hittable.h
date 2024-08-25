#ifndef HITTABLE_H
#define HITTABLE_H

class hitRecord {
	public:
		point3 p;
		vec3 normal;
		double t;

		bool frontFace;

		void setFaceNormal(const ray& r, const vec3& outwardNormal){
			// Sets the hit record normal vector
			// outwardNormal is assumed to be a unit vector
			
			frontFace = dot(r.direction(), outwardNormal) < 0;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
};

class hittable {
	public:
		virtual ~hittable() = default;

		virtual bool hit(const ray& r, double rayTMin, double rayTMax, hitRecord& rec) const = 0;
};

#endif
