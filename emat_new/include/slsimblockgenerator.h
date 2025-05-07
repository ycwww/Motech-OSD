///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimblockgenerator.h
 *  \author Norbert Olah, Walter Häring
 *  \date   01.03.2007
 *  \brief  Headerfile for class SlSimBlockGenerator
 *
 *  This file is part of the HMI SolutionLine Simulation.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_SIM_BLOCK_GENERATOR
#define SL_SIM_BLOCK_GENERATOR

///////////////////////////////////////////////////////////////////////////////

#include <QtCore/QObject>
#include "slsimiface.h"

///////////////////////////////////////////////////////////////////////////////
const double SLSIM_NCK_VERSION_SIM_BLOCK = 1338500.0; // nckversion with new $AC_SIM_TIME_BLOCK timing
///////////////////////////////////////////////////////////////////////////////
typedef QList<QByteArray> SlSimStringList; //!< Lists of Strings
typedef QMap<int, SlSimStringList> SlSimBlockStrings; //!< Map of Lists of Block Strings

///////////////////////////////////////////////////////////////////////////////
// SlSimBlockGenerator
///////////////////////////////////////////////////////////////////////////////
/*! \class SlSimBlockGenerator slsimblockgenerator.h
 *  \brief Protocol Buffer Variables
*/
class SlSimBlockGenerator : public QObject
{
    Q_OBJECT;
public:
    ///////////////////////////////////////////////////////////////////////////
    enum SimSupportEnum   //! Simulation Support
    {
      SL_SIMSUP_TRAFO             = 0x0001,  // Bit0: Trafo
      SL_SIMSUP_FRAME             = 0x0002,  // Bit1: Frame
      SL_SIMSUP_ACTION_BLOCK      = 0x0004,  // Bit2: Aktionssatz
      SL_SIMSUP_ACTION_BLOCK_LAST = 0x0008,  // Bit3: letzter Aktionssatz
      SL_SIMSUP_PTP_AKTIV         = 0x0010,  // Bit4: PTP-Satz
    };
    enum SimSupTaskEnum   //! Simulation Support Task
    {
      SL_SIMSUP_CHANGE_COORD = 1,     // Positionen ignorieren: Trafo/Frame
      SL_SIMSUP_MOVE_POSITION,        // auf Position moven: Frame
      SL_SIMSUP_IGNORE_ACTION,        // Satz ignorieren: Aktionssatz
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct HeadStructType slsimblockgenerator.h
     *  Structure for Event-Header
    */
    struct HeadStructType
    {
      quint32   eventCount;  //!< EventCounter
      quint32   eventProt;   //!< EventTypeCounter
      short int eventType;   //!< EventType
      short int eventChan;   //!< Channel
      double    eventTime;   //!< NCSC Systemzeit in Mikrosekunden
      double    eventProgTime; //!< actual progruntime
      double    eventTimeStep;  //!< actual timestep
    };
    /*! \struct VarStructType slsimblockgenerator.h
     *  Structure for all Variables
    */
    struct VarStructType
    {
      short int  ipotype;    //!< Ipo Type
      short int getIpoType() const;
      SlSimNewMotionType newMotionType; //!< EV_NEW_MOT_LIN etc.
      GeoposType pos;        //!< Geometry Axis
      CircleType cir;        //!< Circle Data
      MachaxType max;        //!< Machine Axis
      MachaxType dist;       //!< Machine Axis Distance
      MaxparType dir;        //!< Moving Direction
      FrameType  frame;      //!< Frame Data
      SpinType   spindle;    //!< Spindle Data
      TrafoType  trafo;      //!< Trafo Data
      ToolType   tool;       //!< Tool Data
      GCodeType  gcode;      //!< G-Groups
      MfuncType  mfunc;      //!< M/H-Functions
      DeclarType declar;     //!< Object Declaration
      StateType  state;      //!< NC State
      AxconfType axconf;     //!< Axes Configuration
      FeedType   feed;       //!< Feed Rate/Unit
      WaitType   wait;       //!< Waiting Channel
      TimeType   time;       //!< Program Time
      WaitCondType waitCond; //!< wait condition
      PathType   path;       //!< Path Parameter
      ChainType  kinchain;   //!< Kinematic Chain
      double     thread;     //!< Threat
      short int  simsup;     //!< Simulation Support
      qint32     snr;        //!< Line Number
       qint32 ipoCounter;

