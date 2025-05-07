// CL3_IF.h

#pragma once
#pragma managed(push, off)
#include <windows.h>
#ifndef _CL3_IF_H_
#define _CL3_IF_H_

#ifdef CL3_IF_EXPORT
#define CL3_IF_API __declspec(dllexport)
#else
#define CL3_IF_API __declspec(dllimport)
#endif

#define CL3IF_RC_OK 0
#define CL3IF_RC_ERR_INITIALIZE 100
#define CL3IF_RC_ERR_NOT_PARAM 101
#define CL3IF_RC_ERR_USB 102
#define CL3IF_RC_ERR_ETHERNET 103
#define CL3IF_RC_ERR_CONNECT 105
#define CL3IF_RC_ERR_TIMEOUT 106
#define CL3IF_RC_ERR_CHECKSUM 110
#define CL3IF_RC_ERR_LIMIT_CONTROL_ERROR 120
#define CL3IF_RC_ERR_UNKNOWN 127

#define CL3IF_RC_ERR_STATE_ERROR 81
#define CL3IF_RC_ERR_PARAMETER_NUMBER_ERROR 82
#define CL3IF_RC_ERR_PARAMETER_RANGE_ERROR 83
#define CL3IF_RC_ERR_UNIQUE_ERROR1 84
#define CL3IF_RC_ERR_UNIQUE_ERROR2 85
#define CL3IF_RC_ERR_UNIQUE_ERROR3 86

#define CL3IF_MAX_OUT_COUNT 8
#define CL3IF_MAX_HEAD_COUNT 6
#define CL3IF_MAX_DEVICE_COUNT 3
#define CL3IF_ALL_SETTINGS_DATA_LENGTH 16612
#define CL3IF_PROGRAM_SETTINGS_DATA_LENGTH 1724
#define CL3IF_LIGHT_WAVE_DATA_LENGTH 512
#define CL3IF_MAX_LIGHT_WAVE_COUNT 4

// Version information
typedef struct {
	INT majorNumber;
	INT minorNumber;
	INT revisionNumber;
	INT buildNumber;
} CL3IF_VERSION_INFO;

// Ethernet connection config
typedef struct {
	BYTE ipAddress[4];
	WORD portNo;
	BYTE reserved[2];
} CL3IF_ETHERNET_SETTING;

// Device type
typedef enum {
	CL3IF_DEVICETYPE_INVALID = 0x0000,
	CL3IF_DEVICETYPE_CONTROLLER = 0x0001,
	CL3IF_DEVICETYPE_OPTICALUNIT1 = 0x0011,
	CL3IF_DEVICETYPE_OPTICALUNIT2 = 0x0012,
	CL3IF_DEVICETYPE_OPTICALUNIT3 = 0x0013,
	CL3IF_DEVICETYPE_OPTICALUNIT4 = 0x0014,
	CL3IF_DEVICETYPE_OPTICALUNIT5 = 0x0015,
	CL3IF_DEVICETYPE_OPTICALUNIT6 = 0x0016,
	CL3IF_DEVICETYPE_EXUNIT1 = 0x0041, // Extensional unit 1
	CL3IF_DEVICETYPE_EXUNIT2 = 0x0042  // Extensional unit 2
} CL3IF_DEVICETYPE;

// Additional information (Measurement value)
typedef struct {
	DWORD	triggerCount;
	LONG	pulseCount;
} CL3IF_ADD_INFO;

// Out measurement data
typedef struct {
	LONG measurementValue;
	BYTE valueInfo;
	BYTE judgeResult;
	BYTE reserved[2];
} CL3IF_OUTMEASUREMENT_DATA;

// Measurement Information
typedef struct {
	CL3IF_ADD_INFO addInfo;
	CL3IF_OUTMEASUREMENT_DATA outMeasurementData[CL3IF_MAX_OUT_COUNT];
} CL3IF_MEASUREMENT_DATA;

// Measurement value type
typedef enum {
	CL3IF_VALUE_INFO_VALID,           // Valid data
	CL3IF_VALUE_INFO_JUDGMENTSTANDBY, // Judgment wait
	CL3IF_VALUE_INFO_INVALID,         // Invalid data
	CL3IF_VALUE_INFO_OVERDISPRANGE_P, // Over display range(+)
	CL3IF_VALUE_INFO_OVERDISPRANGE_N  // Over display range(-)
} CL3IF_VALUE_INFO;

// Judgment result
typedef enum {
	CL3IF_JUDGE_RESULT_HI = 0x01, // HI
	CL3IF_JUDGE_RESULT_GO = 0x02, // GO
	CL3IF_JUDGE_RESULT_LO = 0x04  // LO
} CL3IF_JUDGE_RESULT;

// OUT target
typedef enum {
	CL3IF_OUTNO_01 = 0x0001,  // OUT1
	CL3IF_OUTNO_02 = 0x0002,  // OUT2
	CL3IF_OUTNO_03 = 0x0004,  // OUT3
	CL3IF_OUTNO_04 = 0x0008,  // OUT4
	CL3IF_OUTNO_05 = 0x0010,  // OUT5
	CL3IF_OUTNO_06 = 0x0020,  // OUT6
	CL3IF_OUTNO_07 = 0x0040,  // OUT7
	CL3IF_OUTNO_08 = 0x0080,  // OUT8
	CL3IF_OUTNO_ALL = 0x00FF  // ALL
} CL3IF_OUTNO;

