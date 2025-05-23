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
		size_t max_threads;  // ����߳���

	public:
		// ����ص���������
		using ProgressCallback = std::function<void(size_t, size_t)>;

		// ���캯����ָ����󲢷��߳���
		CurveFittingManager(size_t max_threads = std::thread::hardware_concurrency());

		// ���߳���϶������ߣ�����ʹ��ģ������Ƶ���
		std::unordered_map<int, std::shared_ptr<CubicSpline>> fit_curves(
			const std::unordered_map<int, std::vector<std::pair<double, double>>>& angle_point,
			bool natural = true,
			double left_deriv = 0.0,
			double right_deriv = 0.0,
			ProgressCallback callback = [](size_t, size_t) {});
	};

} // namespace CurveFitting

#endif // CURVE_FITTING_MANAGER_H