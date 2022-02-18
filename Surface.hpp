#ifndef _SURFACE_HPP_
#define _SURFACE_HPP_
#include "mwTPoint3d.hpp"
#include "mwMathConstants.hpp"
#include "GridParameters.hpp"
#include "unordered_map.hpp"

using custom::column_d;
using custom::point_map;

class Surface
{
public:
	Surface(const GridParameters &grid_param);
	bool IsPointInCloud(const cadcam::mwTPoint3d<double> &point) const;
	bool IsPointInCloud(const double &x, const double &y, const double &z) const;
	const GridParameters& GetGridParameters() const;
	//Returns z-value by given column (x,y), otherwise - returns NAN;
	double Find(const column_d& key) const;
	//Override z-value at column (x,y)
	void Insert(const column_d& key, const double &value);
	//Returns array of surface points
	std::vector<cadcam::mwTPoint3d<double>> GetPoints() const;

private:
	point_map map;
	bool IsInCloud(const double x, const double y, const double z) const;
	const GridParameters gp;
};
#endif // !_SURFACE_HPP_



