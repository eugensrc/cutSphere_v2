#include "SurfaceWriter.hpp"

void SurfaceWriter::write(const std::string &fname, const Surface &surface)
{
	std::vector<cadcam::mwTPoint3d<double>> surf_pts= surface.GetPoints();
	std::ofstream output(fname, std::ios::trunc);
	for (auto& point: surf_pts)
		if (!std::isinf(point.z())) // INF mean pillar cutted, and no points for output
			output << point.x() << " " << point.y() << " " << point.z() << std::endl;
}
