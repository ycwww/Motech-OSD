#include "paramDefine.h"

void init_device_param(DEVICE_ULTRA_PARAM_U& deviceParam)
{
	deviceParam.stParam.gate2End.index = 0;
	deviceParam.stParam.gate2End.value = 300;

	deviceParam.stParam.zeroPointEnvelope.index = 1;
	deviceParam.stParam.zeroPointEnvelope.value = 2470;

	deviceParam.stParam.ultraSpeed.index = 2;
	deviceParam.stParam.ultraSpeed.value = 32500;

	deviceParam.stParam.zeroPointOrigin.index = 3;
	deviceParam.stParam.zeroPointOrigin.value = 2470;

	deviceParam.stParam.gate2Start.index = 4;
	deviceParam.stParam.gate2Start.value = 200;

	deviceParam.stParam.gate1Start.index = 5;
	deviceParam.stParam.gate1Start.value = 100;

	deviceParam.stParam.gate1End.index = 6;
	deviceParam.stParam.gate1End.value = 180;

	deviceParam.stParam.calibrationThick.index = 7;
	deviceParam.stParam.calibrationThick.value = 1200;

	deviceParam.stParam.temperature.index = 8;
	deviceParam.stParam.temperature.value = 25;

	deviceParam.stParam.curveSmooth.index = 9;
	deviceParam.stParam.curveSmooth.value = USING_CURVE_SMOOTH;

	deviceParam.stParam.smoothTime.index = 10;
	deviceParam.stParam.smoothTime.value = 4;

	deviceParam.stParam.sensorGain.index = 11;
	deviceParam.stParam.sensorGain.value = 300;

	deviceParam.stParam.ferqSelect.index = 12;
	deviceParam.stParam.ferqSelect.value = LOW_FREQUENCY;

	deviceParam.stParam.waveType.index = 13;
	deviceParam.stParam.waveType.value = ORIGIN_WAVE;

	deviceParam.stParam.measureMode.index = 14;
	deviceParam.stParam.measureMode.value = MEASURE_AUTO;

	deviceParam.stParam.SNR.index = 15;
	deviceParam.stParam.SNR.value = 10;

	deviceParam.stParam.dampingRadio.index = 16;
	deviceParam.stParam.dampingRadio.value = 10;

	deviceParam.stParam.envelopeWidth.index = 17;
	deviceParam.stParam.envelopeWidth.value = 2470;

	deviceParam.stParam.widthHeightRadio.index = 18;
	deviceParam.stParam.widthHeightRadio.value = 10;

	deviceParam.stParam.thresholdValue.index = 19;
	deviceParam.stParam.thresholdValue.value = 10;

	deviceParam.stParam.emitInterval.index = 20;
	deviceParam.stParam.emitInterval.value = 1000;

	deviceParam.stParam.pulseNumber.index = 21;
	deviceParam.stParam.pulseNumber.value = 2;

	deviceParam.stParam.excitationFrequency.index = 22;
	deviceParam.stParam.excitationFrequency.value = 500;

	deviceParam.stParam.startDisplay.index = 23;
	deviceParam.stParam.startDisplay.value = 2;

	deviceParam.stParam.stopDisplay.index = 24;
	deviceParam.stParam.stopDisplay.value = 30;

	deviceParam.stParam.communicateMode.index = 25;
	deviceParam.stParam.communicateMode.value = 0;

	deviceParam.stParam.measureControlMode.index = 26;
	deviceParam.stParam.measureControlMode.value = PP_CONTROL_MODE;

	deviceParam.stParam.manualMeasureMode.index = 27;
	deviceParam.stParam.manualMeasureMode.value = MANUAL_PP_CONTROL_MODE;

	deviceParam.stParam.lcdDisplayTxt.index = 28;
	deviceParam.stParam.lcdDisplayTxt.value = DISPLAY_THICKNESS;

	deviceParam.stParam.selfMultiplying.index = 29;
	deviceParam.stParam.selfMultiplying.value = SELF_MULTIPLYING;

	deviceParam.stParam.lcdDisplayTxt.index = 30;
	deviceParam.stParam.thicknessSmooth.value = 30;

	deviceParam.stParam.lcdDisplayTxt.index = 31;
	deviceParam.stParam.thicknessSmooth.value = TITANIUM_ALLOY;
}