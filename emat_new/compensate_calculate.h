#pragma once
#include <QPair>
#include "general_define.h"
#include <vector>
#include <QStringList>
#include <QObject>

typedef struct
{
	float axis[AXIS_NUMBER];
	float real_thick;
	float theroy_thick;
	float up_limit;
	float low_limit;
	int gird_number;
	double compen_value = 0;
}MEASURE_POINT_S;

enum MEASURE_TYPE_E
{
	POINT_MEASURE_TYPE = 1,
	SCAN_MEASURE_TYPE = 2,
};

class compensate_calculate : public QObject
{
	Q_OBJECT

public:
	compensate_calculate(QObject *parent = nullptr);
	int cal_compensate_val(QVector<MEASURE_POINT_S>& point_list, QPair<double, double>& final_range, float max_deviation = 0.6);
	int readSensorData(const QString sensorDataPath, QVector<MEASURE_POINT_S>& point_list, MEASURE_TYPE_E& mea_type);
	int cal_tool_comp_val(QVector<MEASURE_POINT_S>& point_list, QVector<QPair<int, double>>& tool_comp, MEASURE_TYPE_E mea_type);
	int cal_point_by_point_compensate(QVector<MEASURE_POINT_S>& point_list, const QStringList& origin_mpf, QStringList& compensate_mpf);

	void accept_tool_length_threshold(QString threshold, float standard, float smooth_factor);
private:
	QString tool_length_threshold;
	QPair<double, double> findIntersection(const QVector<QPair<double, double>>& ranges);
	int cal_tool_comp_val_scan(QVector<MEASURE_POINT_S>& point_list,  double& tool_comp);
	
};

