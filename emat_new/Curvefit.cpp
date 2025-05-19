#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <unordered_map>
#include <utility>  // for std::pair
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <cmath>

// ����������ֵ�ࣨ��������ϣ�
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
		double right_deriv = 0.0) {

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

	// ��ֵ����
	double interpolate(double x_val) const {
		auto it = std::upper_bound(x.begin(), x.end(), x_val);
		if (it == x.begin()) return y[0];
		if (it == x.end()) return y.back();

		size_t i = it - x.begin() - 1;
		double dx = x_val - x[i];

		return a[i] * dx*dx*dx + b[i] * dx*dx + c[i] * dx + d[i];
	}

	// ��ȡ���������ָ���㼯�ϵ�ֵ
	std::vector<double> evaluate(const std::vector<double>& x_vals) const {
		std::vector<double> result;
		result.reserve(x_vals.size());
		for (double x : x_vals) {
			result.push_back(interpolate(x));
		}
		return result;
	}
};

// ��������Ϲ�����
class CurveFittingManager {
private:
	size_t max_threads;  // ����߳���

public:
	// ���캯����ָ����󲢷��߳���
	CurveFittingManager(size_t max_threads = std::thread::hardware_concurrency())
		: max_threads(max_threads) {}

	// ���߳���϶������ߣ�����������ݽṹ��
	template<typename ProgressCallback = std::function<void(size_t, size_t)>>
	std::unordered_map<int, std::shared_ptr<CubicSpline>> fit_curves(
		const std::unordered_map<int, std::vector<std::pair<double, double>>>& angle_point,
		bool natural = true,
		double left_deriv = 0.0,
		double right_deriv = 0.0,
		ProgressCallback callback = [](size_t, size_t) {}) {

		size_t num_curves = angle_point.size();
		if (num_curves == 0) return {};

		std::unordered_map<int, std::shared_ptr<CubicSpline>> results;
		std::vector<std::thread> threads;
		std::mutex mtx;
		size_t completed = 0;

		// ������������ϵ�������
		auto worker = [&](int group_id, const std::vector<std::pair<double, double>>& points) {
			try {
				auto spline = std::make_shared<CubicSpline>(points, natural, left_deriv, right_deriv);

				// ���½��
				std::lock_guard<std::mutex> lock(mtx);
				results[group_id] = spline;
				completed++;
				callback(completed, num_curves);
			}
			catch (const std::exception& e) {
				std::cerr << "�� " << group_id << " ���ʧ��: " << e.what() << std::endl;
			}
		};

		// ������󲢷��߳���
		for (const auto& pair : angle_point) {
			int group_id = pair.first;
			const auto& points = pair.second;

			threads.emplace_back(worker, group_id, points);

			// ���ﵽ����߳���ʱ�ȴ�һ���߳����
			if (threads.size() >= max_threads) {
				threads.back().join();
				threads.pop_back();
			}
		}

		// �ȴ�����ʣ���߳����
		for (auto& t : threads) {
			t.join();
		}

		return results;
	}
};

// ʾ����ʹ��������ݽṹ���ж��߳��������
int main() {
	// ����ʾ�����ݽṹ
	std::unordered_map<int, std::vector<std::pair<double, double>>> angle_point;

	// ����3���������ߣ�����IDΪ0,1,2��
	for (int group_id = 0; group_id < 3; ++group_id) {
		std::vector<std::pair<double, double>> points;

		// ����ÿ�����ߵ�10���㣨��ͬ�����Ҳ���
		for (int i = 0; i < 10; ++i) {
			double x = i * 0.5;
			double y = std::sin(x * (group_id + 1)) + (double)rand() / RAND_MAX * 0.1;  // �������
			points.emplace_back(x, y);
		}

		angle_point[group_id] = points;
	}

	// ����������Ϲ�����
	CurveFittingManager manager;

	// ����������߲���ʾ����
	std::cout << "��ʼ�������..." << std::endl;

	auto results = manager.fit_curves(
		angle_point, true, 0.0, 0.0,
		[](size_t completed, size_t total) {
		std::cout << "\r����: " << completed << "/" << total << " ("
			<< static_cast<int>(100.0 * completed / total) << "%)" << std::flush;
	}
	);

	std::cout << "\n�����ɣ�" << std::endl;

	// ��֤��һ�����ߵ���Ͻ��
	if (!results.empty()) {
		int sample_group_id = angle_point.begin()->first;
		std::cout << "\n�� " << sample_group_id << " ����Ͻ��ʾ����" << std::endl;

		// ����Ҫ�����ĵ�
		std::vector<double> test_points = { 1.0, 2.0, 3.0 };

		// ��ȡ������������
		auto spline = results[sample_group_id];
		if (spline) {
			// �����ֵ���
			auto values = spline->evaluate(test_points);

			// ������
			for (size_t i = 0; i < test_points.size(); ++i) {
				std::cout << "x = " << test_points[i] << ", y = " << values[i] << std::endl;
			}
		}
	}

	return 0;
}