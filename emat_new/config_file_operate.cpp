#include "config_file_operate.h"
#include <QSettings>
#include <qDebug>


void config_file_operate::init_def_sys_config()
{
	mConfig.buad_rate = 115200;
	mConfig.port_number = "COM6";
}

config_file_operate::config_file_operate()
{
	init_def_sys_config();
	QSettings settings("config.ini", QSettings::IniFormat);
	mConfig.buad_rate = settings.value("Serial/buad_rate", 115200).toInt();
	mConfig.port_number = settings.value("Serial/port_number", "COM6").toString();

	qDebug() << mConfig.buad_rate << mConfig.port_number;
}


void config_file_operate::get_sys_config(SYS_CONFIG_EMAT& config)
{
	config = mConfig;
	return;
}

int config_file_operate::set_sys_config(const SYS_CONFIG_EMAT& config)
{
	QSettings settings("config.ini", QSettings::IniFormat);

	mConfig = config; 

	settings.setValue("Serial/buad_rate", mConfig.buad_rate);
	settings.setValue("Serial/port_number", mConfig.port_number);

	return CONFIG_FILE_SUCCESS;
}