      ChanaxParData cdir;
      ChanaxPosData edgePosEns;
      ChanaxPosData basePosMcs;      //actToolBasePosMcs
      ChanaxPosData aaVactM;
      ChanaxPosData edgePosBcs;      //actToolEdgeCenterPosBcs
      ChanaxPosData basePosEns;      //actToolBasPosEN
      ChanaxPosData pathn1PosEns;    //actToolEdgeCenterPosEnsPathn1
      ChanaxPosData pathn1PosMcs;    //cmdToolEdgeCenterPosMcsPathn1

       //axes_bitfield<chanax_idx> axesAtEnd;
    };
    /*! \struct EventStructType slsimblockgenerator.h
     *  Structure for Event Data
    */
    struct EventStructType
    {
      bool               m_BlockBeg;     //!< New BlockBeg
      bool               m_newBlockBeg;  //!< New Event
      bool               m_newBlockDraw; //!< New BlockBeg Draw
      bool               m_tempEvent;    //!< Ipo Event Arrived
      bool               m_circleChange; //!< Circle Data Changed
    //bool               m_circleMirror; //!< Mirror CYCFRAME
      bool               m_collAlarm;    //!< Collision Alarm
      unsigned short int m_noIpo;        //!< No Ipo Events (2->1->0)
      unsigned short int m_whatsnew;     //!< New Data
      axes_bitfield<chanax_idx> m_newdata;
      unsigned short int m_axisnew;      //!< Axis new in Channel
      axes_bitfield<chanax_idx> m_newaxes;
      unsigned short int m_oldsrk;       //!< Old SRK-State
      FeedType           m_oldfeed;      //!< Old Feed Data
      double             m_ry_tracyl;    //!< Real Y-Offset Tracyl
      bool               m_gewBeg;       //!< Threat Begin
      double             m_thread;       //!< Threat
      bool               m_tmpHelix;     //!< Helix bei Halbschnitt langsam
      bool               m_oldTime;      //!< Ende Spline -> alte Zeit nehmen
      bool               m_swivelEnd;    //!< Ende Schwenken CYCLE800
    };
    /*! \struct GroupType slsimblockgenerator.h
     *  Structure for group Data
    */
    struct GroupType
    {
      long               spindle;          //!< spindle number
      long               level;            //!< level
      long               cmdType;          //!< cmd type
      char namestr[SL_SIM_BTSS_BLOCKSTR];  //!< group name
    };
    /*! \struct ChanVarStructType slsimblockgenerator.h
     *  Structure for all Channel Variables
    */
    struct ChanVarStructType
    {
      VarStructType      m_var;        //!< Variables new
      VarStructType      m_old;        //!< Variables old
    //GeoposType         m_start;      //!< Startpoint Circle
      GeoposType         m_actpos;     //!< Aktuelle Position fuer Anzeige
      MachaxType         m_actmax;     //!< Aktuelle Position fuer Anzeige
    //FrameType          m_partframe;  //!< Partframe (kinematische Trafo)
    //FrameType          m_nullebene;  //!< Nullebene
      ManAxType          m_manax;      //!< Manual Axis
      FocusType          m_focus;      //!< Focus on Main-/Subspindle
      BlankType          m_blank;      //!< Blank Definition
      JawDefType         m_jawdef;     //!< Chuck Definition
      ChuckType          m_chuck;      //!< Chuck Open/Close
      PinoleType         m_pinole;     //!< Tailstock On/Off
      EventStructType    m_eventdata;  //!< Event Data
      GroupType          m_group;      //!< Group Data
      CollType           m_collision;  //!< Collision Data
      unsigned short int m_blockoffset;//!< Block Offset
      bool               m_swivel;     //!< Signal from Cycle800
      bool               m_no_toolpath; //!< Flag for ignoring movements for automated testing, hides toolpath
    //bool               m_noeros;     //!< Kein Abtrag nach Schwenken
      char m_wrtpr_str[SL_SIM_BTSS_WRTPRSTR]; //!< WRTPR-String
      char m_block_str[SL_SIM_BTSS_BLOCKSTR]; //!< NC-Block-String
      char m_block_old[SL_SIM_BTSS_BLOCKSTR]; //!< NC-Block-String
      char m_progr_str[SL_SIM_BTSS_BLOCKSTR]; //!< NC-Program-Name: P_C_SPARP_workPandProgName
      char m_progr_old[SL_SIM_BTSS_BLOCKSTR]; //!< NC-Program-Name: P_C_SPARP_workPandProgName
      char m_msg_str[SL_SIM_BTSS_MSG_STR]; //!< MSG-String
      char m_imach_str[SL_SIM_BTSS_BLOCKSTR]; //!< i-Machining File-String
      SlSimIfaceBlockList m_TempBlock;    //!< list of temp blocks
      SlSimIfaceBlockList m_chanBuffer;   //!< list of channel depending blocks, used in simulation
    };

