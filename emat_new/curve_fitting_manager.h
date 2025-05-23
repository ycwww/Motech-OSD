#ifndef CURVE_FITTING_MANAGER_H
#define CURVE_FITTING_MANAGER_H

#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <memory>
#include <functional>
#include "cubic_spline.h"

namespace CurveFitting {

	class CurveFittingManager {
	private:
		size_t max_threads;  // 最大线程数

	public:
		// 定义回调函数类型
		using ProgressCallback = std::function<void(size_t, size_t)>;

		// 构造函数：指定最大并发线程数
		CurveFittingManager(size_t max_threads = std::thread::hardware_concurrency());

		// 多线程拟合多条曲线（不再使用模板参数推导）
		std::unordered_map<int, std::shared_ptr<CubicSpline>> fit_curves(
			const std::unordered_map<int, std::vector<std::pair<double, double>>>& angle_point,
			bool natural = true,
			double left_deriv = 0.0,
			double right_deriv = 0.0,
			ProgressCallback callback = [](size_t, size_t) {});
	};

} // namespace CurveFitting

#endif // CURVE_FITTING_MANAGER_H