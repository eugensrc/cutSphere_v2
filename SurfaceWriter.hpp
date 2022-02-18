#ifndef _SURFACE_WRITER_HPP_
#define _SURFACE_WRITER_HPP_
#include <fstream>
#include <string>
#include "Surface.hpp"

//Class provide writing surface points to file
class SurfaceWriter
{
public:
	static void write(const std::string &fname, const Surface &surface);
};

#endif // !_SKIN_WRITER_HPP_
