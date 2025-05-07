#include "celibrate_calculate.h"



double celibrate_calculate::calculateErrorSumOfSquares(double speed, const std::vector<double>& measuredThicknesses, const std::vector<double>& actualThicknesses) 
{
	double errorSumOfSquares = 0.0;
	for (size_t i = 0; i < measuredThicknesses.size(); ++i) 
	{
		double timeDiff = measuredThicknesses[i] / speed * 2;
		double predictedThickness = speed * timeDiff / 2;
		double error = predictedThickness - actualThicknesses[i];
		errorSumOfSquares += error * error;
	}
	return errorSumOfSquares;
}


double celibrate_calculate::calculateBestSpeed(const std::vector<double>& measuredThicknesses, const std::vector<double>& actualThicknesses, double init_speed)
{
	double sumXY = 0.0;
	double sumX2 = 0.0;

	for (size_t i = 0; i < measuredThicknesses.size(); ++i) {
		double timeDiff = measuredThicknesses[i] / init_speed * 2; // 使用初始速度计算时间差
		sumXY += actualThicknesses[i] * timeDiff;
		sumX2 += timeDiff * timeDiff;
	}

	return sumXY / sumX2 * 2;
}

double celibrate_calculate::calculateBestSpeed(const std::vector<double>& calculatedThickness, const std::vector<double>& actualThickness) 
{
	// Ensure the vectors have the same size
	if (calculatedThickness.size() != actualThickness.size()) {
		throw std::invalid_argument("Vectors must have the same size");
	}

	double sum_numerator = 0;
	double sum_denominator = 0;

	// Calculate sums for the least squares method
	for (size_t i = 0; i < calculatedThickness.size(); ++i) {
		sum_numerator += actualThickness[i] * calculatedThickness[i];
		sum_denominator += std::pow(calculatedThickness[i], 2);
	}

	// Calculate the best speed
	return sum_numerator / sum_denominator;
}