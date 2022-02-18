#ifndef __SKIN_CUTTER_HPP__
#define __SKIN_CUTTER_HPP__
#include "mwTPoint3d.hpp"
#include "mwMathConstants.hpp"
#include "unordered_set.hpp"
#include "GridParameters.hpp"
#include "Surface.hpp"
#include "SpherePath.hpp"
#include <vector>
#include <stack>

using custom::column_d;
class SphereCutter
{
public:
	SphereCutter(Surface &surf);
	void Cut(const SpherePath &spherepath);
private:
	//Returns true, if sphere path intersect surface
	bool IsSphereIntersectSurface() const;
	//If exist, returns Z coordinate of bottom cut border, otherwise - returns -INFINITE
	double FindBottomBorder(const cadcam::mwTPoint3d<double> &refProjectionPoint) const;
	//Find projection of path on z-max surface and adds points to projection list;
	std::vector<cadcam::mwTPoint3d<double>> FindPathProjection();

	const GridParameters grid_param;
	Surface &surface;
	SpherePath path;
};
#endif // !__SKIN_CUTTER_HPP__