// Selected index
typedef enum {
	CL3IF_SELECTED_INDEX_OLDEST,
	CL3IF_SELECTED_INDEX_NEWEST
} CL3IF_SELECTED_INDEX;

// AutoZero target
typedef enum {
	CL3IF_ZERO_GROUP_01 = 0x0001, // Group01
	CL3IF_ZERO_GROUP_02 = 0x0002  // Group02
} CL3IF_ZERO_GROUP;

// Timing target
typedef enum {
	CL3IF_TIMING_GROUP_01 = 0x0001, // Group01
	CL3IF_TIMING_GROUP_02 = 0x0002  // Group02
} CL3IF_TIMING_GROUP;

// Reset target
typedef enum {
	CL3IF_RESET_GROUP_01 = 0x0001, // Group01
	CL3IF_RESET_GROUP_02 = 0x0002  // Group02
} CL3IF_RESET_GROUP;

// Peak number
typedef enum {
	CL3IF_PEAKNO_01 = 0x0001,
	CL3IF_PEAKNO_02 = 0x0002,
	CL3IF_PEAKNO_03 = 0x0004,
	CL3IF_PEAKNO_04 = 0x0008
} CL3IF_PEAKNO;

//Encoder setting
typedef struct {
	BOOL encoderOnOff;
	BYTE reserved1[3];
	BYTE operatingMode;
	BYTE enterMode;
	WORD decimationPoint;
	BYTE detectionEdge;
	BYTE minInputTime;
	BYTE reserved2[2];
	BYTE pulseCountOffsetDetectionLogic;
	BYTE reserved3[3];
	LONG presetValue;
	BYTE reserved4[8];
	BYTE reserved5[8];
	BYTE reserved6[28];
} CL3IF_ENCODER_SETTING;

//Encoder operation mode
typedef enum {
	CL3IF_ENCODER_OPERATING_MODE_OFF,
	CL3IF_ENCODER_OPERATING_MODE_TIMING,
	CL3IF_ENCODER_OPERATING_MODE_TRIGGER
} CL3IF_ENCODER_OPERATING_MODE;

//Encoder input mode
typedef enum {
	CL3IF_ENCODER_ENTER_MODE_1_PHASE_1_MULTIPLIER,
	CL3IF_ENCODER_ENTER_MODE_2_PHASE_1_MULTIPLIER,
	CL3IF_ENCODER_ENTER_MODE_2_PHASE_2_MULTIPLIER,
	CL3IF_ENCODER_ENTER_MODE_2_PHASE_4_MULTIPLIER,
} CL3IF_ENCODER_ENTER_MODE;

//Encoder detection edge
typedef enum{
	CL3IF_ENCODER_DETECTION_EDGE_RISING,
	CL3IF_ENCODER_DETECTION_EDGE_FALLING,
	CL3IF_ENCODER_DETECTION_EDGE_BOTH_EDGE,
} CL3IF_ENCODER_DETECTION_EDGE;

//Enceder min input time
typedef enum{
	CL3IF_ENCODER_MIN_INPUT_TIME_100ns,
	CL3IF_ENCODER_MIN_INPUT_TIME_200ns,
	CL3IF_ENCODER_MIN_INPUT_TIME_500ns,
	CL3IF_ENCODER_MIN_INPUT_TIME_1us,
	CL3IF_ENCODER_MIN_INPUT_TIME_2us,
	CL3IF_ENCODER_MIN_INPUT_TIME_5us,
	CL3IF_ENCODER_MIN_INPUT_TIME_10us,
	CL3IF_ENCODER_MIN_INPUT_TIME_20us,
} CL3IF_ENCODER_MIN_INPUT_TIME;

//Encoder pulse count offset detection logic
typedef enum{
	CL3IF_ENCODER_PULSE_COUNT_OFFSET_DETECTION_LOGIC_OFF,
	CL3IF_ENCODER_PULSE_COUNT_OFFSET_DETECTION_LOGIC_POSITIVE,
	CL3IF_ENCODER_PULSE_COUNT_OFFSET_DETECTION_LOGIC_NEGATIVE,
} CL3IF_ENCODER_PULSE_COUNT_OFFSET_DETECTION_LOGIC;

// Sampling cycle
typedef enum {
	CL3IF_SAMPLINGCYCLE_100USEC,  // 100us
	CL3IF_SAMPLINGCYCLE_200USEC,  // 200us
	CL3IF_SAMPLINGCYCLE_500USEC,  // 500us
	CL3IF_SAMPLINGCYCLE_1000USEC  // 1000us
} CL3IF_SAMPLINGCYCLE;

// Median filter
typedef enum {
	CL3IF_MEDIANFILTER_OFF, // OFF
	CL3IF_MEDIANFILTER_7,   // 7
	CL3IF_MEDIANFILTER_15,  // 15
	CL3IF_MEDIANFILTER_31   // 31
} CL3IF_MEDIANFILTER;

