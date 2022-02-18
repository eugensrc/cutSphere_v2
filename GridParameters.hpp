#ifndef _GRID_PARAMETERS_HPP_
#define _GRID_PARAMETERS_HPP_
#include "mwTPoint3d.hpp"
#include "mwMathConstants.hpp"

class GridParameters
{
public:
	GridParameters();
	GridParameters(const cadcam::mwTPoint3d<double>& refPoint, const size_t& nx, const size_t& ny, const size_t& nz, const double& gridDelta);
	GridParameters(const GridParameters& gp);
	double min_x() const;
	double min_y() const;
	double min_z() const;
	double max_x() const;
	double max_y() const;
	double max_z() const;
	size_t count_x() const;
	size_t count_y() const;
	size_t count_z() const;
	double delta() const;
	cadcam::mwTPoint3d<double> getReferencePoint() const;
	//Returns a point corresponding to the grid parameters
	cadcam::mwTPoint3d<double> Formalize(const cadcam::mwTPoint3d<double>& point) const;

private:
	cadcam::mwTPoint3d<double> reference_point;
	//Point count of axis
	size_t x_count, y_count, z_count;
	double grid_delta;
	//Contains min/max axes values
	double bounds[6];
};

#endif //_GRID_PARAMETERS_HPP_
