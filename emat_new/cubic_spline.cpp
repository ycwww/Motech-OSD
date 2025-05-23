#include "cubic_spline.h"
#include <algorithm>
#include <cmath>

namespace CurveFitting {

	CubicSpline::CubicSpline(const std::vector<std::pair<double, double>>& points,
		bool natural, double left_deriv, double right_deriv) {
		size_t n = points.size();
		if (n < 2) throw std::invalid_argument("������Ҫ��������в�ֵ");

		// ����x��y���꣬��ȷ��x���ϸ������
		x.reserve(n);
		y.reserve(n);

		for (const auto& point : points) {
			x.push_back(point.first);
			y.push_back(point.second);
		}

		// ���x�Ƿ��ϸ��������Ҫʱ����
		bool sorted = true;
		for (size_t i = 1; i < n; ++i) {
			if (x[i] <= x[i - 1]) {
				sorted = false;
				break;
			}
		}

		if (!sorted) {
			// ��x��������
			std::vector<std::pair<double, double>> sorted_points = points;
			std::sort(sorted_points.begin(), sorted_points.end(),
				[](const auto& a, const auto& b) { return a.first < b.first; });

			// �������x��y
			x.clear();
			y.clear();
			for (const auto& point : sorted_points) {
				x.push_back(point.first);
				y.push_back(point.second);
			}
		}

		// ���������Ĳ���
		std::vector<double> h(n - 1);
		for (size_t i = 0; i < n - 1; ++i) {
			h[i] = x[i + 1] - x[i];
		}

		// ������������Խ����Է������Ի�ȡ���׵�������أ�
		std::vector<double> mu(n - 1);
		std::vector<double> z(n);

		if (natural) {
			// ��Ȼ�߽�����
			mu[0] = 0.0;
			z[0] = 0.0;

			for (size_t i = 1; i < n - 1; ++i) {
				double l = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
				mu[i] = h[i] / l;
				z[i] = (3.0 * (y[i + 1] - y[i]) / h[i] - 3.0 * (y[i] - y[i - 1]) / h[i - 1] - h[i - 1] * z[i - 1]) / l;
			}

			z[n - 1] = 0.0;
		}
		else {
			// �̶��߽�����
			mu[0] = 0.5;
			z[0] = (3.0 / h[0]) * ((y[1] - y[0]) / h[0] - left_deriv);

			for (size_t i = 1; i < n - 1; ++i) {
				double l = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
				mu[i] = h[i] / l;
				z[i] = (3.0 * (y[i + 1] - y[i]) / h[i] - 3.0 * (y[i] - y[i - 1]) / h[i - 1] - h[i - 1] * z[i - 1]) / l;
			}

			double l = 2.0 * h[n - 2] - h[n - 2] * mu[n - 2];
			z[n - 1] = (3.0 * (right_deriv - (y[n - 1] - y[n - 2]) / h[n - 2]) - h[n - 2] * z[n - 2]) / l;
		}

		// �ش����M�����׵�����
		std::vector<double> M(n);
		M[n - 1] = z[n - 1];
		for (int i = n - 2; i >= 0; --i) {
			M[i] = z[i] - mu[i] * M[i + 1];
		}

		// ������������ϵ��
		a.resize(n - 1);
		b.resize(n - 1);
		c.resize(n - 1);
		d.resize(n - 1);

		for (size_t i = 0; i < n - 1; ++i) {
			a[i] = (M[i + 1] - M[i]) / (6.0 * h[i]);
			b[i] = M[i] / 2.0;
			c[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (M[i + 1] + 2.0 * M[i]) / 6.0;
			d[i] = y[i];
		}
	}

	double CubicSpline::interpolate(double x_val) const {
		auto it = std::upper_bound(x.begin(), x.end(), x_val);
		if (it == x.begin()) return y[0];
		if (it == x.end()) return y.back();

		size_t i = it - x.begin() - 1;
		double dx = x_val - x[i];

		return a[i] * dx*dx*dx + b[i] * dx*dx + c[i] * dx + d[i];
	}

	std::vector<double> CubicSpline::evaluate(const std::vector<double>& x_vals) const {
		std::vector<double> result;
		result.reserve(x_vals.size());
		for (double x : x_vals) {
			result.push_back(interpolate(x));
		}
		return result;
	}

	std::vector<std::pair<double, double>> CubicSpline::get_points() const {
		std::vector<std::pair<double, double>> points;
		points.reserve(x.size());
		for (size_t i = 0; i < x.size(); ++i) {
			points.emplace_back(x[i], y[i]);
		}
		return points;
	}

} // namespace CurveFitting