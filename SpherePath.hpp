#ifndef __PATH_HPP__
#define __PATH_HPP__
#include "mwTPoint3d.hpp"
#include "mwMathConstants.hpp"

class SpherePath
{
public:
	SpherePath();
	SpherePath(const cadcam::mwTPoint3d<double> &start, const cadcam::mwTPoint3d<double> &end, double sphereRadius);
	SpherePath(const SpherePath& path);
	double GetSphereRadius() const;
	bool IsInsidePath(const cadcam::mwTPoint3d<double> &point) const;
	bool IsInsidePath(const double &x, const double &y, const double &z) const;
	cadcam::mwTPoint3d<double> GetStart() const;
	cadcam::mwTPoint3d<double> GetEnd() const;

private:
	bool IsInside(const cadcam::mwTPoint3d<double> &pt) const;
	double GetDistanceToMoveVector(const cadcam::mwTPoint3d<double> &point) const;
	cadcam::mwTPoint3d<double> start, end;
	cadcam::mwTVector3d<double> move_vec;
	double sphere_radius;
	//Indicate if path distance = 0
	bool nomove;
	
};

#endif // !"PATH_H_"

