#if !defined(SL_PAINT_DATA_INCLUDE)
#define SL_PAINT_DATA_INCLUDE


const int MAX_LEN_FILENAME = 255;

typedef enum
   {
      STRAIGHT = 1,         /* Gerade */
      CIRCLE,               /* Kreis */
      POINT_LG,               /* Punkt*/
      HEADER,               /* Kennung fuer Einstellungsheader */
      ARROW,               /* Definition eines Pfeiles */
      FILES,               /* Kennung eines Files */
      AXIS_NAME,            /* Achsnamen */
      FRAME,               /* Frame: Translation */
      LAST_ID               /* letzte Kennung */
   } SectionEnum;
//   Q_DECLARE_METATYPE(SectionEnum);

typedef enum
   {
      STRAIGHT_FINITE = 0,    /* Gerade */
      STRAIGHT_INFINITE,      /* unendliche Gerade */
      STRAIGHT_MID_ARROW,     /* Gerade mit Pfeil in der Mitte */
      STRAIGHT_END_ARROW,     /* Gerade mit Pfeil am Ende      */
   } StraightEnum;
//   Q_DECLARE_METATYPE(StraightEnum);

typedef enum
   {
      CIRCLE_FINITE = 0,      /* Kreis */
      CIRCLE_MID_ARROW,      /* Kreis  mit Pfeil in der Mitte */
      CIRCLE_END_ARROW,      /* Kreis  mit Pfeil am Ende      */
   } CircleEnum;
//   Q_DECLARE_METATYPE(CircleEnum);

typedef enum
   {
      FRAME_TRANS = 0,      /* Translation */
      FRAME_ROT,            /* Rotation */
      FRAME_SCALE,         /* Scale */
      FRAME_MIRROR,         /* Mirror */
   } FrameEnum;
//   Q_DECLARE_METATYPE(FrameEnum);

typedef enum
   {
      PS_SOLID_LG = 0,           /*durchgezogene Linie*/
      PS_DASH_LG,            /*-----------------------------*/
      PS_DOT_LG,               /*..................*/
      PS_DASHDOT_LG,            /*-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.*/
      PS_DASHDOTDOT_LG,         /*-..-..-..-..-..-..-..-..-..-..-..-..-..-..-*/
      PS_NULL_LG,            /*                                           */   /* Linie wird nicht gezeichnet*/
      PS_INSIDEFRAME_LG         /* wie PS_SOLID allerdings mit Ausrichtung zum Randinneren bei z.B. Rechtecken*/
   } LineEnum;
//   Q_DECLARE_METATYPE(LineEnum);

typedef enum
   {
      PIXEL=0,            /* ein Pixel wird dargestellt*/
      PLUS,               /* ein gerades Kreuz wird dargestellt*/
      CROSS,               /* ein schräges Kreuz wird dargestellt*/
      SQUARE_EMPTY,         /* ein leeres Quadrat wird dargestellt */
      SQUARE_FILLED,         /* ein gefülltes Quadrat wird dargestellt*/
      RHOMBUS_EMPTY,         /* eine leere Route wird dargestellt*/
      RHOMBUS_FILLED,         /* eine gefüllte Route wird dargestellt*/
      CIRCLE_EMPTY,         /* ein leerer Kreis wird dargestellt */
      CIRCLE_FILLED,         /* ein gefüllter Kreis wird dargestellt*/
      INVISIBLE,            /*unsichtbarere Punkt z.B. für Zoom bei Startpunktangabe */
      POLE,               /*Poldarstellung*/
      CIRCLE_RADIUS,         /*Darstellung Kreis mit Radius*/
      CROSS_DOTTED         /*Ein schräges Kreuz mit unterbrochener Linie wird dargestellt*/
   } PointEnum;
//   Q_DECLARE_METATYPE(PointEnum);

typedef enum
   {
      NO_ZOOM_ELEMENT=0,
      ZOOM_ELEMENT,
      ZOOM_ACTIVE
   } ZoomEnum;
