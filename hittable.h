#ifndef HITTABLE_H
#define HITTABLE_H

class material;

class hitRecord {
	public:
		point3 p;
		shared_ptr<material> mat;
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

		virtual bool hit(const ray& r, interval rayT, hitRecord& rec) const = 0;
		
};

#endif
