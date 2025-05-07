#include "compensate_calculate.h"
#include <QVector>
#include <algorithm>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <qDebug>

compensate_calculate::compensate_calculate(QObject *parent) : QObject(parent)
{
	
}

QPair<double, double> compensate_calculate::findIntersection(const QVector<QPair<double, double>>& ranges)
{
	if (ranges.isEmpty())
	{
		return QPair<double, double>(0.0, 0.0); // Return a default value or handle empty input appropriately
	}

	// Initialize intersection range with the first range
	double low = ranges[0].first;
	double up = ranges[0].second;

	// Traverse through all ranges and compute the intersection
	for (const auto& range : ranges)
	{
		low = std::max(low, range.first);
		up = std::min(up, range.second);

		// If the current intersection is invalid, return an empty range
		if (low > up) 
		{
			return QPair<double, double>(0.0, 0.0);
		}
	}
	return QPair<double, double>(low, up);
}
bool readInfo(const QString& fileName, QList<QString>& readResult)
{
	QFile readFile(fileName);
	if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(NULL, "warning", "cannot open file", QMessageBox::Yes);
		return false;
	}
	while (!readFile.atEnd())
	{
		QByteArray line = readFile.readLine();
		QString str(line);
		if ((str != QString::null) && (str != " ") && (str != "\n"))
		{
			readResult.push_back(str);
		}
	}
	return true;
}
int compensate_calculate::readSensorData(const QString sensorDataPath, QVector<MEASURE_POINT_S>& point_list, MEASURE_TYPE_E& mea_type)
{

	MEASURE_POINT_S tmpPoint;
	QString line;
	if (0 == sensorDataPath.length())
		return ERROR_SLOEM;
	QStringList* pStrLst = new QStringList;
	readInfo(sensorDataPath, *pStrLst);
	point_list.clear();
	for (int i = 0; i < pStrLst->size(); i++)
	{
		line = pStrLst->at(i).trimmed();
		QStringList tmp = line.split(",");
		if (AXIS_NUMBER + 5 == tmp.size())
		{
			mea_type = POINT_MEASURE_TYPE;
		}
		else if (AXIS_NUMBER + 3 == tmp.size())
		{
			mea_type = SCAN_MEASURE_TYPE;
		}

	}

	for (int i = 0; i < pStrLst->size(); i++)
	{
		line = pStrLst->at(i).trimmed();
		QStringList tmp = line.split(",");
		
		if (mea_type == POINT_MEASURE_TYPE)
		{
			if (AXIS_NUMBER + 5 != tmp.size())
			{
				continue;
			}
			for (int j = 0; j < AXIS_NUMBER; j++)
			{
				tmpPoint.axis[j] = tmp.at(j).toDouble();
			}
			tmpPoint.real_thick = tmp.at(AXIS_NUMBER).toDouble();
			tmpPoint.theroy_thick = tmp.at(AXIS_NUMBER + 1).toDouble();
			tmpPoint.up_limit = tmp.at(AXIS_NUMBER + 2).toDouble();
			tmpPoint.low_limit = tmp.at(AXIS_NUMBER + 3).toDouble();
			tmpPoint.gird_number = tmp.at(AXIS_NUMBER + 4).toInt();
		}
		else
		{
			if (AXIS_NUMBER + 3 != tmp.size())
			{
				continue;
			}
			for (int j = 0; j < AXIS_NUMBER; j++)
			{
				tmpPoint.axis[j] = tmp.at(j).toDouble();
			}
			tmpPoint.real_thick = tmp.at(AXIS_NUMBER).toDouble();
			tmpPoint.theroy_thick = tmp.at(AXIS_NUMBER + 1).toDouble();
			tmpPoint.gird_number = tmp.at(AXIS_NUMBER + 2).toInt();
		}

		point_list.push_back(tmpPoint);
	}

	delete pStrLst;
	return EOK;
}
// 计算均值
double mean_thick(const std::vector<double>& data)
{
	double sum = std::accumulate(data.begin(), data.end(), 0.0);
	return sum / data.size();
}

// 计算标准差
double standard_deviation(const std::vector<double>& data, double mean) 
{
	if (0 == data.size())
	{
		return -1.0;
	}
	double sum = 0.0;
	for (double value : data) {
		sum += (value - mean) * (value - mean);
	}
	return std::sqrt(sum / data.size());
}
void compensate_calculate::accept_tool_length_threshold(QString threshold, float standard, float smooth_factor) {
	tool_length_threshold = threshold;
}
int compensate_calculate::cal_compensate_val( QVector<MEASURE_POINT_S>& point_list, QPair<double, double>& final_range, float max_deviation)
{
	QPair<double, double> tmpRange;
	QVector<QPair<double, double>> ranges;
	std::vector<double> bais_lsit;
	float mean_val = 0.0;
	float stand_deviate = -1.0;

	while (0.1 <= max_deviation)
	{
		bais_lsit.clear();
		ranges.clear();
		for (int i = 0; i < point_list.size(); i++)
		{
			if (max_deviation < abs(point_list.at(i).real_thick - point_list.at(i).theroy_thick))
			{
				continue;
			}
			bais_lsit.push_back(point_list.at(i).real_thick - point_list.at(i).theroy_thick);
		}
		mean_val = mean_thick(bais_lsit);
		stand_deviate = standard_deviation(bais_lsit, mean_val);

		for (auto it = point_list.begin(); it != point_list.end(); it++)
		{
			if (mean_val - 3 * stand_deviate > it->real_thick - it->theroy_thick ||
				mean_val + 3 * stand_deviate < it->real_thick - it->theroy_thick)
			{
				continue;
			}
			tmpRange.first = (it->theroy_thick - it->real_thick) + it->low_limit;
			tmpRange.second = (it->theroy_thick - it->real_thick) + it->up_limit;
			ranges.append(tmpRange);
		}
		final_range = findIntersection(ranges);
		if (0.0001 > abs(final_range.first) && 0.0001 > abs(final_range.second))
		{
			max_deviation -= 0.03;
		}
		else
		{
			//qDebug() << max_deviation;
			return EOK;
		}
		
	}
	return ERROR_SLOEM;

}

