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

// 三次样条插值类（单曲线拟合）
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
		double right_deriv = 0.0) {

		size_t n = points.size();
		if (n < 2) throw std::invalid_argument("至少需要两个点进行插值");

		// 分离x和y坐标，并确保x是严格递增的
		x.reserve(n);
		y.reserve(n);

		for (const auto& point : points) {
			x.push_back(point.first);
			y.push_back(point.second);
		}

		// 检查x是否严格递增，必要时排序
		bool sorted = true;
		for (size_t i = 1; i < n; ++i) {
			if (x[i] <= x[i - 1]) {
				sorted = false;
				break;
			}
		}

		if (!sorted) {
			// 按x坐标排序
			std::vector<std::pair<double, double>> sorted_points = points;
			std::sort(sorted_points.begin(), sorted_points.end(),
				[](const auto& a, const auto& b) { return a.first < b.first; });

			// 重新填充x和y
			x.clear();
			y.clear();
			for (const auto& point : sorted_points) {
				x.push_back(point.first);
				y.push_back(point.second);
			}
		}

		// 计算各区间的步长
		std::vector<double> h(n - 1);
		for (size_t i = 0; i < n - 1; ++i) {
			h[i] = x[i + 1] - x[i];
		}

		// 构建并求解三对角线性方程组以获取二阶导数（弯矩）
		std::vector<double> mu(n - 1);
		std::vector<double> z(n);

		if (natural) {
			// 自然边界条件
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
			// 固定边界条件
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

		// 回代求解M（二阶导数）
		std::vector<double> M(n);
		M[n - 1] = z[n - 1];
		for (int i = n - 2; i >= 0; --i) {
			M[i] = z[i] - mu[i] * M[i + 1];
		}

		// 计算三次样条系数
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

	// 插值函数
	double interpolate(double x_val) const {
		auto it = std::upper_bound(x.begin(), x.end(), x_val);
		if (it == x.begin()) return y[0];
		if (it == x.end()) return y.back();

		size_t i = it - x.begin() - 1;
		double dx = x_val - x[i];

		return a[i] * dx*dx*dx + b[i] * dx*dx + c[i] * dx + d[i];
	}

	// 获取拟合曲线在指定点集上的值
	std::vector<double> evaluate(const std::vector<double>& x_vals) const {
		std::vector<double> result;
		result.reserve(x_vals.size());
		for (double x : x_vals) {
			result.push_back(interpolate(x));
		}
		return result;
	}
};

// 多曲线拟合管理器
class CurveFittingManager {
private:
	size_t max_threads;  // 最大线程数

public:
	// 构造函数：指定最大并发线程数
	CurveFittingManager(size_t max_threads = std::thread::hardware_concurrency())
		: max_threads(max_threads) {}

	// 多线程拟合多条曲线（适配你的数据结构）
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

		// 工作函数：拟合单条曲线
		auto worker = [&](int group_id, const std::vector<std::pair<double, double>>& points) {
			try {
				auto spline = std::make_shared<CubicSpline>(points, natural, left_deriv, right_deriv);

				// 更新结果
				std::lock_guard<std::mutex> lock(mtx);
				results[group_id] = spline;
				completed++;
				callback(completed, num_curves);
			}
			catch (const std::exception& e) {
				std::cerr << "组 " << group_id << " 拟合失败: " << e.what() << std::endl;
			}
		};

		// 控制最大并发线程数
		for (const auto& pair : angle_point) {
			int group_id = pair.first;
			const auto& points = pair.second;

			threads.emplace_back(worker, group_id, points);

			// 当达到最大线程数时等待一个线程完成
			if (threads.size() >= max_threads) {
				threads.back().join();
				threads.pop_back();
			}
		}

		// 等待所有剩余线程完成
		for (auto& t : threads) {
			t.join();
		}

		return results;
	}
};

// 示例：使用你的数据结构进行多线程曲线拟合
int main() {
	// 创建示例数据结构
	std::unordered_map<int, std::vector<std::pair<double, double>>> angle_point;

	// 生成3条测试曲线（分组ID为0,1,2）
	for (int group_id = 0; group_id < 3; ++group_id) {
		std::vector<std::pair<double, double>> points;

		// 生成每条曲线的10个点（不同的正弦波）
		for (int i = 0; i < 10; ++i) {
			double x = i * 0.5;
			double y = std::sin(x * (group_id + 1)) + (double)rand() / RAND_MAX * 0.1;  // 添加噪声
			points.emplace_back(x, y);
		}

		angle_point[group_id] = points;
	}

	// 创建曲线拟合管理器
	CurveFittingManager manager;

	// 拟合所有曲线并显示进度
	std::cout << "开始拟合曲线..." << std::endl;

	auto results = manager.fit_curves(
		angle_point, true, 0.0, 0.0,
		[](size_t completed, size_t total) {
		std::cout << "\r进度: " << completed << "/" << total << " ("
			<< static_cast<int>(100.0 * completed / total) << "%)" << std::flush;
	}
	);

	std::cout << "\n拟合完成！" << std::endl;

	// 验证第一条曲线的拟合结果
	if (!results.empty()) {
		int sample_group_id = angle_point.begin()->first;
		std::cout << "\n组 " << sample_group_id << " 的拟合结果示例：" << std::endl;

		// 定义要评估的点
		std::vector<double> test_points = { 1.0, 2.0, 3.0 };

		// 获取该组的拟合曲线
		auto spline = results[sample_group_id];
		if (spline) {
			// 计算插值结果
			auto values = spline->evaluate(test_points);

			// 输出结果
			for (size_t i = 0; i < test_points.size(); ++i) {
				std::cout << "x = " << test_points[i] << ", y = " << values[i] << std::endl;
			}
		}
	}

	return 0;
}