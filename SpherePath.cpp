#include "SpherePath.hpp"

SpherePath::SpherePath()
{
	start = end = move_vec = cadcam::mwTPoint3d<double>(0.,0.,0.);
	nomove = true;
}

SpherePath::SpherePath(const cadcam::mwTPoint3d<double> &begin, const cadcam::mwTPoint3d<double> &end, double sphereRadius) :
	start(begin), end(end), sphere_radius(sphereRadius)
{
	move_vec = (end - begin);
	if (cadcam::is_equal(~move_vec, 0.))
		nomove = true;
	else 
		nomove = false;
}

SpherePath::SpherePath(const SpherePath & path)
{
	start = path.start;
	end = path.end;
	move_vec = path.move_vec;
	sphere_radius = path.sphere_radius;
	nomove = path.nomove;
}

double SpherePath::GetSphereRadius() const
{
	return sphere_radius;
}

bool SpherePath::IsInsidePath(const cadcam::mwTPoint3d<double> &point) const
{
	return IsInside(point);
}

bool SpherePath::IsInsidePath(const double &x, const double &y, const double &z) const
{
	return IsInside(cadcam::mwTPoint3d<double>(x, y, z));
}

double SpherePath::GetDistanceToMoveVector(const cadcam::mwTPoint3d<double> &point) const
{
	return ~((start - point) % move_vec) / ~move_vec;
}

cadcam::mwTPoint3d<double> SpherePath::GetStart() const
{
	return start;
}

cadcam::mwTPoint3d<double> SpherePath::GetEnd() const
{
	return end;
}

bool SpherePath::IsInside(const cadcam::mwTPoint3d<double> &pt) const
{
	if (nomove)
	{
		double sqrX = (pt.x()*pt.x()) - (2.0 * pt.x() * start.x()) + (start.x() * start.x());
		double sqrY = (pt.y()*pt.y()) - (2.0 * pt.y() *  start.y()) + (start.y() * start.y());
		double sqrZ = (pt.z()*pt.z()) - (2.0 * pt.z() *  start.z()) + (start.z() * start.z());

		return (sqrX + sqrY + sqrZ < sphere_radius * sphere_radius || cadcam::is_equal(sqrX + sqrY + sqrZ, sphere_radius * sphere_radius));
	}

	cadcam::mwTVector3d<double> v = pt - start, w = pt - end;
	double range = 0.;
	if (v * move_vec < 0.)
	{
		range = ~v;
		return range < sphere_radius || cadcam::is_equal(range,sphere_radius);
	}
	else if (w * (-1. * move_vec) < 0.)
	{
		range = ~w;
		return range < sphere_radius || cadcam::is_equal(range, sphere_radius);
	}
	else
	{
		range = GetDistanceToMoveVector(pt);
		return range < sphere_radius || cadcam::is_equal(range, sphere_radius);
	}
	
}