    ///////////////////////////////////////////////////////////////////////////
    typedef SlSimPseudoMap<ChanVarStructType, SL_SIM_MAXNUM_CHANNELS+1> ChanVarMapType;
    // Die ChanMapType beinhaltet zehn Channels. Damit aber die
    // Kanalnummer 1..10 zum direkten Zugriff verwendet werden kann und
    // wir nicht immer minus eins zu rechnen haben, geben wir noch
    // einen hinzu.
    static ChanVarStructType s_templateChanVarStructType;
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct TimeCompareType slsimblockgenerator.h
     *  Structure for sort and compare time
    */
    struct TimeCompareType
    {
        double time;
        long   chan;
    };
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlSimBlockGenerator();
     *
     *  Constructor
    */
    SlSimBlockGenerator();

    /*! \fn virtual ~SlSimBlockGenerator();
     *
     *  Destructor
    */
    virtual ~SlSimBlockGenerator();

signals:
    void kinematicChanged(int counter);

public:

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    void setError(short int channel, const long error); //!< Set Error State
    void setConfigPtr(SlSimConfig* pConfig); //!< Store Pointer
    void setBlockPtr(SlSimIface* pBlock); //!< Store Pointer
    void resetAll(void); //!< Reset All
    void resetVariables(void); //!< Reset Variables
    void initChanIterator(void); //!< Init Channel Map, Reset M/H-Functions
    bool checkBlock(short int channel, bool initEvent = false, bool tempEvent = false, bool doitEvent = false); //!< Check Block
	bool checkBlockMCS(short int channel, bool initEvent = false, bool tempEvent = false, bool doitEvent = false); //!< Check Block for MCS
    long GetBufferSize(); //!< Get Buffer Size
    long GetChanBufferSize(long channel = 0); //!< Get Buffer Size
    long getNextBlockNo(long channel); //!< Get next Block Number
    void clearBuffer(void); //!< Clear Buffer
    long readBlock(IfaceType& block); //!< Read Block from Iface Buffer
    long readBlock(IfaceType& block, ChannelArrivalTimeStructList& arrivalTimeList, long& blockfound); //!< Read Block from Iface Buffer
    long readFilteredBuffer(IfaceStructType& block, ChannelArrivalTimeStructList& arrivalTimeList, long& blockfound); //!< Read Block from Buffer
    bool peekBlock(unsigned short int channel, IfaceStructType& block) const;
    void checkSchnecke(unsigned short int channel, IfaceType& block);
    void checkSpiral(unsigned short int channel, IfaceType& block);
    void checkEllipse(unsigned short int channel, IfaceType& block);
    void checkTraint(unsigned short int channel, IfaceType& block);
    double convert_ry(const AxPosStructType& axis, int channel) const;
    long buildBlock(const BlockTypeEnum TYPE); //!< Build Block
    void buildHeader(HeaderStructType& head, int channel, const BlockTypeEnum TYPE) const;
    void buildTrafoBlock(TrafoStructType& btrafo, EventStructType& m_eventdata, int channel);
    void buildFrameBlock(FrameStructType& frame_block, int channel) const;
    void buildWaitCondBlock(WaitCondStructType& waitCondBlock, const WaitCondStructType& waitCond) const;
    int buildPinoleBlock(PinoleStructType& pinole_block, PinoleStructType& pinole, int channel) const;
    int buildAxposBlock(IfaceType& block, int channel);
    int buildAxposBlockMCS(IfaceType& block, int channel);
    int buildSpindleBlock(SpinStructType& spindle, int channel) const;
    long writeBlockToBuffer(IfaceType& block, long channel); //!< write block to buffer
    long moveTempBuffer(const long channel, const double maintime , const double auxtime); //!< move temp --> buffer 
  //long moveTempBufferLine(const long channel); // Wait: move BLOCK_LINE --> buffer
    long writeblock(IfaceType& block, long channel); //!<  write channel-specific block

