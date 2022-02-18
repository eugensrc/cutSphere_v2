#include "CreateSkin.hpp"

void CreateSkin(const cadcam::mwTPoint3d<double> refPoint,
	const unsigned long nx, const unsigned long ny,
	const unsigned long nz, const double sphereRad,
	mwDiscreteFunction &func, const double deltaT,
	const double delta, const std::string &skinFileName)
{

	GridParameters gridParam(refPoint, nx, ny, nz, delta);
	Surface surface(gridParam);
	std::cout << "Initialization done.\nCutting started.\n";
	clock_t begin_time = clock();
	SphereCutter cutter(surface);

	double range = 1. / deltaT;
	for (double factor = 1.; factor < range || cadcam::is_equal(factor, range); ++factor)
	{
		cadcam::mwTPoint3d<double> begin = func.Evaluate((factor - 1.) * deltaT);
		cadcam::mwTPoint3d<double> end = func.Evaluate(factor * deltaT);
		cutter.Cut(SpherePath(begin, end, sphereRad));
	}
	std::cout << "Cutting complete in " << float(clock() - begin_time) / 1000 << "s.\n"; 
	std::cout << "Starting write result to output file.\n";
	SurfaceWriter::write(skinFileName, surface);
	std::cout << "Done.\n";
}