//   Q_DECLARE_METATYPE(ZoomEnum);

typedef enum
   {
      FOREGROUND=0,
      BACKGROUND,
      LEGEND,
      MARK,
      NORMAL,
      FOCUS,
      DIALOG,
      AXIS,
      ZEROLINE,
      COORDINATE,
      COAT
   } ColorEnum;
//   Q_DECLARE_METATYPE(ColorEnum);
 
typedef enum
   {
      G02=1,                /*im Uhrzeigersinn*/
      G03        /*gegen den Uhrzeigersinn*/
   } DirectionEnum;
//   Q_DECLARE_METATYPE(DirectionEnum);

typedef struct
   {
      double dX;
      double dY;
      double dZ;
   } VectorType;
//   Q_DECLARE_METATYPE(VectorType);

typedef struct
   { /* Speichertyp Punkt */
      PointEnum type;               /* P_KENNUNG*/
      ZoomEnum zoom;
      ColorEnum color;               /* Farbe */
      VectorType tPos;               /* Position in Maßeinheit */
   } PointType;
//  Q_DECLARE_METATYPE(PointType);

typedef struct
   { /* Speichertyp Gerade */
      StraightEnum kind;               /* Kennung der Gerade */
      ZoomEnum zoom;
      LineEnum type;                  /* Art der Linie durchgezogen = 0xffff*/
      ColorEnum color;               /* Farbe*/
      VectorType start;               /* Anfangs-Position in Maßeinheit */
      VectorType end;               /* End-Position in Maßeinheit */
   } StraightType;
//   Q_DECLARE_METATYPE(StraightType);



typedef struct
   { /* Speichertyp Kreis */
      CircleEnum kind;               /* Kennung des Kreises */
      ZoomEnum zoom;                  /* NO_ZOOM_ELEMENT, ZOOM_ELEMENT*/
      DirectionEnum direction;         /* Kreisrichtung */
      LineEnum type;                  /* Linienart 0xffff = durchgezogene Linie */
      ColorEnum color;               /* Farbe */
      VectorType start;               /* Anfangspunkt in Maßeinheit */
      VectorType end;               /* Endpunkt in Maßeinheit */
      VectorType mid;               /* Mittelpunkt in Maßeinheit */
      //double dRad;               /* Radius in Maßeinheit */
      bool bClosed;               /* true für Vollkreis */
   } CircleType;
//   Q_DECLARE_METATYPE(CircleType);

typedef struct
   {
      ZoomEnum zoom; /*NO_ZOOM_ELEMENT, ZOOM_ELEMENT*/
      LineEnum type; /* gibt den linestyle an für alle Elemente der Datei */
      ColorEnum color; /* gibt die Farbe an für alle Element der Datei */
      char cFileName[64];//[MAX_LEN_FILENAME]; /* Dateiname - RAMDISK-Pfad, absolute oder relative Angabe. Wird durch Punkt (./../.. )unterschieden */
   } FileType;
//   Q_DECLARE_METATYPE(FileType);

typedef struct
   {
      char name[3][10];      // Achsname Abszisse  
      int nTransverseAxis;   // Nummer der Planachse oder -1, falls keine Planachse vorhanden
   } AxesType;
//   Q_DECLARE_METATYPE(AxesType);

typedef union
   {
      PointType point;
      StraightType straight;
      CircleType circle;
      FileType file;
      AxesType axes;
   } UnionDataType;
//   Q_DECLARE_METATYPE(UnionDataType);

typedef struct
   {
      SectionEnum section;
      UnionDataType uData;
   } DataType;
//   Q_DECLARE_METATYPE(DataType);

typedef struct
   {
      VectorType start;               /* Anfangs-Position in Maßeinheit */
      VectorType end;               /* End-Position in Maßeinheit */

   }ZoomAreaType;
//   Q_DECLARE_METATYPE(ZoomAreaType);

#endif // !defined(SL_PAINT_DATA_INCLUDE)