    void checkGeoaxChange(short int channel, const GeoposType& pos_in, GeoposType& pos_out) const; //!< Check Geoax Change
    void checkGeoaxChange(short int channel, const MachaxType& max_in, GeoposType& pos_out) const; //!< Check Geoax Change with Machine Axes
    void setBlockAxis(short int channel, AxPosType& axis); //!< Set Block Axis
	void setBlockAxisMCS(short int channel, AxPosType& axis); //!< Set Block Axis for MCS
    void checkSlotSideOffset(const long channel, AxPosStructType& axis) const;  //!< Check Slot Side Offset
    void checkSlotSideOffset(const long channel, IfaceStructType& block) const;  //!< Check Slot Side Offset
    double calcCircleRadius(const CircleType& circle, const GeoposType& epos) const; //!< Calculate Circle Radius
    double calcCircleAngle(const CircleType& circle, const GeoposType& epos, const GeoposType& apos) const; //!< Calculate Circle Angle
    bool checkPos(short int channel, bool initEvent, bool circle); //!< Check Positions
    bool checkPosMCS(short int channel, bool initEvent); //!< Check Positions
    bool checkPos(short int channel); //!< Check Positions after CYCLE800
    void checkMfunc(short int channel); //!< Check M/H-Functions
    void checkChuck(short int channel, short int mfunction, short int madress); //!< Check Chuck open/close
    void checkDiam(short int channel, GeoposType& pos) const; //!< Check Diamon/Diamoff
    void checkDiam(short int channel, ChanaxPosData& pos, const SimArray<chanax_idx, 3>& geoconf) const;
    bool checkSupa(short int channel) const; //!< Check SUPA
    bool checkValid(short int simsup) const; //!< Check Position valid
    bool checkSimsup(short int task, short int simsup) const; //!< Check Simulation Support
    void checkModulo(double& angle) const;  //!< Check Modulo Range
    void checkWrtpr(short int channel); //!< Check WRTPR
    void checkObjDecl(short int channel); //!< Check Object Declaration
    void checkBlockStr(short int channel); //!< Check Block String
    void checkMsgStr(short int channel); //!< Check msg String
    void checkSrk(short int channel, GeoposType& pos) const; //!< Check SRK
    void checkTrafoGeoAx(short int channel, GeoposType& pos) const; //!< Check Trafo for GeoAx Assign
    void checkTrafoRotAx(short int channel, GeoposType& pos, const MachaxType& machax) const; //!< Check Trafo for Position
    void checkTrafoFrame(short int channel, FrameType& frame) const; //!< Check Trafo for Frame
    bool isComplexMotion(short int ipotype) const; //!< Check Splines und Polynoms
    bool isCompressor(short int comp) const; //!< Check Compressor
    bool isInch(short int metric) const; //!< Check INCH/METRIC
    void switchScaleToMetric(double& value) const; //!< Switch Scale To Metric
    void switchScaleToMetric(GeoposType& value) const; //!< Switch Scale To Metric
    void switchSysVarMetric(double& value) const; //!< Switch System Variable To Metric
    void switchInchMetric(double& value) const; //!< Switch INCH/METRIC
    void switchInchMetric(GeoposType& value) const; //!< Switch INCH/METRIC
    void switchInchMetric(CircleType& value) const; //!< Switch INCH/METRIC
    void switchInchMetric(MachaxType& value) const; //!< Switch INCH/METRIC
    void switchInchMetric(BlankType& blank) const; //!< Switch INCH/METRIC
    void switchInchMetric(JawDefType& jawdef) const; //!< Switch INCH/METRIC
    void switchInchGeoax(const long channel, GeoposType& actpos) const; //!< Switch INCH for Geoaxes
    void switchInchMachax(const long channel, MachaxType& actmax) const; //!< Switch INCH for Machaxes
    void fillGeoAxes(int channel, GeoposStructType& pos, const MachaxStructType& machax) const; //Uses the current geoAxisInChan to fill the geoaxes with values from the machine axes
    void fillGeoAxes(int channel, GeoposStructType& pos, const MachaxStructType& machax, const AxconfType& axconf) const;
    void fillGeoAxes(int channel, GeoposStructType& pos, const ChanaxPosData& machax) const;

