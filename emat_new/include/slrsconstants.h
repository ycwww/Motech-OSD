#pragma once

namespace RS_TCU_INFO
{
  // mandatory info
  const QString DISPLAY_RESOLUTION_KEY = "DisplayResolution";
  const QString HMI_RESOLUTION_KEY = "HmiResolution";
  const QString HMI_ORIGIN_KEY = "HmiOrigin";

  // optional info
  const QString TCU_NAME = "TCUName";
  const QString IP_ADDRESS = "IPAddress";
  const QString DISPLAY_DIAGONAL_INCH_KEY = "DisplayDiagonalInch";
  const QString DISPLAY_WIDTH_MM_KEY = "DisplayWidthMM";
  const QString DISPLAY_HEIGHT_MM_KEY = "DisplayHeightMM";
  const QString DPI_KEY = "DPI";
  const QString MAX_TOUCH_POINTS_KEY = "MaxTouchPoints";
  const QString HAS_ALPHA_KEYBOARD_KEY = "HasAlphaKeyboard";
  const QString HAS_NUMERIC_KEYBOARD_KEY = "HasNumericKeyboard";
  const QString HAS_NAVIGATION_KEYS_KEY = "HasNavigationKeys";
  const QString NUM_HORIZONTAL_SKS_KEY = "NumHorizontalSKs";
  const QString NUM_VERTICAL_SKS_KEY = "NumVerticalSKs";
  const QString VIRTUAL_KEYBOARD_KEY = "virtualKeyboard"; // data from TCU config.ini (Auto = -1, Never = 0, Always = 1)
  const QString SW_CAPS_LOCK_KEY = "swCapsLock"; // data from TCU config.ini (Auto = -1, Never = 0, Always = 1)
  const QString TOUCH_LOOK_KEY = "touchLook"; // Auto = -1, NormalUI = 0, MultiTouchUI = 1
  const QString IS_SINUMERIK_PANEL = "isSinumerikPanel";

  // derived info
  const QString USE_MULTITOUCH_UI_KEY = "useMultitouchUI"; // true or false, this is the global "Smart Operation" or MultiTouch UI Look & Feel switch, includes every setting and condition
  const QString DISPLAY_DIAGONAL_MM_KEY = "DisplayDiagonalMM";
  const QString MIN_TOUCHABLE_PIXEL_HEIGHT_KEY = "MinTouchablePixelHeight";
  const QString MIN_TOUCHABLE_PIXEL_WIDTH_KEY = "MinTouchablePixelWidth";
  const QString MIN_VERTICAL_PIXEL_SPACING_KEY = "MinVerticalPixelSpacing";
  const QString MIN_HORIZONTAL_PIXEL_SPACING_KEY = "MinHorizontalPixelSpacing";
  const QString VIRTUAL_KEYBOARD_KEY_PIXEL_HEIGHT_KEY = "VirtualKeyboardKeyPixelHeight";
  const QString PIXELS_PER_MM_KEY = "PixelsPerMM";
  const QString DISPLAY_PANEL_LAYOUT = "DisplayPanelLayout";

  enum SlRsTcuInfoFlags
  {
    KeepPreviousValues          = 0x00000001,
    ForceResolutionChangeSignal = 0x00000002
  };
}


