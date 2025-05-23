#pragma once
#ifndef CUBIC_SPLINE_H
#define CUBIC_SPLINE_H

#include <vector>
#include <string>
#include <stdexcept>

namespace CurveFitting {

	class CubicSpline {
	private:
		std::vector<double> x;  // x�����
		std::vector<double> y;  // y�����
		std::vector<double> a;  // ��������ϵ����a[i]*(x-x[i])^3
		std::vector<double> b;  // ��������ϵ����b[i]*(x-x[i])^2
		std::vector<double> c;  // ��������ϵ����c[i]*(x-x[i])
		std::vector<double> d;  // ��������ϵ����d[i]

	public:
		// ���캯�������յ���б�
		CubicSpline(const std::vector<std::pair<double, double>>& points,
			bool natural = true,
			double left_deriv = 0.0,
			double right_deriv = 0.0);

		// ��ֵ����
		double interpolate(double x_val) const;

		// ��ȡ���������ָ���㼯�ϵ�ֵ
		std::vector<double> evaluate(const std::vector<double>& x_vals) const;

		// ��ȡԭʼ���ݵ�
		std::vector<std::pair<double, double>> get_points() const;
	};

} // namespace CurveFitting

#endif // CUBIC_SPLINE_H