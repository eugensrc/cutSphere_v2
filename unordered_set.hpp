#ifndef _U_SET_CUSTOM_HPP_
#define _U_SET_CUSTOM_HPP_

#include <unordered_set>
#include "mwTPoint3d.hpp"
#include "mwMathConstants.hpp"

namespace custom
{
	struct PointHasher
	{
		size_t operator()(cadcam::mwTPoint3d<double> const &p) const noexcept
		{
			return (std::hash<std::double_t>{}(p.x()) ^ (std::hash<std::double_t>{}(p.y()) << 1)) ^ std::hash<std::double_t>{}(p.z());
		}
	};
	struct PointEqualsFunc {
		bool operator()(const cadcam::mwTPoint3d<double>& first, const cadcam::mwTPoint3d<double>& second) const {
			return cadcam::is_equal(first.x(), second.x()) && cadcam::is_equal(first.y(), second.y()) && cadcam::is_equal(first.z(), second.z());
		}
	};
	typedef std::unordered_set<cadcam::mwTPoint3d<double>, PointHasher, PointEqualsFunc> point_set;
}
#endif
