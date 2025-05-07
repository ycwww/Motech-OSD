#pragma once
#include <QString>
#include <vector>
#include "general_define.h"
#include "file_operator.h"
#include "compensate_calculate.h"

const QString COMPENSATE_MPF_NAME = "TEST_COMP";


typedef struct {
	double i;
	double j;
	double k;
}conversion_coefficient;
struct PointDistance {
	MEASURE_POINT_S point;  // 点的信息
	double distance;        // 距离
};
typedef enum {
	modify_file=0,
	find_point
}FileStatus;
typedef struct {
	double x;
	double y;
	double z;
	double a;
	double b;
	double c;
}MACHINE_COORDINATE;
struct Coordinate {
	double x, y, z;
};
typedef enum {
	laser_comp = 0,
	maching_comp,
}CompStatus;


struct NC_PROGRAM_INDEX
{
	int beginIndex;
	int endIndex;
};
typedef struct
{
	float theory_thick;
	float avr_thick;
	std::vector<POINT_WITH_NORMAL> point;
}SINGLE_GIRD_MEASURE_POINT;

struct SINGLE_GIRD_THICK
{
	double maxThick;
	double minThick;
};
class compProgramGenerate : public QObject
{
	Q_OBJECT

public:
	/*func:readInfo
	brief:
	*/
	compProgramGenerate(QObject *parent = nullptr);
	int generateProgram(const QString sensorDataPath, const QString originNCPath, CompStatus mode);
	void setOriginPos(const POINT_WITH_NORMAL& originPos);
	virtual int measurement_data_comparison(const POINT_WITH_NORMAL& curPos, std::vector<SENSOR_DATA_WITH_POS>& sensorDataWithPos, int index);
	virtual bool isNosise(SENSOR_DATA_WITH_POS sensorData, float basic, float tolerance);
	std::vector<SENSOR_DATA_WITH_POS> vecSensorData;
	bool isFilter;
	//float maxBais;
	float basicThick;
	float toleranceThick;
	float theoryThick;
	float mRangeAxisSize[2];
	TOOL_AXIS_INDEX mAxisIndex;
	void setSmoothParam(float startIndex, float endIndex, TOOL_AXIS_INDEX axis_index = INDEX_TOOL_AXIS_Z);
	int generateSimulateData(const QString mpfFilePath, float simulateThick, const QString outFilePath);
	int dataFilter(const QString sensorDataPath);
private:
	
	std::vector<TOOL_POINT_DIFF> vecPointDiff;
	std::vector<NC_PROGRAM_INDEX> vecMachineFeildIndex;
	file_operator fileIO;
	int extract_number_from_mpf(const QString single_line_mpf, POINT_WITH_NORMAL&  pnt_and_normal);
	POINT_WITH_NORMAL mOriginPoint;
	bool calculateComVal(std::vector<TOOL_POINT_DIFF>& vecPointNormal, QStringList& originMpf, QString fileName);
	void readSensorData(const QString sensorDataPath);
	bool findBeginEndIndex(const QStringList* pStrLst, std::vector<NC_PROGRAM_INDEX>& vecInex);
	int multi_parameter_linear(std::vector<TOOL_POINT_DIFF>& vecPointNormal, std::vector<double>& result);
	int smoothAlongWithWorkAxis(std::vector<TOOL_POINT_DIFF>& vecPointNormal);
	int reslove_r100_mpf(const QStringList* pStrLst, float& thickness_theory, int begin_index = 0);
	int isMeasurePointData(const POINT_WITH_NORMAL& toolPoint, std::vector<SENSOR_DATA_WITH_POS>& vecData, float theroy_thick, float& avrThick);
	bool isMeasurefield(int index, const std::vector<NC_PROGRAM_INDEX>& vecInex);
	int moveMean(std::vector<TOOL_POINT_DIFF>& vecDiff, int window_size);

	
public:
	CompStatus comp_status;
	FileStatus file_status;
	QString tool_length_threshold;
	float mSmoothFactor;
	float laserStandard;
	MEASURE_POINT_S findClosestPoint(const QList<MEASURE_POINT_S>& points, double targetX, double targetY, double targetZ);
	MEASURE_POINT_S findClosestPoint(const QList<MEASURE_POINT_S>& points, double targetX, double targetY, double targetZ, double targetB);
	MACHINE_COORDINATE machine_coordinate;
	QList<MEASURE_POINT_S> parts;
	QList<MEASURE_POINT_S> compen_points;
	compensate_calculate cal_comp_val;
	conversion_coefficient Coordinate_change(double &x, double &y, double &z, double angle_x, double angle_y, double angle_z, double compensate);
	QVector<MEASURE_POINT_S> findClosestPoints(const QList<MEASURE_POINT_S>& points, double targetX, double targetY, double targetZ, double targetB,int numClosest);
	double calculateDistance(double x1, double y1, double z1, double x2, double y2, double z2);
	QString modifyXYZCoordinates(QString& line);
	void modifyFile(const QString& filePath);
	QList<MEASURE_POINT_S> cubicBSplineSmoothZ(const QList<MEASURE_POINT_S>& points, double tension = 0.5);
public slots:
	void accept_tool_length_threshold(QString threshold, float standard, float smooth_factor);
};
class virticalMillNCGenerate : public compProgramGenerate
{
public:
	void setMillDirc(TOOL_AXIS_INDEX graduationDirc)
	{
		mGraduationDirc = graduationDirc;
	}
	int measurement_data_comparison(const POINT_WITH_NORMAL& curPos,
		std::vector<SENSOR_DATA_WITH_POS>& sensorDataWithPos, int index) override
	{
		float abs_difference[2] = { 0 };
		float minAbsDiff = 1000.0;
		int minIndex = -1;

		for (int i = index; i < sensorDataWithPos.size() - 1; i++)
		{
			if (3.0 > abs(curPos.data[mGraduationDirc] - sensorDataWithPos.at(i).wcs[mGraduationDirc]))
			{
				continue;
			}
			abs_difference[0] = sqrt(pow(curPos.data[0] - sensorDataWithPos.at(i).wcs[0], 2) +
				pow(curPos.data[1] - sensorDataWithPos.at(i).wcs[1], 2) +
			pow((curPos.data[2] - sensorDataWithPos.at(i).wcs[2]), 2));

			if (minAbsDiff > abs_difference[0])
			{
				minAbsDiff = abs_difference[0];
				minIndex = i;
			}
		}
		return minIndex;
	}
private:
	TOOL_AXIS_INDEX mGraduationDirc;

};
class ultraCompProgram : public compProgramGenerate
{
public:
	bool isNosise(SENSOR_DATA_WITH_POS sensorData, float basic, float tolerance)override
	{
		float lowLimit = basic - tolerance;
		float upLimit = basic + tolerance;
		if (sensorData.sensorVal < lowLimit || sensorData.sensorVal > upLimit)
		{
			return true;
		}
		return false;
	}
};