    ///////////////////////////////////////////////////////////////////////////
    /// The file name (incl. path) to the SL_SIM_EVENT_VNCK_LOG / SL_SIM_EVENT_MONI_LOG file.
    QString getEventLogFileName() const;
    void traceSetName(void); //!< Set Trace File Name
    void traceDelete(void) const; //!< Delete Trace File
    void traceEvent(short int channel, short int eventType, bool init=false, bool force = false); //!< Trace Event VNCK
    QString createTraceEventString() const;
    void traceEvent(); //!< Trace Event
    void appendTraceEventLine(const QString LINE);  //!< Trace Event
    void appendTraceEventLine(const QString FILE_PATH, QString line); //!< Trace Event
    QString getAndClearTraceLine();
    QString traceGeoEns(short int channel) const; //!< Trace Geopos ENS
    QString traceGeopos(short int channel) const; //!< Trace Geopos Data
    QString traceCircle(short int channel) const; //!< Trace Circle Data
    QString traceMachax(short int channel) const; //!< Trace Machax Data
    QString traceSpindle(short int channel) const; //!< Trace Spindle Data
    QString traceSpindir(short int channel) const; //!< Trace Spindle Direction
  //QString traceTraFrame(short int channel) const;  //!< Trace TrafFrame Data
    QString traceFrame(short int channel) const;  //!< Trace Frame Data
    QString traceFrameRotax(short int channel) const; //!< Trace Frame Data Rotax
    QString traceNewMotion(int channel) const;
    QString traceTrafo(short int channel) const;  //!< Trace Trafo Data
    QString traceTool(short int channel) const;   //!< Trace Tool Data
    QString traceGgroup(short int channel) const; //!< Trace G-Groups
    QString traceMfunc(short int channel) const;  //!< Trace M/H-Functions
    QString traceDeclar(short int channel) const; //!< Trace Object Declararion
    QString traceState(short int channel) const;  //!< Trace NC State
    QString traceAxisActive(short int channel) const; //!< Trace Axis Active In Channel
    QString traceProgTime(short int channel) const; //!< Trace Prog Time In Channel
    QString tracePath(short int channel) const; //!< Trace Path Parameter In Channel
    QString traceCollision(short int channel) const; //!< Trace Collision Data

    static short int checkMovDir(short int dir);
    static void switchBCS2WCS(MachaxType& value, const FrameType& frame); //!< Switch BCS->WCS
    static QString event2Str(short int eventType); //!< Convert Event to String

