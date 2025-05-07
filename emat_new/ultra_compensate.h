#pragma once

#include <QMainWindow>
#include "ui_ultra_compensate.h"
#include "compensate_calculate.h"
#include "./nc_communicate/connectnc.h"
#include "compProgramGenerate.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ultra_compensateClass; };
QT_END_NAMESPACE

class ultra_compensate : public QMainWindow
{
	Q_OBJECT

public:
	ultra_compensate(QWidget *parent = nullptr);
	~ultra_compensate();
	void set_status_pointer(void* p);
signals:
	void send_tool_length_threshold(QString threshold, float standard,float smooth_factor);
private:
	Ui::ultra_compensateClass *ui;
	void setUltraMeasureUi();
	void set_status_txt(const QString& txt);
	
	QLabel* pStatus;
	QString* pOutStr;

	QVector<MEASURE_POINT_S>* point_list;
	QVector<QPair<int, double>> tool_comp_vec;
	compensate_calculate cal_comp_val;

	ultraCompProgram compensateProgram;
	bool is_finish_cal;

	void origin_move_compensate();
	void tool_comp_compensate();

	void download_ncfile();
	connectNC nc_connect;
	QString NCProgramPath;
private slots:
	void data_process();
	void output_mpf_file();
	void  set_standard_valid(bool checked);
};