// Mode Auto/Manual
typedef enum {
	CL3IF_MODE_AUTO,   //AUTO
	CL3IF_MODE_MANUAL  //MANUAL
} CL3IF_MODE;

//High sensitivity
typedef struct{
	BOOL highSensitivityOnOff;
	BYTE highSensitivityStrength;
	BYTE thresholdValueFractionalPoint;
} CL3IF_HIGH_SENSITIVITY;

// Intensity
typedef enum {
	CL3IF_INTENSITY_1, // 1
	CL3IF_INTENSITY_2, // 2
	CL3IF_INTENSITY_3, // 3
	CL3IF_INTENSITY_4, // 4
	CL3IF_INTENSITY_5  // 5
} CL3IF_INTENSITY;

// Integration Intensity
typedef enum {
	CL3IF_INTEGRATION_NUMBER_OFF, // OFF
	CL3IF_INTEGRATION_NUMBER_4,   // 4
	CL3IF_INTEGRATION_NUMBER_16,  // 16
	CL3IF_INTEGRATION_NUMBER_64,  // 64
	CL3IF_INTEGRATION_NUMBER_256  // 256
} CL3IF_INTEGRATION_NUMBER;

// Quad Processing
typedef enum {
	CL3IF_QUADPROCESSING_AVERAGE,  // Average
	CL3IF_QUADPROCESSING_MULTIPLE  // Multiple
} CL3IF_QUADPROCESSING;

// Material Used For Refractive Index
typedef enum{
	CL3IF_MATERIAL_VACUUM,
	CL3IF_MATERIAL_QUARTZ,
	CL3IF_MATERIAL_OPTICAL_GLASS,
	CL3IF_MATERIAL_ACRYLIC,
	CL3IF_MATERIAL_PMMA,
	CL3IF_MATERIAL_PMMI,
	CL3IF_MATERIAL_PS,
	CL3IF_MATERIAL_PC,
	CL3IF_MATERIAL_WHITE_FLAT_GLASS,
	CL3IF_MATERIAL_RESERVED1,
	CL3IF_MATERIAL_RESERVED2,
	CL3IF_MATERIAL_RESERVED3,
	CL3IF_MATERIAL_RESERVED4,
	CL3IF_MATERIAL_RESERVED5,
	CL3IF_MATERIAL_RESERVED6,
	CL3IF_MATERIAL_RESERVED7,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL1,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL2,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL3,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL4,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL5,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL6,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL7,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL8,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL9,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL10,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL11,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL12,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL13,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL14,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL15,
	CL3IF_MATERIAL_ADDITIONAL_MATERIAL16
} CL3IF_MATERIAL;

// Measurement method
typedef enum {
	CL3IF_MEASUREMENTMETHOD_DISPLACEMENT,
	CL3IF_MEASUREMENTMETHOD_DISPLACEMENT_FOR_TRANSPARENT,
	CL3IF_MEASUREMENTMETHOD_THICKNESS_FOR_TRANSPARENT,
	CL3IF_MEASUREMENTMETHOD_THICKNESS_2HEADS,
	CL3IF_MEASUREMENTMETHOD_HEIGHTDIFFERENCE_2HEADS,
	CL3IF_MEASUREMENTMETHOD_FORMULA,
	CL3IF_MEASUREMENTMETHOD_AVERAGE,
	CL3IF_MEASUREMENTMETHOD_PEAK_TO_PEAK,
	CL3IF_MEASUREMENTMETHOD_MAX,
	CL3IF_MEASUREMENTMETHOD_MIN,
	CL3IF_MEASUREMENTMETHOD_NO_CALCULATION
} CL3IF_MEASUREMENTMETHOD;

// Measurement method parameter - displacement
typedef struct {
	BYTE headNo;
	BYTE reserved[3];
} CL3IF_MEASUREMENTMETHOD_PARAM_DISPLACEMENT;

// Measurement method parameter - displacement for transparent
typedef struct {
	BYTE headNo;
	BYTE reserved1;
	BYTE peak;
	BYTE reserved2;
} CL3IF_MEASUREMENTMETHOD_PARAM_DISPLACEMENT_FOR_TRANSPARENT;

// Transparent peak
typedef enum {
	CL3IF_TRANSPARENTPEAK_PLUS1,  // +1
	CL3IF_TRANSPARENTPEAK_PLUS2,  // +2
	CL3IF_TRANSPARENTPEAK_PLUS3,  // +3
	CL3IF_TRANSPARENTPEAK_PLUS4,  // +4
	CL3IF_TRANSPARENTPEAK_MINUS1, // -1
	CL3IF_TRANSPARENTPEAK_MINUS2, // -2
	CL3IF_TRANSPARENTPEAK_MINUS3, // -3
	CL3IF_TRANSPARENTPEAK_MINUS4  // -4
} CL3IF_TRANSPARENTPEAK;

// Measurement method parameter - thickness for transparent
typedef struct {
	BYTE headNo;
	BYTE reserved;
	BYTE peak1;
	BYTE peak2;
} CL3IF_MEASUREMENTMETHOD_PARAM_THICKNESS_FOR_TRANSPARENT;

