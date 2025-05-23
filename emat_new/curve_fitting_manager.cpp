#include "curve_fitting_manager.h"
#include <iostream>
#include <stdexcept>

namespace CurveFitting {

	CurveFittingManager::CurveFittingManager(size_t max_threads)
		: max_threads(max_threads) {
		// ȷ������߳�������Ϊ1
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
			return {}; // ���ؿս��
		}

		std::unordered_map<int, std::shared_ptr<CubicSpline>> results;
		std::vector<std::thread> threads;
		std::mutex mtx;
		size_t completed = 0;
		bool has_error = false;

		// ������������ϵ�������
		auto worker = [&](int group_id, const std::vector<std::pair<double, double>>& points) {
			try {
				// �������Ƿ����㹻�ĵ�
				if (points.size() < 2) {
					throw std::invalid_argument("���ߵ��������㣨������Ҫ2���㣩");
				}

				// ������������Ͻ��
				auto spline = std::make_shared<CubicSpline>(points, natural, left_deriv, right_deriv);

				// �̰߳�ȫ�ظ��½��
				{
					std::lock_guard<std::mutex> lock(mtx);
					results[group_id] = spline;
					completed++;

					// ���ý��Ȼص�
					if (callback) {
						callback(completed, num_curves);
					}
				}
			}
			catch (const std::exception& e) {
				// �̰߳�ȫ�ؼ�¼����
				std::lock_guard<std::mutex> lock(mtx);
				std::cerr << "����: �� " << group_id << " ���ʧ��: " << e.what() << std::endl;
				has_error = true;
			}
			catch (...) {
				std::lock_guard<std::mutex> lock(mtx);
				std::cerr << "����: �� " << group_id << " ����δ֪�쳣" << std::endl;
				has_error = true;
			}
		};

		// ������󲢷��߳���
		for (const auto& pair : angle_point) {
			int group_id = pair.first;
			const auto& points = pair.second;

			// ����Ƿ��Ѵﵽ����߳���
			if (threads.size() >= max_threads) {
				// �ȴ�һ���߳����
				threads.back().join();
				threads.pop_back();
			}

			// �������̴߳���ǰ����
			threads.emplace_back(worker, group_id, points);
		}

		// �ȴ�����ʣ���߳����
		for (auto& t : threads) {
			if (t.joinable()) {
				t.join();
			}
		}

		// ����Ƿ��������߶��ɹ����
		if (results.size() != num_curves) {
			std::cerr << "����: ���ɹ���� " << results.size() << " �����ߣ��� " << num_curves << " ��" << std::endl;
		}

		return results;
	}

} // namespace CurveFitting