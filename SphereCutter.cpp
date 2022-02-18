#include "SphereCutter.hpp"

SphereCutter::SphereCutter(Surface &surf) : surface(surf), grid_param(surf.GetGridParameters()), path()
{
}

void SphereCutter::Cut(const SpherePath &sphere_path)
{
	path = sphere_path;
	if (IsSphereIntersectSurface())
	{
		std::vector<cadcam::mwTPoint3d<double>> projection = FindPathProjection();
		for (auto& pt : projection)
		{
			column_d column (pt.x(),pt.y());
			double current_border = surface.Find(column);
			if (!std::isnan(current_border)) //NAN means column x, y does not belong to the surface.it shouldn't be, but it doesn't hurt to be careful
			{
				double new_bottom_border = FindBottomBorder(pt);
				if (new_bottom_border < current_border)
					surface.Insert(column, new_bottom_border);
			}
		}
	}
}

bool SphereCutter::IsSphereIntersectSurface() const
{
	double radius = path.GetSphereRadius();
	cadcam::mwTPoint3d<double> start = path.GetStart(), end = path.GetEnd();
	cadcam::mwTVector3d<double> start_projection_vec(start - cadcam::mwTPoint3d<double>(start.x(), start.y(), grid_param.max_z())),
		end_projection_vec(end - cadcam::mwTPoint3d<double>(end.x(), end.y(), grid_param.max_z())),
		orth(grid_param.delta(), 0., 0.);

	// if range of projection vectors greater than radius - sphere not istersect surface, but only if projection vectors codirectional
	if ((~start_projection_vec > radius) && (~end_projection_vec > radius)) 
		if (signbit(~(orth % start_projection_vec)) == signbit(~(orth % end_projection_vec))) //if projection codirectional
			return false;
	return true;
}

double SphereCutter::FindBottomBorder(const cadcam::mwTPoint3d<double>& refPoint) const
{
	double x = refPoint.x(), y = refPoint.y(), z = refPoint.z();

	for (double factor = 0.; z > grid_param.min_z() || cadcam::is_equal(z, grid_param.min_z()); ++factor)
	{
		double term = grid_param.delta() * factor;
		if (surface.IsPointInCloud(x, y, z) && !path.IsInsidePath(x, y, z))
			return z;
		else
			z = refPoint.z() - term;
	}
	return -INFINITY; // returns if sphere cut all points in column (x,y)
}

std::vector<cadcam::mwTPoint3d<double>> SphereCutter::FindPathProjection()
{
	double grid_delta = grid_param.delta();
	//In case of radius < grid need to assign new radius, because minimal check area of algoritm is grid.delta()
	double radius = path.GetSphereRadius();
	radius = radius < grid_param.delta() ? grid_delta : radius;

	cadcam::mwTPoint3d<double> begin = path.GetStart(), end = path.GetEnd();
	begin.z(grid_param.max_z());
	end.z(grid_param.max_z());
	//Projection of sphere movement is equal to sphere movement through surface x,y, max_z()
	SpherePath projectionPath(begin, end, radius);

	//Initialization part
	std::vector<cadcam::mwTPoint3d<double>> chech_area{
			{grid_delta,0.,0. }, { 0.,grid_delta,0. }, { -grid_delta,0.,0. }, { 0.,-grid_delta,0. } 
	};
	std::vector<cadcam::mwTPoint3d<double>> projection;
	std::stack<cadcam::mwTPoint3d<double>> stack;
	custom::point_set visited_pts;
	cadcam::mwTPoint3d<double> current_pt, temp_pt, start_pt = grid_param.Formalize(begin);
	stack.push(start_pt);
	visited_pts.insert(start_pt);

	//Search projection
	while (!stack.empty())	
	{
		current_pt = stack.top(); //Put point
		stack.pop();

		//Filter point for output array
		if (surface.IsPointInCloud(current_pt) && path.IsInsidePath(current_pt) && !std::isinf(surface.Find(std::make_pair(current_pt.x(), current_pt.y()))))
			projection.push_back(current_pt);

		//Check neighbours of current point
		for (const auto& vec : chech_area)
		{
			temp_pt = current_pt + vec;
			if (visited_pts.find(temp_pt) == visited_pts.end()) // if point not visited
			{
				visited_pts.insert(temp_pt); //Mark as visited
				if (projectionPath.IsInsidePath(temp_pt))
					stack.push(temp_pt); //If point inside projection, add it to next iteration	
			}
		}
	}
	return projection;
}