// Measurement method parameter - thickness (2 heads)
typedef struct {
	BYTE headNo1;
	BYTE headNo2;
	BYTE reserved[2];
} CL3IF_MEASUREMENTMETHOD_PARAM_THICKNESS_2HEADS;

// Measurement method parameter - height difference (2 heads)
typedef struct {
	BYTE headNo1;
	BYTE headNo2;
	BYTE reserved[2];
} CL3IF_MEASUREMENTMETHOD_PARAM_HEIGHTDIFFERENCE_2HEADS;

// Measurement method parameter - formula
typedef struct {
	LONG factorA;
	LONG factorB;
	LONG factorC;
	BYTE targetOutX;
	BYTE targetOutY;
	BYTE reserved[2];
} CL3IF_MEASUREMENTMETHOD_PARAM_FORMULA;

// Measurement method parameter - out operation
typedef struct {
	WORD targetOut;
	BYTE reserved[2];
} CL3IF_MEASUREMENTMETHOD_PARAM_OUT_OPERATION;

// Measurement method parameter - no calculation
typedef struct {
	BYTE reserved[4];
} CL3IF_MEASUREMENTMETHOD_PARAM_NO_CALCULATION;

// Measurement method parameter 
typedef union {
	CL3IF_MEASUREMENTMETHOD_PARAM_DISPLACEMENT paramDisplacement;
	CL3IF_MEASUREMENTMETHOD_PARAM_DISPLACEMENT_FOR_TRANSPARENT paramDisplacementForTransparent;
	CL3IF_MEASUREMENTMETHOD_PARAM_THICKNESS_FOR_TRANSPARENT paramThicknessForTransparent;
	CL3IF_MEASUREMENTMETHOD_PARAM_THICKNESS_2HEADS paramThickness2Heads;
	CL3IF_MEASUREMENTMETHOD_PARAM_HEIGHTDIFFERENCE_2HEADS paramHeightDifference2Heads;
	CL3IF_MEASUREMENTMETHOD_PARAM_FORMULA paramFormula;
	CL3IF_MEASUREMENTMETHOD_PARAM_OUT_OPERATION paramOutOperation;
	CL3IF_MEASUREMENTMETHOD_PARAM_NO_CALCULATION paramNoCalculation;
} CL3IF_MEASUREMENTMETHOD_PARAM;

// Filter mode
typedef enum {
	CL3IF_FILTERMODE_MOVING_AVERAGE, // Moving average
	CL3IF_FILTERMODE_LOWPASS,        // Low pass filter
	CL3IF_FILTERMODE_HIGHPASS        // High pass filter
} CL3IF_FILTERMODE;

// Filter average parameter
typedef enum {
	CL3IF_FILTERPARAM_AVERAGE_1,      // 1 time
	CL3IF_FILTERPARAM_AVERAGE_2,      //
	CL3IF_FILTERPARAM_AVERAGE_4,      //
	CL3IF_FILTERPARAM_AVERAGE_8,      //
	CL3IF_FILTERPARAM_AVERAGE_16,     //
	CL3IF_FILTERPARAM_AVERAGE_32,     //
	CL3IF_FILTERPARAM_AVERAGE_64,     //
	CL3IF_FILTERPARAM_AVERAGE_256,    //
	CL3IF_FILTERPARAM_AVERAGE_1024,   //
	CL3IF_FILTERPARAM_AVERAGE_4096,   //
	CL3IF_FILTERPARAM_AVERAGE_16384,  //
	CL3IF_FILTERPARAM_AVERAGE_65536,  //
	CL3IF_FILTERPARAM_AVERAGE_262144  // 262144 times
} CL3IF_FILTERPARAM_AVERAGE;

// Filter cutoff parameter
typedef enum {
	CL3IF_FILTERPARAM_CUTOFF_1000,     // 1000 Hz
	CL3IF_FILTERPARAM_CUTOFF_300,      //
	CL3IF_FILTERPARAM_CUTOFF_100,      //
	CL3IF_FILTERPARAM_CUTOFF_30,       //
	CL3IF_FILTERPARAM_CUTOFF_10,       //
	CL3IF_FILTERPARAM_CUTOFF_3,        //
	CL3IF_FILTERPARAM_CUTOFF_1,        //
	CL3IF_FILTERPARAM_CUTOFF_0_3,      //
	CL3IF_FILTERPARAM_CUTOFF_0_1       // 0.1 Hz
} CL3IF_FILTERPARAM_CUTOFF;

// Hold mode
typedef enum {
	CL3IF_HOLDMODE_NORMAL,
	CL3IF_HOLDMODE_PEAK,
	CL3IF_HOLDMODE_BOTTOM,
	CL3IF_HOLDMODE_PEAK_TO_PEAK,
	CL3IF_HOLDMODE_SAMPLE,
	CL3IF_HOLDMODE_AVERAGE,
	CL3IF_HOLDMODE_AUTOPEAK,
	CL3IF_HOLDMODE_AUTOBOTTOM
} CL3IF_HOLDMODE;

