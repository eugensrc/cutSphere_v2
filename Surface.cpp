#include "Surface.hpp"

Surface::Surface(const GridParameters &grid_param) : gp(grid_param)
{
	cadcam::mwTPoint3d<double> refPoint = gp.getReferencePoint();
	map[std::make_pair(refPoint.x(), refPoint.y())] = gp.max_z();
	for (size_t x = 1; x < gp.count_x(); ++x)
		for (size_t y = 1; y < gp.count_y(); ++y)
			map[std::make_pair(double(x) * gp.delta(), double(y) * gp.delta())] = gp.max_z();
}

bool Surface::IsPointInCloud(const cadcam::mwTPoint3d<double> &point) const
{
	return  IsInCloud(point.x(), point.y(), point.z());
}

bool Surface::IsPointInCloud(const double &x, const double &y, const double &z) const
{
	return IsInCloud(x, y, z);
}

const GridParameters &Surface::GetGridParameters() const
{
	return gp;
}

double Surface::Find(const column_d &Key) const 
{
	point_map::const_iterator search = map.find(Key);
	if (search != map.end())
		return search->second;
	else
		return NAN;
}

void Surface::Insert(const column_d &key, const double &value)
{
	try
	{
		map.at(key) = value;
	}
	catch (std::out_of_range)
	{ }
}

std::vector<cadcam::mwTPoint3d<double>> Surface::GetPoints() const
{
	std::vector<cadcam::mwTPoint3d<double>> ret;
	for (const auto& value : map)
	{
		ret.push_back({ value.first.first, value.first.second, value.second });
	}
	return ret;
}
bool Surface::IsInCloud(const double x, const double y, const double z) const
{
	return  x >= gp.min_x() && x <= gp.max_x() &&
		y >= gp.min_y() && y <= gp.max_y() &&
		z >= gp.min_z() && z <= gp.max_z();
}
