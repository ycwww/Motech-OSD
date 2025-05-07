#pragma once
#include <QVector>
#include <QPair>
typedef enum
{
	CONFIG_ULTRA_SPEED_FAILED = -1,
	CONFIG_ULTRA_SPEED_SUCCESS = 1,
}CONFIG_ULTRA_SPEED_E;
typedef struct
{
	float cur_speed;
	int step_number;
	QVector<QPair<float, float>> thickness;

}SYS_CONFIG_ULTRA_SPEED;
class ultra_speed_config
{
public:
	void get_sys_config(const QString congfig_name, SYS_CONFIG_ULTRA_SPEED& config);
	int set_sys_config(const QString congfig_name, const SYS_CONFIG_ULTRA_SPEED& config);


};