int compensate_calculate::cal_tool_comp_val(QVector<MEASURE_POINT_S>& point_list, QVector<QPair<int, double>>& tool_comp, MEASURE_TYPE_E mea_type)
{
	QVector<MEASURE_POINT_S> tmp_point_list;
	int fomer_gird_num = -1;
	QPair<double, double> range;
	double tmp_comp = 0.0;
	if (0 == point_list.size())
	{
		return -1;
	}
	tool_comp.clear();
	std::sort(point_list.begin(), point_list.end(), [](const MEASURE_POINT_S& a, const MEASURE_POINT_S& b) {
		return a.gird_number < b.gird_number;
	});
	fomer_gird_num = point_list.at(0).gird_number;
	for (int i = 0; i < point_list.size(); i++)
	{
		if (fomer_gird_num == point_list.at(i).gird_number)
		{
			tmp_point_list.append(point_list.at(i));
		}
		else
		{
			if (POINT_MEASURE_TYPE == mea_type)
			{
				cal_compensate_val(tmp_point_list, range, 0.3f);
				if (0.00001 > abs(range.first) && 0.00001 > abs(range.second))
				{
					return -1;
				}
				tool_comp.push_back(qMakePair(fomer_gird_num, (range.first + range.second) / 2));
			}
			else
			{
				cal_tool_comp_val_scan(tmp_point_list, tmp_comp);
				tool_comp.push_back(qMakePair(fomer_gird_num, tmp_comp));
			}
			tmp_point_list.clear();
			tmp_point_list.append(point_list.at(i));
		}
		fomer_gird_num = point_list.at(i).gird_number;
	}
	if (tmp_point_list.size() != 0)
	{
		if (POINT_MEASURE_TYPE == mea_type)
		{
			cal_compensate_val(tmp_point_list, range, 0.4f);
			if (0.00001 > abs(range.first) && 0.00001 > abs(range.second))
			{
				return -1;
			}
			tool_comp.push_back(qMakePair(fomer_gird_num, (range.first + range.second) / 2));
		}
		else
		{
			cal_tool_comp_val_scan(tmp_point_list, tmp_comp);
			tool_comp.push_back(qMakePair(fomer_gird_num, tmp_comp));
		}
		tmp_point_list.clear();
	}
	return EOK;
}

// 去噪处理：移动平均滤波
QVector<float> movingAverageFilter(const QVector<float>& data, int window_size) {
	QVector<float> filtered_data;
	int half_window = window_size / 2;

	for (int i = 0; i < data.size(); ++i) {
		float sum = 0.0f;
		int count = 0;
		for (int j = -half_window; j <= half_window; ++j) {
			if (i + j >= 0 && i + j < data.size()) {
				sum += data[i + j];
				count++;
			}
		}
		filtered_data.append(sum / count);
	}
	return filtered_data;
}

// 计算平均值
float calculateAverage(const QVector<float>& data) {
	if (data.isEmpty()) {
		return 0.0f;
	}
	float sum = std::accumulate(data.begin(), data.end(), 0.0f);
	return sum / data.size();
}
int compensate_calculate::cal_tool_comp_val_scan(QVector<MEASURE_POINT_S>& point_list, double& tool_comp)
{
	QVector<float> differences;
	QVector<float> denoised_differences;
	for (const auto& point : point_list) 
	{
		if (tool_length_threshold.size() > 0) {
			if (tool_length_threshold.toDouble() < abs(point.theroy_thick - point.real_thick))
			{
				continue;
			}
		}
		differences.append(point.theroy_thick - point.real_thick);
	}
	if (0 == differences.size())
	{
		tool_comp = 0;
		return -1;
	}
	// 去噪处理
	int window_size = 4; // 窗口大小，可根据需要调整
	if (window_size < point_list.size())
	{
		denoised_differences = movingAverageFilter(differences, window_size);
		// 计算平均值
		tool_comp = calculateAverage(denoised_differences);
	}
	else
	{
		tool_comp = calculateAverage(differences);
	}
	
	return 0;
}

int compensate_calculate::cal_point_by_point_compensate(QVector<MEASURE_POINT_S>& point_list, const QStringList& origin_mpf, QStringList& compensate_mpf)
{

	if (0 == point_list.size() || 0 == origin_mpf.size())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未导入测量数据或补偿程序"), QMessageBox::Yes);
		return -1;
	}

	return EOK;


}
