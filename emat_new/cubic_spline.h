#pragma once
#ifndef CUBIC_SPLINE_H
#define CUBIC_SPLINE_H

#include <vector>
#include <string>
#include <stdexcept>

namespace CurveFitting {

	class CubicSpline {
	private:
		std::vector<double> x;  // x坐标点
		std::vector<double> y;  // y坐标点
		std::vector<double> a;  // 三次样条系数：a[i]*(x-x[i])^3
		std::vector<double> b;  // 三次样条系数：b[i]*(x-x[i])^2
		std::vector<double> c;  // 三次样条系数：c[i]*(x-x[i])
		std::vector<double> d;  // 三次样条系数：d[i]

	public:
		// 构造函数：接收点对列表
		CubicSpline(const std::vector<std::pair<double, double>>& points,
			bool natural = true,
			double left_deriv = 0.0,
			double right_deriv = 0.0);

		// 插值函数
		double interpolate(double x_val) const;

		// 获取拟合曲线在指定点集上的值
		std::vector<double> evaluate(const std::vector<double>& x_vals) const;

		// 获取原始数据点
		std::vector<std::pair<double, double>> get_points() const;
	};

} // namespace CurveFitting

#endif // CUBIC_SPLINE_H