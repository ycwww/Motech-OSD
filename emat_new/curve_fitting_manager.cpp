#include "curve_fitting_manager.h"
#include <iostream>
#include <stdexcept>

namespace CurveFitting {

	CurveFittingManager::CurveFittingManager(size_t max_threads)
		: max_threads(max_threads) {
		// 确保最大线程数至少为1
		if (max_threads < 1) {
			this->max_threads = 1;
		}
	}

	std::unordered_map<int, std::shared_ptr<CubicSpline>>
		CurveFittingManager::fit_curves(
			const std::unordered_map<int, std::vector<std::pair<double, double>>>& angle_point,
			bool natural, double left_deriv, double right_deriv, ProgressCallback callback) {

		size_t num_curves = angle_point.size();
		if (num_curves == 0) {
			return {}; // 返回空结果
		}

		std::unordered_map<int, std::shared_ptr<CubicSpline>> results;
		std::vector<std::thread> threads;
		std::mutex mtx;
		size_t completed = 0;
		bool has_error = false;

		// 工作函数：拟合单条曲线
		auto worker = [&](int group_id, const std::vector<std::pair<double, double>>& points) {
			try {
				// 检查该组是否有足够的点
				if (points.size() < 2) {
					throw std::invalid_argument("曲线点数量不足（至少需要2个点）");
				}

				// 创建并保存拟合结果
				auto spline = std::make_shared<CubicSpline>(points, natural, left_deriv, right_deriv);

				// 线程安全地更新结果
				{
					std::lock_guard<std::mutex> lock(mtx);
					results[group_id] = spline;
					completed++;

					// 调用进度回调
					if (callback) {
						callback(completed, num_curves);
					}
				}
			}
			catch (const std::exception& e) {
				// 线程安全地记录错误
				std::lock_guard<std::mutex> lock(mtx);
				std::cerr << "错误: 组 " << group_id << " 拟合失败: " << e.what() << std::endl;
				has_error = true;
			}
			catch (...) {
				std::lock_guard<std::mutex> lock(mtx);
				std::cerr << "错误: 组 " << group_id << " 发生未知异常" << std::endl;
				has_error = true;
			}
		};

		// 控制最大并发线程数
		for (const auto& pair : angle_point) {
			int group_id = pair.first;
			const auto& points = pair.second;

			// 检查是否已达到最大线程数
			if (threads.size() >= max_threads) {
				// 等待一个线程完成
				threads.back().join();
				threads.pop_back();
			}

			// 创建新线程处理当前曲线
			threads.emplace_back(worker, group_id, points);
		}

		// 等待所有剩余线程完成
		for (auto& t : threads) {
			if (t.joinable()) {
				t.join();
			}
		}

		// 检查是否所有曲线都成功拟合
		if (results.size() != num_curves) {
			std::cerr << "警告: 仅成功拟合 " << results.size() << " 条曲线，共 " << num_curves << " 条" << std::endl;
		}

		return results;
	}

} // namespace CurveFitting