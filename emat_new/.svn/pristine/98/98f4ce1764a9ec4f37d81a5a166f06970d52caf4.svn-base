#pragma once

#ifndef ERROR_SLOEM
#define ERROR_SLOEM (-1)
#endif // !ERROR_SLOEM

#ifndef EOK
#define EOK (0)
#endif // !EOK

#ifndef AXIS_NUMBER
#define AXIS_NUMBER (6)
#endif // !AXIS_NUMBER

typedef enum
{
	INDEX_TOOL_AXIS_X = 0,
	INDEX_TOOL_AXIS_Y = 1,
	INDEX_TOOL_AXIS_Z = 2,
	INDEX_TOOL_AXIS_A = 3,
	INDEX_TOOL_AXIS_B = 4,
	INDEX_TOOL_AXIS_C = 5,

	MAX_TOOL_AXIS_INDEX = AXIS_NUMBER
}TOOL_AXIS_INDEX;

struct SENSOR_DATA_WITH_POS
{
	float wcs[AXIS_NUMBER];
	float sensorVal;
	float standard_value;
};
struct FIVE_AXIS_POINT
{
	float x;
	float y;
	float z;
	float a;
	float b;
	float c;
};
union POINT_WITH_NORMAL
{
	FIVE_AXIS_POINT point;
	float data[AXIS_NUMBER];
};
typedef struct {
	POINT_WITH_NORMAL wcs;
	int index;
	float diff;
}TOOL_POINT_DIFF;