// Hold mode parameter - normal
typedef struct {
	BYTE reserved[4];
} CL3IF_HOLDMODE_PARAM_NORMAL;

// Hold mode parameter - hold
typedef struct {
	BYTE updateCondition;
	BYTE reserved;
	WORD numberOfSamplings;
} CL3IF_HOLDMODE_PARAM_HOLD;

// Trigger mode
typedef enum {
	CL3IF_UPDATECONDITION_EXTERNAL1, // External trigger 1
	CL3IF_UPDATECONDITION_EXTERNAL2, // External trigger 2
	CL3IF_UPDATECONDITION_INTERNAL   // Internal trigger
} CL3IF_UPDATECONDITION;

// Hold mode parameter - auto hold
typedef struct {
	LONG level;
	LONG hysteresis;
} CL3IF_HOLDMODE_PARAM_AUTOHOLD;

// Hold mode parameter
typedef union {
	CL3IF_HOLDMODE_PARAM_NORMAL paramNormal;
	CL3IF_HOLDMODE_PARAM_HOLD paramHold;
	CL3IF_HOLDMODE_PARAM_AUTOHOLD paramAutoHold;
} CL3IF_HOLDMODE_PARAM;

// Display unit
typedef enum {
	CL3IF_DISPLAYUNIT_0_01MM,     // 0.01mm
	CL3IF_DISPLAYUNIT_0_001MM,    // 0.001mm
	CL3IF_DISPLAYUNIT_0_0001MM,   // 0.0001mm
	CL3IF_DISPLAYUNIT_0_00001MM,  // 0.00001mm
	CL3IF_DISPLAYUNIT_0_1UM,      // 0.1um
	CL3IF_DISPLAYUNIT_0_01UM,     // 0.01um
	CL3IF_DISPLAYUNIT_0_001UM     // 0.001um
} CL3IF_DISPLAYUNIT;

// Timing Reset
typedef enum {
	CL3IF_TIMINGRESET_NONE, //None
	CL3IF_TIMINGRESET_1,    //Timing1/Reset1
	CL3IF_TIMINGRESET_2     //Timing2/Reset2
} CL3IF_TIMINGRESET;

// ZERO
typedef enum {
	CL3IF_ZERO_NONE,
	CL3IF_ZERO_1,
	CL3IF_ZERO_2
} CL3IF_ZERO;

// Judgment output setting
typedef struct {
	BYTE logic;
	BYTE strobe;
	BYTE reserved1[2];
	WORD hi;
	WORD go;
	WORD lo;
	BYTE reserved2[2];
} CL3IF_JUDGMENT_OUTPUT;

// Logic AND/OR
typedef enum {
	CL3IF_LOGIC_AND,
	CL3IF_LOGIC_OR
} CL3IF_LOGIC;

// Strobe assigning
typedef enum {
	CL3IF_STROBE_NO,      //None
	CL3IF_STROBE_STROBE1, //STRB1
	CL3IF_STROBE_STROBE2  //STRB2
} CL3IF_STROBE;

// Storage timing
typedef enum {
	CL3IF_STORAGETIMING_MEASUREMENT,
	CL3IF_STORAGETIMING_JUDGMENT
} CL3IF_STORAGETIMING;

// Storage timing parameter - measurement
typedef struct {
	WORD storageCycle;
	BYTE reserved[2];
} CL3IF_STORAGETIMING_PARAM_MEASUREMENT;

// Storage timing parameter - judgment
typedef struct {
	BYTE logic;
	BYTE reserved1[3];
	WORD hi;
	WORD go;
	WORD lo;
	BYTE reserved2[2];
} CL3IF_STORAGETIMING_PARAM_JUDGMENT;

// Storage timing parameter
typedef union {
	CL3IF_STORAGETIMING_PARAM_MEASUREMENT paramMeasurement;
	CL3IF_STORAGETIMING_PARAM_JUDGMENT paramJudgment;
} CL3IF_STORAGETIMING_PARAM;