    ///////////////////////////////////////////////////////////////////////////
    // Member functions
    ///////////////////////////////////////////////////////////////////////////
    void set_header(short int eventChan, short int eventType, double eventTime, quint32 eventCount, quint32 eventProt); //!< Header VNCK
    /// @brief Returns true if a machine coordinate system mode is switched on
    bool isMCS() const;
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // Member variables
    ///////////////////////////////////////////////////////////////////////////
    HeadStructType    m_head;          //!< Event Header
    mutable ChanVarMapType    m_chan;  //!< Channel Variables
    QString           m_EVENT_LOG;     //!< Logfile Events
    QString           m_traceline;     //!< actual Traceline
    unsigned short int m_initevent;    //!< Init Event
    unsigned short int m_ipomode;      //!< Ipomode for Axis Movements
    unsigned short int m_whatsnew;     //!< Whatsnew for Axis Movements
    axes_bitfield<chanax_idx> m_newaxvalues;
    quint32           m_blockno;       //!< Block Counter
    bool              m_vnck;          //!< Source is VNCK
    SlSimInit<PerformantEventsMode> m_performantEventsMode;
    SlSimConfig*      m_pConfig;       //!< Pointer to Configuration
    SlSimIface*       m_pBlock;        //!< Pointer to Block
    SlSimBlockStrings m_blockStrings;  //!< Lists Block Strings
    QMap<int, QList<int> > m_lineNumbers; //!< channel --> last line numbers
    ///////////////////////////////////////////////////////////////////////////

    inline int currentChannel() const { return m_head.eventChan; }

    axes_bitfield<chanax_idx> createChanAxIdxBitfield(int channel, ChanAxIterator::ChanAxIteratorOptions options = ChanAxIterator::DefaultOptions, ChanAxIterator::ChanAxGroupOptions group_options = ChanAxIterator::All) const; // from var()
    axes_bitfield<chanax_idx> createOldChanAxIdxBitfield(int channel, ChanAxIterator::ChanAxIteratorOptions options = ChanAxIterator::DefaultOptions, ChanAxIterator::ChanAxGroupOptions group_options = ChanAxIterator::All) const; // from old()

    template<typename T, int N>
    AxKey compare_chanax_containers(const AxesValues<T, chanax_idx, N>& lhs, const AxesValues<T, chanax_idx, N>& rhs, int channel, ChanAxIterator::ChanAxIteratorOptions options = ChanAxIterator::DefaultOptions, ChanAxIterator::ChanAxGroupOptions group_options = ChanAxIterator::All);

    inline VarStructType& var() { return var(currentChannel()); }
    inline const VarStructType& var() const { return var(currentChannel()); }
    inline VarStructType& var(int channel) { return complete_var(channel).m_var; }
    inline const VarStructType& var(int channel) const { return complete_var(channel).m_var; }    
    
    ChanVarStructType& complete_var() { return complete_var(currentChannel()); }
    const ChanVarStructType& complete_var() const { return complete_var(currentChannel()); }
    ChanVarStructType& complete_var(int channel) { return m_chan[channel]; }
    const ChanVarStructType& complete_var(int channel) const { return m_chan[channel]; }

    inline VarStructType& old() { return old(currentChannel()); }
    inline const VarStructType& old() const { return old(currentChannel()); }
    inline VarStructType& old(int channel) { return complete_var(channel).m_old; }
    inline const VarStructType& old(int channel) const { return complete_var(channel).m_old; }
private:
    ///////////////////////////////////////////////////////////////////////////
    mutable QMutex m_mutexReadWriteBuffer;  //!< Semaphore for buffer reading and writing
    mutable QMutex m_mutexTempBuffer;       //!< Semaphore for reading/writing temporary buffer
    ///////////////////////////////////////////////////////////////////////////
};  // class SlSimBlockGenerator
///////////////////////////////////////////////////////////////////////////////

QString createBlockBegString(const SlSimBlockGenerator::ChanVarStructType& m_var, short int channel);
QString createLineAndTimeString(const SlSimBlockGenerator::ChanVarStructType& m_var, short int channel);

#endif // SL_SIM_BLOCK_GENERATOR
///////////////////////////////////////////////////////////////////////////////
