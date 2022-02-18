#include "GridParameters.hpp"

GridParameters::GridParameters() : x_count(0.), y_count(0.), z_count(0.), reference_point{ 0.,0.,0. }, grid_delta(0.), bounds{ 0.,0.,0.,0.,0.,0. }
{
}

GridParameters::GridParameters(const cadcam::mwTPoint3d<double>& refPoint, const size_t& nx, const size_t& ny, const size_t& nz, const double& gridDelta):
	reference_point(refPoint), x_count((double)nx / gridDelta), y_count((double)ny / gridDelta), z_count((double)nz / gridDelta), grid_delta(gridDelta)
{
	//Check if ref point lay on grid
	try {
		if (fmod(refPoint.x(), gridDelta) != 0 ||
				fmod(refPoint.y(), gridDelta) != 0 ||
					fmod(refPoint.z(), gridDelta) != 0)
			throw misc::mwException(-1, "Reference point not divisible by the grid delta without a remainder.");
	}
	catch (misc::mwException e)
	{
		throw e;
	}
	bounds[0] = refPoint.x();
	bounds[2] = refPoint.y();
	bounds[4] = refPoint.z();
	bounds[1] = (double)nx - refPoint.x();
	bounds[3] = (double)ny - refPoint.y();
	bounds[5] = (double)nz - refPoint.z();
}

GridParameters::GridParameters(const GridParameters& gp)
{
	x_count = gp.x_count;
	y_count = gp.y_count;
	z_count = gp.z_count;
	grid_delta = gp.grid_delta;
	reference_point = gp.reference_point;
	for (short i = 0; i < 6; ++i)
		bounds[i] = gp.bounds[i];
}

double GridParameters::min_x() const
{
	return bounds[0];
}

double GridParameters::min_y() const
{
	return bounds[2];
}

double GridParameters::min_z() const
{
	return bounds[4];
}

double GridParameters::max_x() const
{
	return bounds[1];
}

double GridParameters::max_y() const
{
	return bounds[3];
}

double GridParameters::max_z() const
{
	return bounds[5];
}

size_t GridParameters::count_x() const
{
	return x_count;
}

size_t GridParameters::count_y() const
{
	return y_count;
}

size_t GridParameters::count_z() const
{
	return z_count;
}

double GridParameters::delta() const
{
	return grid_delta;
}

cadcam::mwTPoint3d<double> GridParameters::getReferencePoint() const
{
	return reference_point;
}

cadcam::mwTPoint3d<double> GridParameters::Formalize(const cadcam::mwTPoint3d<double>& point) const
{
	return { round(point.x() / grid_delta) *  grid_delta,
			round(point.y() / grid_delta) *  grid_delta,
			round(point.z() / grid_delta) *  grid_delta };
}

