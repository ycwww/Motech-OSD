#pragma once
#include <vector>

enum CELIBRATE_STATUS_E
{
	CELIBRATE_STATUS_UNINIT = 0,
	CELIBRATE_STATUS_UNDERWAY = 1,
	CELIBRATE_STATUS_FINISHED = 2,
	CELIBRATE_STATUS_FAILED = 3,
	CELIBRATE_STATUS_BREAK = 4,

};
enum COMPENSATE_TYPE_E
{
	COMPENSATE_ORIGIN_MOVE = 1,
	COMPENSATE_TOOL_COMPENSATE = 2,
	COMPENSATE_POINT_TO_POINT =3,
};
class celibrate_calculate
{
public:
	double calculateBestSpeed(const std::vector<double>& measuredThicknesses, const std::vector<double>& actualThicknesses, double init_speed);
	double calculateBestSpeed(const std::vector<double>& calculatedThickness, const std::vector<double>& actualThickness);
private:
	double calculateErrorSumOfSquares(double speed, const std::vector<double>& measuredThicknesses, const std::vector<double>& actualThicknesses);
};

