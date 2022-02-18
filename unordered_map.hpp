#ifndef __UNORDERED_MAP_HPP__
#define __UNORDERED_MAP_HPP__
#include <unordered_map>
#include "mwMathConstants.hpp"

namespace custom
{
	struct PairHasher_d
	{
		size_t operator()(const std::pair<double, double> &p) const noexcept
		{
			return (std::hash<std::double_t>{}(p.first) ^ (std::hash<std::double_t>{}(p.second) << 1));
		}
	};
	struct PairEqualFunc_d {
		bool operator()(const std::pair<double, double> &pair1, const std::pair<double, double> &pair2) const {
			return cadcam::is_equal(pair1.first, pair2.first) && cadcam::is_equal(pair1.second, pair2.second);
		}
	};

	//Defines pair of (x,y) coordinates
	typedef std::pair<double, double> column_d; 
	typedef std::unordered_map <column_d, double, PairHasher_d, PairEqualFunc_d> point_map;
}
#endif // !__UNORDERED_MAP_HPP__


