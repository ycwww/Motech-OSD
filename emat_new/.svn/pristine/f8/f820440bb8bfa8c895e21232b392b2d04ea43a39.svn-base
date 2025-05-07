#pragma once
#include <QString>

typedef enum
{
	CONFIG_FILE_FAILED = -1,
	CONFIG_FILE_SUCCESS = 1,
}CONFIG_FILE_STATUS_E;
typedef struct
{
	QString port_number;
	int buad_rate;

}SYS_CONFIG_EMAT;
class config_file_operate
{
public:
	config_file_operate::config_file_operate();
	void get_sys_config(SYS_CONFIG_EMAT& config);
	int set_sys_config(const SYS_CONFIG_EMAT& config);

private:
	void init_def_sys_config();
	SYS_CONFIG_EMAT mConfig;

	

};

