#include "ultra_speed_config.h"
#include <QSettings>
#include <qDebug>




int ultra_speed_config::set_sys_config(const QString congfig_name, const SYS_CONFIG_ULTRA_SPEED& config)
{
	int i = 1;
	QSettings settings(congfig_name, QSettings::IniFormat);

	settings.setValue("cur_speed", config.cur_speed);
	settings.setValue("step_number", config.step_number);
	for (auto pair : config.thickness)
	{
		settings.setValue("step_thickness/measure_thickness_" + QString::number(i), pair.first);
		settings.setValue("step_thickness/actual_thickness_" + QString::number(i), pair.second);
		i++;
	}
	return CONFIG_ULTRA_SPEED_SUCCESS;
}

void ultra_speed_config::get_sys_config(const QString congfig_name, SYS_CONFIG_ULTRA_SPEED& config)
{
	//int i = 1;
	QPair<float, float> tmp;
	QSettings settings(congfig_name, QSettings::IniFormat);

	config.cur_speed = settings.value("cur_speed", 3193.0).toFloat();
	config.step_number = settings.value("step_number", 4).toInt();
	config.thickness.clear();

	for (int i = 0; i < config.step_number; i++)
	{
		tmp.first = settings.value("step_thickness/measure_thickness_" + QString::number(i + 1), 0.0).toFloat();
		tmp.second = settings.value("step_thickness/actual_thickness_" + QString::number(i + 1), 0.0).toFloat();
		config.thickness.push_back(tmp);
	}
}