extern "C"
{
	CL3_IF_API CL3IF_VERSION_INFO WINAPI CL3IF_GetVersion(void);

	CL3_IF_API LONG WINAPI CL3IF_OpenUsbCommunication(LONG deviceId, DWORD timeout);
	CL3_IF_API LONG WINAPI CL3IF_OpenEthernetCommunication(LONG deviceId, CL3IF_ETHERNET_SETTING* ethernetSetting, DWORD timeout);
	CL3_IF_API LONG WINAPI CL3IF_CloseCommunication(LONG deviceId);

	CL3_IF_API LONG WINAPI CL3IF_GetSystemConfiguration(LONG deviceId, BYTE* deviceCount, CL3IF_DEVICETYPE* deviceTypeList);
	CL3_IF_API LONG WINAPI CL3IF_ReturnToFactoryDefaultSetting(LONG deviceId);

	CL3_IF_API LONG WINAPI CL3IF_GetMeasurementData(LONG deviceId, CL3IF_MEASUREMENT_DATA* measurementData);
	CL3_IF_API LONG WINAPI CL3IF_GetTrendIndex(LONG deviceId, DWORD* index);
	CL3_IF_API LONG WINAPI CL3IF_GetTrendData(LONG deviceId, DWORD index, DWORD requestDataCount, DWORD* nextIndex, DWORD* obtainedDataCount, CL3IF_OUTNO* outTarget, DWORD* measurementData);
	CL3_IF_API LONG WINAPI CL3IF_GetStorageIndex(LONG deviceId, CL3IF_SELECTED_INDEX selectedIndex, DWORD* index);
	CL3_IF_API LONG WINAPI CL3IF_GetStorageData(LONG deviceId, DWORD index, DWORD requestDataCount, DWORD* nextIndex, DWORD* obtainedDataCount, CL3IF_OUTNO* outTarget, DWORD* measurementData);
	CL3_IF_API LONG WINAPI CL3IF_AutoZeroSingle(LONG deviceId, BYTE outNo, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_AutoZeroMulti(LONG deviceId, CL3IF_OUTNO outNo, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_AutoZeroGroup(LONG deviceId, CL3IF_ZERO_GROUP group, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_TimingSingle(LONG deviceId, BYTE outNo, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_TimingMulti(LONG deviceId, CL3IF_OUTNO outNo, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_TimingGroup(LONG deviceId, CL3IF_TIMING_GROUP group, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_ResetSingle(LONG deviceId, BYTE outNo);
	CL3_IF_API LONG WINAPI CL3IF_ResetMulti(LONG deviceId, CL3IF_OUTNO outNo);
	CL3_IF_API LONG WINAPI CL3IF_ResetGroup(LONG deviceId, CL3IF_RESET_GROUP group);
	CL3_IF_API LONG WINAPI CL3IF_LightControl(LONG deviceId, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_MeasurementControl(LONG deviceId, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_SwitchProgram(LONG deviceId, BYTE programNo);
	CL3_IF_API LONG WINAPI CL3IF_GetProgramNo(LONG deviceId, BYTE* programNo);
	CL3_IF_API LONG WINAPI CL3IF_LockPanel(LONG deviceId, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_StartStorage(LONG deviceId);
	CL3_IF_API LONG WINAPI CL3IF_StopStorage(LONG deviceId);
	CL3_IF_API LONG WINAPI CL3IF_ClearStorageData(LONG deviceId);
	CL3_IF_API LONG WINAPI CL3IF_GetTerminalStatus(LONG deviceId, WORD* inputTerminalStatus, WORD* outputTerminalStatus);
	CL3_IF_API LONG WINAPI CL3IF_GetPulseCount(LONG deviceId, LONG* pulseCount);
	CL3_IF_API LONG WINAPI CL3IF_ResetPulseCount(LONG deviceId);
	CL3_IF_API LONG WINAPI CL3IF_GetLightWaveform(LONG deviceId, BYTE headNo, CL3IF_PEAKNO peakNo, WORD* waveData);
	CL3_IF_API LONG WINAPI CL3IF_StartLightIntensityTuning(LONG deviceId, BYTE headNo);
	CL3_IF_API LONG WINAPI CL3IF_StopLightIntensityTuning(LONG deviceId, BYTE headNo);
	CL3_IF_API LONG WINAPI CL3IF_CancelLightIntensityTuning(LONG deviceId, BYTE headNo);
	CL3_IF_API LONG WINAPI CL3IF_StartCalibration(LONG deviceId, BYTE headNo);
	CL3_IF_API LONG WINAPI CL3IF_StopCalibration(LONG deviceId, BYTE headNo);
	CL3_IF_API LONG WINAPI CL3IF_CancelCalibration(LONG deviceId, BYTE headNo);

	CL3_IF_API LONG WINAPI CL3IF_SetSettings(LONG deviceId, BYTE* settings);
	CL3_IF_API LONG WINAPI CL3IF_SetProgram(LONG deviceId, BYTE programNo, BYTE* program);
	CL3_IF_API LONG WINAPI CL3IF_SetEncoder(LONG deviceId, CL3IF_ENCODER_SETTING* encoder);
	CL3_IF_API LONG WINAPI CL3IF_SetSamplingCycle(LONG deviceId, BYTE programNo, CL3IF_SAMPLINGCYCLE samplingCycle);
	CL3_IF_API LONG WINAPI CL3IF_SetMutualInterferencePrevention(LONG deviceId, BYTE programNo, BOOL onOff, WORD group);
	CL3_IF_API LONG WINAPI CL3IF_SetAmbientLightFilter(LONG deviceId, BYTE programNo, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_SetMedianFilter(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_MEDIANFILTER medianFilter);
	CL3_IF_API LONG WINAPI CL3IF_SetThreshold(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_MODE mode, BYTE value);
	CL3_IF_API LONG WINAPI CL3IF_SetHighSensitivity(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_HIGH_SENSITIVITY highSensitivity);
	CL3_IF_API LONG WINAPI CL3IF_SetMask(LONG deviceId, BYTE programNo, BYTE headNo, BOOL onOff, LONG position1, LONG position2);
	CL3_IF_API LONG WINAPI CL3IF_SetLightIntensityControl(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_MODE mode, BYTE upperLimit, BYTE lowerLimit);
	CL3_IF_API LONG WINAPI CL3IF_SetPeakShapeFilter(LONG deviceId, BYTE programNo, BYTE headNo, BOOL onOff, CL3IF_INTENSITY intensity);
	CL3_IF_API LONG WINAPI CL3IF_SetLightIntensityIntegration(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_INTEGRATION_NUMBER integrationNumber);
	CL3_IF_API LONG WINAPI CL3IF_SetQuadProcessing(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_QUADPROCESSING processing, BYTE quadValidPoint);
	CL3_IF_API LONG WINAPI CL3IF_SetMeasurementPeaks(LONG deviceId, BYTE programNo, BYTE headNo, BYTE peaks);
	CL3_IF_API LONG WINAPI CL3IF_SetCheckingNumberOfPeaks(LONG deviceId, BYTE programNo, BYTE headNo, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_SetMultiLightIntensityControl(LONG deviceId, BYTE programNo, BYTE headNo, BOOL onOff);
	CL3_IF_API LONG WINAPI CL3IF_SetRefractiveIndexCorrection(LONG deviceId, BYTE programNo, BYTE headNo, BOOL onOff, CL3IF_MATERIAL layer1, CL3IF_MATERIAL layer2, CL3IF_MATERIAL layer3);
	CL3_IF_API LONG WINAPI CL3IF_SetMeasurementMethod(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_MEASUREMENTMETHOD method, CL3IF_MEASUREMENTMETHOD_PARAM param);
	CL3_IF_API LONG WINAPI CL3IF_SetScaling(LONG deviceId, BYTE programNo, BYTE outNo, LONG inputValue1, LONG outputValue1, LONG inputValue2, LONG outputValue2);
	CL3_IF_API LONG WINAPI CL3IF_SetOffset(LONG deviceId, BYTE programNo, BYTE outNo, LONG offset);
	CL3_IF_API LONG WINAPI CL3IF_SetTolerance(LONG deviceId, BYTE programNo, BYTE outNo, LONG upperLimit, LONG lowerLimit, LONG hysteresis);
	CL3_IF_API LONG WINAPI CL3IF_SetFilter(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_FILTERMODE filterMode, WORD filterParam);
	CL3_IF_API LONG WINAPI CL3IF_SetHold(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_HOLDMODE holdMode, CL3IF_HOLDMODE_PARAM param);
	CL3_IF_API LONG WINAPI CL3IF_SetInvalidDataProcessing(LONG deviceId, BYTE programNo, BYTE outNo, WORD invalidationNumber, WORD recoveryNumber);
	CL3_IF_API LONG WINAPI CL3IF_SetDisplayUnit(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_DISPLAYUNIT displayUnit);
	CL3_IF_API LONG WINAPI CL3IF_SetTerminalAllocation(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_TIMINGRESET timingReset, CL3IF_ZERO zero);
	CL3_IF_API LONG WINAPI CL3IF_SetAnalogOutputScaling(LONG deviceId, BYTE programNo, BYTE outNo, LONG inputValue1, LONG outputValue1, LONG inputValue2, LONG outputValue2);
	CL3_IF_API LONG WINAPI CL3IF_SetJudgmentOutput(LONG deviceId, BYTE programNo, CL3IF_JUDGMENT_OUTPUT* judgmentOutput);
	CL3_IF_API LONG WINAPI CL3IF_SetStorageNumber(LONG deviceId, BYTE programNo, BYTE overwrite, DWORD storageNumber);
	CL3_IF_API LONG WINAPI CL3IF_SetStorageTiming(LONG deviceId, BYTE programNo, BYTE storageTiming, CL3IF_STORAGETIMING_PARAM param);
	CL3_IF_API LONG WINAPI CL3IF_SetStorageTarget(LONG deviceId, BYTE programNo, CL3IF_OUTNO outNo);
	CL3_IF_API LONG WINAPI CL3IF_SetAnalogOutAllocation(LONG deviceId, BYTE programNo, BYTE ch1Out, BYTE ch2Out, BYTE ch3Out, BYTE ch4Out);

	CL3_IF_API LONG WINAPI CL3IF_GetSettings(LONG deviceId, BYTE* settings);
	CL3_IF_API LONG WINAPI CL3IF_GetProgram(LONG deviceId, BYTE programNo, BYTE* program);
	CL3_IF_API LONG WINAPI CL3IF_GetEncoder(LONG deviceId, CL3IF_ENCODER_SETTING* encoder);
	CL3_IF_API LONG WINAPI CL3IF_GetSamplingCycle(LONG deviceId, BYTE programNo, CL3IF_SAMPLINGCYCLE* samplingCycle);
	CL3_IF_API LONG WINAPI CL3IF_GetMutualInterferencePrevention(LONG deviceId, BYTE programNo, BOOL* onOff, WORD* group);
	CL3_IF_API LONG WINAPI CL3IF_GetAmbientLightFilter(LONG deviceId, BYTE programNo, BOOL* onOff);
	CL3_IF_API LONG WINAPI CL3IF_GetMedianFilter(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_MEDIANFILTER* medianFilter);
	CL3_IF_API LONG WINAPI CL3IF_GetThreshold(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_MODE* mode, BYTE* value);
	CL3_IF_API LONG WINAPI CL3IF_GetHighSensitivity(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_HIGH_SENSITIVITY* highSensitivity);
	CL3_IF_API LONG WINAPI CL3IF_GetMask(LONG deviceId, BYTE programNo, BYTE headNo, BOOL* onOff, LONG* position1, LONG* position2);
	CL3_IF_API LONG WINAPI CL3IF_GetLightIntensityControl(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_MODE* mode, BYTE* upperLimit, BYTE* lowerLimit);
	CL3_IF_API LONG WINAPI CL3IF_GetPeakShapeFilter(LONG deviceId, BYTE programNo, BYTE headNo, BOOL* onOff, CL3IF_INTENSITY* intensity);
	CL3_IF_API LONG WINAPI CL3IF_GetLightIntensityIntegration(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_INTEGRATION_NUMBER* integrationNumber);
	CL3_IF_API LONG WINAPI CL3IF_GetQuadProcessing(LONG deviceId, BYTE programNo, BYTE headNo, CL3IF_QUADPROCESSING* processing, BYTE* quadValidPoint);
	CL3_IF_API LONG WINAPI CL3IF_GetMeasurementPeaks(LONG deviceId, BYTE programNo, BYTE headNo, BYTE* peaks);
	CL3_IF_API LONG WINAPI CL3IF_GetCheckingNumberOfPeaks(LONG deviceId, BYTE programNo, BYTE headNo, BOOL* onOff);
	CL3_IF_API LONG WINAPI CL3IF_GetMultiLightIntensityControl(LONG deviceId, BYTE programNo, BYTE headNo, BOOL* onOff);
	CL3_IF_API LONG WINAPI CL3IF_GetRefractiveIndexCorrection(LONG deviceId, BYTE programNo, BYTE headNo, BOOL* onOff, CL3IF_MATERIAL* layer1, CL3IF_MATERIAL* layer2, CL3IF_MATERIAL* layer3);
	CL3_IF_API LONG WINAPI CL3IF_GetMeasurementMethod(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_MEASUREMENTMETHOD* method, CL3IF_MEASUREMENTMETHOD_PARAM* param);
	CL3_IF_API LONG WINAPI CL3IF_GetScaling(LONG deviceId, BYTE programNo, BYTE outNo, LONG* inputValue1, LONG* outputValue1, LONG* inputValue2, LONG* outputValue2);
	CL3_IF_API LONG WINAPI CL3IF_GetOffset(LONG deviceId, BYTE programNo, BYTE outNo, LONG* offset);
	CL3_IF_API LONG WINAPI CL3IF_GetTolerance(LONG deviceId, BYTE programNo, BYTE outNo, LONG* upperLimit, LONG* lowerLimit, LONG* hysteresis);
	CL3_IF_API LONG WINAPI CL3IF_GetFilter(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_FILTERMODE* filterMode, WORD* filterParam);
	CL3_IF_API LONG WINAPI CL3IF_GetHold(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_HOLDMODE* holdMode, CL3IF_HOLDMODE_PARAM* param);
	CL3_IF_API LONG WINAPI CL3IF_GetInvalidDataProcessing(LONG deviceId, BYTE programNo, BYTE outNo, WORD* invalidationNumber, WORD* recoveryNumber);
	CL3_IF_API LONG WINAPI CL3IF_GetDisplayUnit(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_DISPLAYUNIT* displayUnit);
	CL3_IF_API LONG WINAPI CL3IF_GetTerminalAllocation(LONG deviceId, BYTE programNo, BYTE outNo, CL3IF_TIMINGRESET* timingReset, CL3IF_ZERO* zero);
	CL3_IF_API LONG WINAPI CL3IF_GetAnalogOutputScaling(LONG deviceId, BYTE programNo, BYTE outNo, LONG* inputValue1, LONG* outputValue1, LONG* inputValue2, LONG* outputValue2);
	CL3_IF_API LONG WINAPI CL3IF_GetJudgmentOutput(LONG deviceId, BYTE programNo, CL3IF_JUDGMENT_OUTPUT* judgmentOutput);
	CL3_IF_API LONG WINAPI CL3IF_GetStorageNumber(LONG deviceId, BYTE programNo, BYTE* overwrite, DWORD* storageNumber);
	CL3_IF_API LONG WINAPI CL3IF_GetStorageTiming(LONG deviceId, BYTE programNo, BYTE* storageTiming, CL3IF_STORAGETIMING_PARAM* param);
	CL3_IF_API LONG WINAPI CL3IF_GetStorageTarget(LONG deviceId, BYTE programNo, CL3IF_OUTNO* outNo);
	CL3_IF_API LONG WINAPI CL3IF_GetAnalogOutAllocation(LONG deviceId, BYTE programNo, BYTE* ch1Out, BYTE* ch2Out, BYTE* ch3Out, BYTE* ch4Out);

	CL3_IF_API LONG WINAPI CL3IF_TransitToMeasurementMode(LONG deviceId);
	CL3_IF_API LONG WINAPI CL3IF_TransitToSettingMode(LONG deviceId);

}

#endif _CL3_IF_H_