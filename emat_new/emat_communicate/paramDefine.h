#pragma once
#include "typeDefine.h"


const int WAVE_POINT_NUM = 1500;
struct PARAM_STRUCT_S
{
	UINT16 index; //������
	INT16 value;  //����ֵ
};

//�Ƿ�ʹ������ƽ�� 1ʹ������ƽ����0��ʹ��
typedef enum
{
	NONE_SMOOTH = 0,
	USING_CURVE_SMOOTH = 1
}IS_CURVE_SMOOTH;
/*�ز�����*/
typedef enum
{
	ENVELOPE_WAVE = 0, //���粨
	ORIGIN_WAVE = 1    //ԭʼ��
}WAVE_TYPE_E;
/*Ƶ��ѡ��*/
typedef enum
{
	LOW_FREQUENCY = 0,    //��Ƶ
	HIGH_FREQUENCY = 1    //��Ƶ
}FREQUENCY_SELECT_E;
/*����ģʽ*/
typedef enum
{
	MEASURE_AUTO = 0,        //�Զ�
	MEASURE_HALF_AUTO,
	MEASURE_MANUAL,      //�ֶ�
	
	MEASURE_THIN_THIKNESS = 4,   //�ⱡ��ģʽ
}MEASURE_MODE_E;
/*����ģʽ����*/
typedef enum
{
	PP_CONTROL_MODE = 0,
	AUTO_CONTROL_MODE =1,
}MEASURE_MODE_CONTROL_E;
/*�ֶ�����ģʽ����*/
typedef enum
{
	MANUAL_PP_CONTROL_MODE = 0,
	MANUAL_ZP_CONTROL_MODE = 1,
}MANUAL_MEASURE_MODE;

typedef enum
{
	DISPLAY_THICKNESS = 0,
	DISPLAY_WAVE_TYPE = 1,
}LCD_DISPLAY_SWITCH;
typedef enum
{
	SELF_MULTIPLYING = 0,
	ORIGINAL_SIGNAL = 1,
}SELF_MULTIPLY_ALGORITHM;

typedef enum
{
	ALUMINIUM_ALLOY = 0,
	TITANIUM_ALLOY = 1,
}MESURE_MATERIAL_E;

class DEVICE_PARAM_S
{
public:
	PARAM_STRUCT_S gate2End;          //0.բ��2����
	PARAM_STRUCT_S zeroPointEnvelope; //1.̽ͷ��㣨���粨��
	PARAM_STRUCT_S ultraSpeed;        //2.��������
	PARAM_STRUCT_S zeroPointOrigin;	  //3.̽ͷ��㣨ԭʼ����
	PARAM_STRUCT_S gate2Start;        //4.բ��2��ʼ
	PARAM_STRUCT_S gate1Start;        //5.բ��1��ʼ
	PARAM_STRUCT_S gate1End;          //6.բ��1����
	PARAM_STRUCT_S calibrationThick;  //7.�����
	PARAM_STRUCT_S temperature;       //8.�����¶�
	PARAM_STRUCT_S curveSmooth;       //9.�Ƿ�ʹ������ƽ�� IS_CURVE_SMOOTH
	PARAM_STRUCT_S smoothTime;        //10.ƽ������
	PARAM_STRUCT_S sensorGain;        //11.̽ͷ����
	PARAM_STRUCT_S ferqSelect;        //12.Ƶ��ѡ�� FREQUENCY_SELECT_E
	PARAM_STRUCT_S waveType;          //13.�ز�����  WAVE_TYPE_E
	PARAM_STRUCT_S measureMode;       //14.����ģʽ
	PARAM_STRUCT_S SNR;               //15.�����
	PARAM_STRUCT_S dampingRadio;      //16.�ź�˥����ֵ
	PARAM_STRUCT_S envelopeWidth;     //17.����
	PARAM_STRUCT_S widthHeightRadio;  //18.���粨��߱�
	PARAM_STRUCT_S thresholdValue;    //19.��ֵ
	PARAM_STRUCT_S emitInterval;      //20.������
	PARAM_STRUCT_S pulseNumber;       //21.��������
	PARAM_STRUCT_S excitationFrequency;  //22.����Ƶ��
	PARAM_STRUCT_S startDisplay;         //23.��ʾ��ʼ
	PARAM_STRUCT_S stopDisplay;          //24.��ʾ����
	PARAM_STRUCT_S communicateMode;      //25. ͨѶģʽ
	PARAM_STRUCT_S measureControlMode;    //26.��������ģʽ
	PARAM_STRUCT_S manualMeasureMode;     //27.�ֶ���������ģʽ
	PARAM_STRUCT_S lcdDisplayTxt;          //28.LCD����ʾ�����л�
	PARAM_STRUCT_S selfMultiplying;        //29.�Գ��㷨
	PARAM_STRUCT_S  thicknessSmooth;        //30.���ƽ��
	PARAM_STRUCT_S  measureMaterial;        //31.������ 0.�� 1.�ѺϽ�
};

const int PARAM_SZIE = sizeof(DEVICE_PARAM_S) / sizeof(PARAM_STRUCT_S);
//�豸�Ǳ����
union DEVICE_ULTRA_PARAM_U
{
	DEVICE_PARAM_S stParam;
	PARAM_STRUCT_S arrParam[sizeof(DEVICE_PARAM_S) / sizeof(PARAM_STRUCT_S)];
};
void init_device_param(DEVICE_ULTRA_PARAM_U& deviceParam);

