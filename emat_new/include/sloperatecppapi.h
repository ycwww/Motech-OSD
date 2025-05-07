//////////////////////////////////////////////////////
//            SlOperateCppApi (C++ API)             //
//  library for accessing SINUMERIK solution line   //
//////////////////////////////////////////////////////
//	declaration of                                  //
//	public                                          //
//      enums,                                      //
//      defines,                                    //
//      classes and their methods                   //
//  in library:     sloperatecppapi.dll             //
//                  sloperatecppapi.so              //
//////////////////////////////////////////////////////
//  library for accessing SINUMERIK solution line   //
//////////////////////////////////////////////////////

#pragma once
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "wchar.h"

#ifdef _WINDOWS
// windows section
# ifdef SL_OPERATE_CPP_API_EXPORTS
#   define SL_OPERATE_CPP_API __declspec(dllexport)
# else
#   define SL_OPERATE_CPP_API __declspec(dllimport)
# endif

#else
// non windows section
#   define SL_OPERATE_CPP_API
#endif

#ifdef _WINDOWS
// to get rid of client alignment topics
#undef time_t
// we force the client to use 64bit time value
typedef __time64_t time_t;      /* time value */
#else
// no need to force the client to use 64bit time value
#endif

	const long SL_SVC_BUSY = -1;
	const long SL_SVC_NO_OA_OPTION = -2;
	const long SL_SVC_NOT_SUPPORTED = -3;

    enum SlPriorityFlags
    {
	    lowPriority     = 0x00010000, //x valid for read and write, advise calls, cyclic reading done one priority level lower
	    defaultPriority = 0x00000000, //x xxvalid for read and write calls, only used to guaranty machine throuput
	    highPriority    = 0x00020000  //x xxvalid for read and write calls, only used to guaranty machine throuput
    };

    //////////////////////////////////////////////////////////
    //					SlVector Class						//
    //////////////////////////////////////////////////////////
	// Caution:  will hold maximum 100 000 elements !!      //
	//           vector will stop increasing then.          //
	//////////////////////////////////////////////////////////
    template <class T> class SlVector
    {
        T* m_pFirst;
        T* m_pLast;
        long m_lSize;

    public:
        //////////////////////////////////
        SlVector(void)
        {
            m_pFirst = NULL;
            m_pLast = NULL;
            m_lSize = 0;
        };

        //////////////////////////////////
        SlVector(const SlVector& v)
        {
            m_pFirst = NULL;
            m_pLast = NULL;
            m_lSize = 0;
            long n = v.size();

            for(long i = 0; i < n; i++)
            {
                push_back(v.at(i));
            }
        };

        //////////////////////////////////
        ~SlVector(void)
        {
            clear();
        };

        //////////////////////////////////
        void clear()
        {
            if (m_pFirst != NULL) delete[] m_pFirst;

            m_pFirst = NULL;
            m_pLast = NULL;
            m_lSize = 0;
        };

        //////////////////////////////////
        long size() const
        {
            return m_lSize;
        };

        //////////////////////////////////
        // make sure to provide a correct index !
        T& at(long n) const
        {
            return *(m_pFirst + n);
        };

        //////////////////////////////////
        long remove(long n)
        {
			if (n < 0 || n >= m_lSize)
				return m_lSize;

			long newSize = m_lSize - 1;

            if (newSize == 0 || newSize == 10 || newSize == 100 || newSize == 1000 || newSize == 10000)
            {
				if (newSize == 0)   // remove last item
	                clear();
				else
				{
					T* pNew = new T[newSize];

					if (pNew != NULL)
					{
						// copy previous
						for (long i = 0; i < n - 1; i++)
						{
							*(pNew + i) = *(m_pFirst + i);
						}
						// copy after n
						for (long i = n + 1; i < m_lSize; i++)
						{
							*(pNew + i - 1) = *(m_pFirst + i);
						}

						delete[] m_pFirst;

						m_lSize--;
						m_pFirst = pNew;
						m_pLast = m_pFirst + (m_lSize - 1);
					}
				}
            }
			else
            {
                // copy after n
                for(long i = n + 1; i < m_lSize; i++)
                {
                    *(m_pFirst + i - 1) = *(m_pFirst + i);
                }

                m_lSize--;
                m_pLast = m_pFirst + (m_lSize - 1);
            }

            return m_lSize;
        };

        //////////////////////////////////
        void push_back(T& item)
        {
			if (m_lSize >= 100000)
				return;

			long newSize = m_lSize + 1;

			if (1 == newSize || 11 == newSize || 101 == newSize || 1001 == newSize || 10001 == newSize)
			{
				T* pNew = NULL;

				if (m_lSize == 0)
					pNew = new T[10];
				else
					pNew = new T[m_lSize * 10];

				if (pNew != NULL)
				{
					// copy previous
					for (long i = 0; i < m_lSize; i++)
					{
						*(pNew + i) = *(m_pFirst + i);
					}

					if (m_pFirst != NULL)
						delete[] m_pFirst;

					m_pFirst = pNew;
				}
			}

			m_pLast = m_pFirst + m_lSize;
			if (m_pLast != NULL)
				*m_pLast = item;

			m_lSize++;
		};

        //////////////////////////////////
        void pop_back()
        {
            if (m_pFirst != NULL)
            {
                remove(m_lSize - 1);
            }
        };

        //////////////////////////////////
        SlVector& operator=(const SlVector& v)
        {
            clear();
            long n = v.size();
            for(long i = 0; i < n; i++)
            {
                push_back(v.at(i));
            }

            return *this;
        };
    };

    //////////////////////////////////////////////////////////
    //					SlString Class						//
    //////////////////////////////////////////////////////////
	class SL_OPERATE_CPP_API SlString
    {
        char*   m_pString;

        void save(const char*);

    public:
        SlString(void);
        SlString(const char*);
        SlString(const SlString&);
        ~SlString(void);
        char at(long) const;
        void append(const char*);
        void append(const SlString&);
        const char* c_str() const;
        void clear();
        bool equals(SlString&);
        long length() const;
        SlVector<SlString> split(const char);
        SlString substr(int /* start index */);
        SlString substr(int /* start index */, int /* length */);
        long find(const SlString& str, long pos = 0) const;  // reports -1 if string is not found
	    bool operator==(SlString&);
	    SlString& operator=(const char*);
	    SlString& operator=(const SlString&);
    };

#ifdef _WINDOWS
#pragma warning(disable:4251)
// warning 4251 results from the fact that the template class and an exported class is used for non exported members (here: m_aValue).
// A client does not need to access m_sParameters(see getter/setter). To get rid of this warning the pragma directive is used.
#endif

    //////////////////////////////////////////////////////////
    //					SlValue Class						//
    //////////////////////////////////////////////////////////
	class SL_OPERATE_CPP_API SlValue
	{
	public:
		enum type 
		{
			Invalid,
			Boolean,
			Char,
			UChar,
			Int,
			UInt,
			Long,
			ULong,
			LongLong,					// 64 bit
			ULongLong,					// 64 bit
			Double,
			String,
			SlValueArray,
            DateTime                    
		};

		SlValue(void);
		SlValue(const bool value);
		SlValue(const char value);
		SlValue(const unsigned char value);
		SlValue(const int value);
		SlValue(const unsigned int value);
		SlValue(const long value);
		SlValue(const unsigned long value);
		SlValue(const long long value);
		SlValue(const unsigned long long value);
		SlValue(const double value);
		SlValue(const SlString& value);
        SlValue(const SlValue& value);
		SlValue(const SlVector<SlValue>&);
        SlValue(const time_t, SlValue::type); 
		~SlValue(void);

		SlValue& operator=(const bool /* value */); 
		SlValue& operator=(const char /* value */); 
		SlValue& operator=(const unsigned char /* value */); 
		SlValue& operator=(const int /* value */); 
		SlValue& operator=(const unsigned int /* value */); 
		SlValue& operator=(const long /* value */); 
		SlValue& operator=(const unsigned long /* value */); 
		SlValue& operator=(const long long /* value */); 
		SlValue& operator=(const unsigned long long /* value */); 
		SlValue& operator=(const double /* value */); 
		SlValue& operator=(const SlString& /* value */); 
		SlValue& operator=(const SlValue& /* value */); 
		SlValue& operator=(const SlVector<SlValue>& /* value */); 

		type GetType() const;
		type getType() const;

		bool				toBool();
		char				toChar();
		unsigned char		toUChar();
		int					toInt();
		unsigned int		toUInt();
		long				toLong();
		unsigned long		toULong();
		long long			toLongLong();
		unsigned long long	toULongLong();
		double				toDouble();
		SlString			toString();
		SlVector<SlValue>&  toSlValueArray();
		time_t              toTime_t();

	private:
		type				m_nType;
		bool				m_Bool;
		char				m_Char;
		unsigned char		m_uChar;
		int					m_Int;
		unsigned int		m_uInt;
		long				m_Long;
		unsigned long		m_uLong;
		long long			m_LongLong;
		unsigned long long	m_uLongLong;
		double				m_Double;
		SlString			m_String;
		SlVector<SlValue>	m_aValue;

        void MakeIdenticalValue(const SlValue& value);
		bool				getBool() const;
		char				getChar() const;
		unsigned char		getUChar() const;
		int					getInt() const;
		unsigned int		getUInt() const;
		long				getLong() const;
		unsigned long		getULong() const;
		long long			getLongLong() const;
		unsigned long long	getULongLong() const;
		double				getDouble() const;
		SlString			getString() const;
		const SlVector<SlValue>&  getSlValueArray() const;
        const time_t        getTime_t() const;
	};
#ifdef _WINDOWS
#pragma warning(default:4251)
#endif

    //////////////////////////////////////////////////////////
    //					SlDataSvcItem Class					//
    //////////////////////////////////////////////////////////
	class SL_OPERATE_CPP_API SlDataSvcItem
	{
	public:
		SlDataSvcItem(void);
		SlDataSvcItem(SlDataSvcItem& /* item */);
		SlDataSvcItem(SlString& /* name */);
		SlDataSvcItem(char* /* name */);
		~SlDataSvcItem(void);

		SlDataSvcItem& operator=(SlDataSvcItem& /* item */);

		SlDataSvcItem& operator=(SlString& /* name */); 
		SlString getName();
		void setName(SlString& /* name */);

        SlDataSvcItem& operator=(SlValue& /* value */); 
		SlValue getValue();
		void setValue(SlValue& /* value */);

		SlValue         value;
		SlString		name;

	private:
	};



    //////////////////////////////////////////////////////////
    //					DataSvc	Class						//
    //////////////////////////////////////////////////////////
    //	class to be used for								//
    //		* reading										//
    //		* writing										//
    //		* subscribing (hotlink)							//
    //	data in NCU or PLC									//
    //////////////////////////////////////////////////////////
	typedef long SlDataSvcError;
	const long SL_DATASVC_OK = 0;

	struct SupplementReadInfo
	{
		SlString    serverInfo;
		long long   sequenceNo;
	};

	class SL_OPERATE_CPP_API SlDataSvcStatus
	{
    public:
        SlDataSvcError		error;
		SupplementReadInfo	readInfo;		// read 
		time_t				timestamp;		// write
	};

	// Callback interface
	class ISlDataSvcCb
	{ 
		public:     
			virtual void SlDataSvcItemChanged(SlDataSvcItem& /* variable */, SlDataSvcStatus& /* status */) = 0; 
			virtual void SlDataSvcItemsChanged(SlVector<SlDataSvcItem>& /* variables */, SlVector<SlDataSvcStatus>& /* status */) = 0; 
			virtual void SlDataSvcAsyncReadResult(SlDataSvcItem& /* variable */, SlDataSvcStatus& /* status */) = 0; 
			virtual void SlDataSvcAsyncReadResult(SlVector<SlDataSvcItem>& /* variables */, SlVector<SlDataSvcStatus>& /* status */) = 0; 
			virtual void SlDataSvcAsyncWriteResult(SlDataSvcItem& /* variable */, SlDataSvcStatus& /* status */) = 0; 
			virtual void SlDataSvcAsyncWriteResult(SlVector<SlDataSvcItem>& /* variables */, SlVector<SlDataSvcStatus>& /* status */) = 0; 
	}; 

	// SlDataSvcClass
	class SL_OPERATE_CPP_API SlDataSvc
	{
	public:
		// ***************  public functions  *********************
		SlDataSvc(void);
		SlDataSvc(SlString /* ncu */);
		~SlDataSvc(void);

		// single item read
		SlDataSvcError read(SlDataSvcItem& /* variable */);
		SlDataSvcError read(SlDataSvcItem& /* variable */, SlDataSvcStatus& /* info */);
		SlDataSvcError readAsync(SlDataSvcItem& /* variable */, ISlDataSvcCb* /* pSlDataSvcAsyncReadResult */);

		// multi item read
		SlDataSvcError read(SlVector<SlDataSvcItem>& /* variables */);
		SlDataSvcError read(SlVector<SlDataSvcItem>& /* variables */, SlVector<SlDataSvcStatus>& /* results */);
		SlDataSvcError readAsync(SlVector<SlDataSvcItem>& /* variables */, ISlDataSvcCb* /* pSlDataSvcAsyncReadResult */);

		// single item write
		SlDataSvcError write(SlDataSvcItem& /* variable */);				
		SlDataSvcError write(SlDataSvcItem& /* variable */, SlDataSvcStatus& /* result */);
		SlDataSvcError writeAsync(SlDataSvcItem& /* variable */, ISlDataSvcCb* /* pSlDataSvcAsyncWriteResult */);
		
		// multi item write
		SlDataSvcError write(SlVector<SlDataSvcItem>& /* variables */);
		SlDataSvcError write(SlVector<SlDataSvcItem>& /* variables */, SlVector<SlDataSvcStatus>& /* results */); 
		SlDataSvcError writeAsync(SlVector<SlDataSvcItem>& /* variables */, ISlDataSvcCb* /* pSlDataSvcAsyncWriteResult */);

		// Advise
		SlDataSvcError subscribe(SlDataSvcItem& /* variable */, ISlDataSvcCb* /* pSlDataSvcItemChanged */);
		SlDataSvcError subscribe(SlVector<SlDataSvcItem>& /* variables */, ISlDataSvcCb* /* pSlDataSvcItemsChanged */);

		// UnAdvise
		SlDataSvcError unSubscribe();

        // Cancel async activity
        SlDataSvcError cancel();

		// updaterate
		unsigned int highUpdateRate();
		unsigned int standardUpdateRate();
		unsigned int lowUpdateRate();

		// timeout
		unsigned int standardTimeout();

		// get/set attributes
		SlPriorityFlags getPriorityFlags();
		void setPriorityflags(SlPriorityFlags /* prio */);

		unsigned int getUpdaterate();
		void setUpdaterate(unsigned int /* updaterate */);

		bool getSynchronizedMultivarAccess();
		void setSynchronizedMultivarAccess(bool /* sync */);

		unsigned int getTimeout();
		void setTimeout(unsigned int /* timeout */);

		double getDeadBand();
		void setDeadBand(double /* deadband */);

	private:
		void*		m_p;
	};

    //////////////////////////////////////////////////////////
    //					AccessLevel Class					//
    //////////////////////////////////////////////////////////
    //	class for file access rights						//
    //////////////////////////////////////////////////////////
	enum SlAccessLevel
	{
		SIEMENS = 0,
        MANUFACT = 1,
        SERVICE = 2,
        USER = 3,
        KEY_3 = 4,
        KEY_2 = 5,
        KEY_1 = 6,
        KEY_0 = 7,
		NOTHING = 10
	};

	class SL_OPERATE_CPP_API SlAccessRights
	{
	public:
		SlAccessRights(void);
		~SlAccessRights(void);

		SlAccessLevel getRead();
		void setRead(SlAccessLevel);

		SlAccessLevel getWrite();
		void setWrite(SlAccessLevel);

		SlAccessLevel getExecute();
		void setExecute(SlAccessLevel);

		SlAccessLevel getShow();
		void setShow(SlAccessLevel);

		SlAccessLevel getDelete();
		void setDelete(SlAccessLevel);
		
	private:
		SlAccessLevel m_Read;
		SlAccessLevel m_Write;
		SlAccessLevel m_Execute;
		SlAccessLevel m_Show;
		SlAccessLevel m_Delete;
	};


    //////////////////////////////////////////////////////////
    //					Node Class							//
    //////////////////////////////////////////////////////////
    //	class representing a single file or directory		//
    //	on PCU or NCU										//
    //////////////////////////////////////////////////////////
	class SlNode2Wrapper;			// forward declaration

	class SL_OPERATE_CPP_API SlNode
	{
	public:
		SlNode(void);
		SlNode(SlString /* path */);
		SlNode(SlNode&);
		~SlNode(void);
		SlNode& operator=(SlNode&);
		SlNode& operator=(SlNode2Wrapper&);

		SlString getPath();
		void setPath(SlString path);

		SlAccessRights getAccessRights();
		void setAccessRights(SlAccessRights);

		SlString getName();
		SlString getRealPath();
		time_t lastAccess();
		bool exists();
		bool IsDirNode();
		bool IsNCNode();
		long size();
		
	private:
		SlNode2Wrapper* m_p;
	};


    //////////////////////////////////////////////////////////
    //					File Class							//
    //////////////////////////////////////////////////////////
    //	class to be used for handling files, e.g.:			//
    //		* list / list asyncchronously a folder			//
    //		* copy a file									//
    //		* delete a file									//
    //		* etc.											//
    //	on PCU or NCU										//
    //////////////////////////////////////////////////////////

	typedef long SlFileSvcError;
	const long SL_FILESVC_OK = 0;

	struct SlFileSvcStatus
	{
		SlFileSvcError	error;
	};

	// Callback interface
	class ISlFileSvcCb
	{ 
		public:     
			virtual void SlFileSvcListCompleted(long nID, SlVector<SlNode>& /* nodes */, SlFileSvcStatus& /* status */) = 0;
			virtual void SlFileSvcListCanceled(long nID) = 0;
			virtual void SlFileSvcListProgress(long nID, int percentage) = 0;

			virtual void SlFileSvcCompleted(long nID, SlFileSvcStatus&) = 0;
			virtual void SlFileSvcCanceled(long nID) = 0;
			virtual void SlFileSvcProgress(long nID, int percentage) = 0;

			virtual void SlFileSvcDeviceMounted(SlString /* strLogicalPath */)=0;
			virtual void SlFileSvcDeviceUnmounted(SlString /* strLogicalPath */)=0;
    }; 

	// Callback interface for block transfer services
	class ISlFileSvcBlockTransferCb
	{ 
		public:     
			virtual void SlFileSvcBlockTransferCompleted(long lID, SlFileSvcStatus status) = 0;
			virtual void SlFileSvcBlockTransferCanceled(long lID) = 0;
			virtual void SlFileSvcBlockTransferProgress(long lID, int percentage) = 0;

			virtual void SlFileSvcReadBlockTransferData(long lID, char* data, int lenData)=0;
			virtual void SlFileSvcProvideBlockTransferData(long lID, SlFileSvcStatus status)=0;
    }; 

	class SL_OPERATE_CPP_API SlFileSvc
	{
	public:
		SlFileSvc(void);
		~SlFileSvc(void);

		SlFileSvcError list(SlNode, SlVector<SlNode>&);
		SlFileSvcError listAsync(SlNode, ISlFileSvcCb*,long& requestId, bool reportProgress = false);

		SlFileSvcError copy(SlNode sourceNode, SlNode destNode, bool overwrite = false);
		SlFileSvcError copyAsync(SlNode sourceNode, SlNode destNode, ISlFileSvcCb*, long& requestId, bool reportProgress = false, bool overwrite = false);

		SlFileSvcError move(SlNode sourceNode, SlNode destNode, bool overwrite = false);
		SlFileSvcError moveAsync(SlNode sourceNode, SlNode destNode, ISlFileSvcCb*, long& requestId, bool reportProgress = false, bool overwrite = false);

		SlFileSvcError create(SlNode sourceNode, bool overwrite = false);
		SlFileSvcError createFolder(SlNode sourceNode, bool createParent = false);

		SlFileSvcError remove(SlNode sourceNode);
		SlFileSvcError removeAsync(SlNode sourceNode, ISlFileSvcCb*, long& requestId, bool reportProgress = false);

		SlFileSvcError rename(SlNode sourceNode, SlNode destNode, bool overwrite = false);
		SlFileSvcError renameAsync(SlNode sourceNode, SlNode destNode, ISlFileSvcCb*, long& requestId, bool reportProgress = false, bool overwrite = false);

		SlFileSvcError select(SlNode sourceNode, unsigned long channel);
        SlFileSvcError selectExtern(SlNode node, unsigned long channel);

		SlFileSvcError cancelAsync(ISlFileSvcCb*, long& requestID);
		SlFileSvcError cancelAsync(ISlFileSvcBlockTransferCb* pCb, long& requestID);
		SlFileSvcError cancel(long& nRequestID);

		SlFileSvcError subscribe(SlString /* strLogicalPath */, ISlFileSvcCb*);     // subscribe device mounted/unmounted events 
		SlFileSvcError unSubscribe();

		SlFileSvcError startBlockTransferReadAsync(SlNode source, ISlFileSvcBlockTransferCb* dest, long& requestId, bool reportProgress = false);
		SlFileSvcError startBlockTransferWriteAsync(SlNode dest, ISlFileSvcBlockTransferCb* source, long& requestId);
        SlFileSvcError writeBlockTransferDataAsync(char* data, int len, bool eof);
    private:
		void*		m_p;
	};


    //////////////////////////////////////////////////////////
    //					Device Class						//
    //////////////////////////////////////////////////////////
    //	class to be used for devices, e.g.:	        		//
    //		* local hard disk ("C:") or                     // 
    //              USB at TCU Front("//ACTTCU/FRONT")		//
    //  for reading attributes, e.g.:                       //
    //      * free / used memory                            //
    //		* device type									//
    //		* mounted in case of removable devices			//
    //	on PCU or NCU										//
    //////////////////////////////////////////////////////////

	typedef long SlDeviceError;
	const long SL_DEVICE_OK = 0;

    // DeviceType
    enum DeviceType
    {
        UNDEFINED = 0,
        FIXED_DEVICE = 0x01,
        REMOVABLE = 0x02,
        REMOTE = 0x04,
        CDROM = 0x08,
        RAMDISK = 0x10,
    };

    struct SlDeviceStatus
	{
		SlDeviceError	error;
	};

	// Callback interface
	class ISlDeviceCb
	{ 
		public:     
			virtual void SlDeviceMounted(SlString /* strLogicalPath */)=0;
			virtual void SlDeviceUnmounted(SlString /* strLogicalPath */)=0;
    }; 

	class SL_OPERATE_CPP_API SlDevice
	{
	public:
		SlDevice(SlString /* deviceName */);
		~SlDevice(void);

		SlDeviceError getDeviceName(SlString&);
		SlDeviceError getDeviceType(DeviceType&);
		SlDeviceError getFreeMemory(unsigned long long&);     // no. of bytes free
		SlDeviceError getUsedMemory(unsigned long long&);     // no. of bytes used
		SlDeviceError isMounted(bool&);

		SlDeviceError subscribe(ISlDeviceCb*);     // subscribe device mounted/unmounted events 
		SlDeviceError unSubscribe();

    private:
		void*		m_p;
	};


    //////////////////////////////////////////////////////////
    //					PiSvc Class							//
    //////////////////////////////////////////////////////////
    //	class to be used for invoking PI functions			//
    //	in NCU or PLC										//
    //////////////////////////////////////////////////////////
	typedef long SlPiSvcError;
	const long SL_PISVC_OK = 0;

	struct SlPiSvcStatus
	{
		SlPiSvcError	error;
		time_t			timestamp;		
	};

    // Callback interface
	class ISlPiSvcCb
	{ 
		public:     
			virtual void SlPiSvcCompleted(SlPiSvcStatus) = 0;
	}; 

	class SL_OPERATE_CPP_API SlPiSvc
	{
	public:
		SlPiSvc(void);
		SlPiSvc(SlVector<SlString>&);
		~SlPiSvc(void);

		SlPiSvcError start();
		SlPiSvcError start(SlPiSvcStatus&);
		SlPiSvcError startAsync(ISlPiSvcCb*);
		SlPiSvcError cancel();

        SlPiSvcError stop();
        SlPiSvcError stop(SlPiSvcStatus&);
		
        SlPiSvcError plcMemoryReset();
        SlPiSvcError plcMemoryReset(SlPiSvcStatus&);

        long getTimeout();
		void setTimeout(long /* t */);

		SlVector<SlString> getArgs();
		void setArgs(SlVector<SlString>& /* args */);

		SlPriorityFlags getPriorityFlags();
		void setPriorityFlags(SlPriorityFlags /* prio */);

	private:
		void*		m_p;
	};

    //////////////////////////////////////////////////////////
    //					SlAlarmSource Class					//
    //////////////////////////////////////////////////////////
	class SL_OPERATE_CPP_API SlAlarmSource
	{
	public:
		SlAlarmSource(void);
        ~SlAlarmSource(void);

		long getId() const;
		void setId(long);
		SlString getName() const;
		void setName(SlString);

	private:
        long        m_lId;
        SlString    m_sName;
	};


    //////////////////////////////////////////////////////////
    //					enums for class SlAlarm		        //
    //////////////////////////////////////////////////////////
	enum SlAlarmDisplayLocation
	{
		NOLOC = 0,
		HEADER = 1,
		SCREEN
	};

	enum SlAlarmCategory				
	{															
		NOCAT = 0,
		SINUMERIK = 1,
		PARTPROG_MESSAGE = 2
	};

#undef NOGROUP
	enum SlAlarmCancelGroup				
	{
		NOGROUP = 0,
		HMI_AND_NCU = 1,
		HMI = 2
	};

	enum SlAlarmClearInfo
	{
        // reserved
	};

	enum SlAlarmState					
	{
		UNKNOWN = -1,
		ALARM_STATE_ACTIVE   = 1,
		ALARM_STATE_ACKED    = 2, 
		ALARM_STATE_ENABLED  = 4,

		ALARM_CHANGE_ACTIVE  = 0x00000010,
		ALARM_CHANGE_ACKED   = 0x00000020,
		ALARM_CHANGE_ENABLED = 0x00000040,
		ALARM_ACK_REQUIRED   = 0x00000080,

		ALARM_HMI_CANCEL_BTN = 0x00000100,

		ALARM_HMI_CANCEL_TIME = 0x00000200,

		ALARM_COMING     = ALARM_STATE_ENABLED | ALARM_STATE_ACTIVE | ALARM_CHANGE_ACTIVE,
		ALARM_CAME_GOING = ALARM_STATE_ENABLED | ALARM_CHANGE_ACTIVE,

		ALARM_HMI_CANCEL_BTN_COMING     = ALARM_HMI_CANCEL_BTN | ALARM_COMING,
		ALARM_HMI_CANCEL_BTN_CAME_GOING = ALARM_HMI_CANCEL_BTN | ALARM_CAME_GOING,

		ALARM_HMI_CANCEL_TIME_COMING     = ALARM_HMI_CANCEL_TIME | ALARM_COMING,
		ALARM_HMI_CANCEL_TIME_CAME_GOING = ALARM_HMI_CANCEL_TIME | ALARM_CAME_GOING,

		ALARM_COMING_TOACK     = ALARM_ACK_REQUIRED | ALARM_COMING,
		ALARM_CAME_GOING_TOACK = ALARM_ACK_REQUIRED | ALARM_CAME_GOING,
		ALARM_CAME_GONE_ACKING = ALARM_ACK_REQUIRED | ALARM_STATE_ENABLED | ALARM_STATE_ACKED | ALARM_CHANGE_ACKED,
		ALARM_CAME_ACKING      = ALARM_ACK_REQUIRED | ALARM_STATE_ENABLED | ALARM_STATE_ACTIVE | ALARM_STATE_ACKED | ALARM_CHANGE_ACKED,
		ALARM_CAME_ACKED_GOING = ALARM_ACK_REQUIRED | ALARM_STATE_ENABLED | ALARM_STATE_ACKED | ALARM_CHANGE_ACTIVE
	};

	enum SlAlarmQuality
	{
		QUALITY_BAD = 1,
		QUALITY_GOOD,        
		QUALITY_UNCERTAIN
	};


#ifdef _WINDOWS
#pragma warning(disable:4251)
// warning 4251 results from the fact that the template class and an exported class is used for non exported members (here: m_sParameters).
// A client does not need to access m_sParameters(see getter/setter). To get rid of this warning the pragma directive is used.
#endif


    //////////////////////////////////////////////////////////
    //					SlAlarm	Class						//
    //////////////////////////////////////////////////////////
    //	class representing a single alarm and its			//
    //	attributes e.g..:									//	
    //				* timstamp (alarm occured)	    		//
    //				* alarm message							//
    //				* etc.									//
    //////////////////////////////////////////////////////////
    class SL_OPERATE_CPP_API SlAlarm
	{
	public:
		SlAlarm(void);
		SlAlarm(const SlAlarm&);
		~SlAlarm(void);

		long getId();
		void setId(long id);

		SlAlarmSource getSource();
		void setSource(SlAlarmSource /* source */);

		int getInstance();
		void setInstance (int /* instance */);

		time_t getTimeStamp();
		void setTimeStamp(time_t /* time */);

		SlAlarmState getState();
		void setAlarmState(SlAlarmState /* state */);

		int getPriority();
		void setPriority(int /* prio */);

		SlAlarmQuality getQuality();
		void setQuality(SlAlarmQuality /* quality */);

		SlString getMessage();
		void setMessage(SlString /* message */);
	    const wchar_t* getWCharMessage();  
		void setWCharMessage(wchar_t* /* message */);

		SlVector<SlString> getParameters();
		void setParameters(SlVector<SlString> /* parameters */);

		SlAlarmDisplayLocation getDisplayLocation();
		void setDisplayLocation(SlAlarmDisplayLocation /* loc */);

		SlString getComment();
		void setComment(SlString /*comment */);

		SlString getHelpFileUrl();
		void setHelpFileUrl(SlString /* url */);

		SlAlarmCategory getCategory();
		void setCategory(SlAlarmCategory /* cat */);

		SlAlarmCancelGroup getCancelGroup();
		void setCancelGroup(SlAlarmCancelGroup /* group */);

		SlAlarmClearInfo getClearInfo();
		void setClearInfo(SlAlarmClearInfo /* info */);

        SlAlarm& operator =(SlAlarm&);

	private:
		long					m_lId;					// alarm no.
		SlAlarmSource			m_AlarmSource;
		int						m_nInstance;
		time_t					m_Timestamp;
		SlAlarmState			m_Alarmstate;
		int						m_nPriority;
		SlAlarmQuality			m_Quality;
		SlString				m_sMessage;
        wchar_t*                m_WCharMessage;
		SlVector<SlString>      m_sParameters;
		SlAlarmDisplayLocation	m_DisplayLocation;
		SlString				m_sComment;
		SlString				m_sHelpFileUrl;
		SlAlarmCategory			m_Category;
		SlAlarmCancelGroup		m_Cancelgroup;
		SlAlarmClearInfo		m_AlarmClearInfo;

        void copyAlarm(const SlAlarm&);
        void copyWCharMessage(wchar_t*);
	};
#ifdef _WINDOWS
#pragma warning(default:4251)
#endif

    //////////////////////////////////////////////////////////
    //					SlAlarmSvc	Class					//
    //////////////////////////////////////////////////////////
    //	class to be used for								//
    //				* reading current alarms				//
    //				* subscribing current alarms			//
    //////////////////////////////////////////////////////////

	typedef long SlAlarmSvcError;
	const long SL_ALARMSVC_OK = 0;

	// Callback interface alarm list
	class ISlAlarmSvcCb
	{ 
		public:     
			virtual void SlAlarmlistChanged(SlVector<SlAlarm>& alarms) = 0;
	}; 

	// Callback interface events
	class ISlAlarmSvcEventsCb
	{ 
		public:     
			virtual void SlAlarmEventlistChanged(SlVector<SlAlarm>& alarms) = 0;
			virtual void SlAlarmNewEvent(SlVector<SlAlarm>& alarms) = 0;
	}; 

	class SL_OPERATE_CPP_API SlAlarmSvc
	{
	public:
		SlAlarmSvc(void);
		SlAlarmSvc(SlString language);
		SlAlarmSvc(SlString language, SlString ncu);
		SlAlarmSvc(SlString language, SlString ncu, int eventlistLength);
		~SlAlarmSvc(void);

		SlAlarmSvcError getSources(SlVector<SlAlarmSource>& );
		SlAlarmSvcError setAlarm(SlAlarm /* alarm */);
		SlAlarmSvcError resetAlarm(SlAlarm /* alarm */);

		// current pending alarms
		SlAlarmSvcError subscribeAlarms(ISlAlarmSvcCb* /* SlAlarmlistChanged */);
		SlAlarmSvcError unSubscribeAlarms(ISlAlarmSvcCb* /* SlAlarmlistChanged */);

		// list (default 20) of events while alarms occured, e.g.: alarm coming, alarm going, alarm acknowledged
		SlAlarmSvcError subscribeEventList(ISlAlarmSvcEventsCb* SlAlarmEventlistChanged);
		SlAlarmSvcError unSubscribeEventList(ISlAlarmSvcEventsCb* SlAlarmEventlistChanged);
		// event(s) while alarm(s) occured, e.g.: alarm coming, alarm going, alarm acknowledged
		SlAlarmSvcError subscribeEvents(ISlAlarmSvcEventsCb* SlAlarmNewEvent);
		SlAlarmSvcError unSubscribeEvents(ISlAlarmSvcEventsCb* SlAlarmNewEvent);

	private:
		void*								m_p;
	};


    //////////////////////////////////////////////////////////
    //				SlDrive Class	    					//
    //////////////////////////////////////////////////////////
    //	class representing s single drives             		//
    //	providing access to a drive's data (e.g.:motor temp.)//
    //////////////////////////////////////////////////////////

    typedef long SlDrivesSvcError;
	const long SL_DRIVESSVC_OK = 0;

    enum SlDriveType
	{
        NotSpecified = 0,
        ControlUnit = 2,
        ComModule,
        Drive,
        LineModule,
        IO
    };

    class ISlDrivesSvcCb
	{ 
		public:     
			virtual void SlDrivesSvcCompleted(long nStatus) = 0;
			virtual void SlDrivesSvcProgress(int percentage) = 0;

	}; 

    class SL_OPERATE_CPP_API SlDrive
	{
	public:
		SlDrive(void);
		SlDrive(long, SlString, long, long, long, SlString, SlDriveType, long);
		~SlDrive(void);

		SlDrivesSvcError readParameter(int /* parameterNo */, double& value); 
		SlDrivesSvcError readParameter(int /* parameterNo */, int /* index */, double& value);
		SlDrivesSvcError readParameter(int /* parameterNo */, int /* start index */,int /* end index*/, SlVector<double>&);
		SlDrivesSvcError readParameter(SlString& /* parameterNo */, double& );
		SlDrivesSvcError readParameter(SlVector<SlString>&, SlVector<double>& );
		
		SlDrivesSvcError writeParameter(int /* parameterNo */, double value);
		SlDrivesSvcError writeParameter(int /* parameterNo */, int /* index */, double value);
		SlDrivesSvcError writeParameter(int /* parameterNo */, int /* start index */,int /* end index*/, SlVector<double>&);
		SlDrivesSvcError writeParameter(SlString /* parameterNo */, double value);
		SlDrivesSvcError writeParameter(SlVector<SlString>& , SlVector<double>& );

        SlDrivesSvcError reset();
		SlDrivesSvcError resetWithNcu();
		SlDrivesSvcError save();
		SlDrivesSvcError saveAsync(ISlDrivesSvcCb*);
		
        SlDriveType getDriveType();
        long getBusAddress();
        long getSlaveAddress();
        long getDriveObjectId();
        long getDriveObjectTypeId();
		SlString getDriveObjectName();
        long getAxisNumber();
        SlString getAxisName();
        long getDriveHandle();

	    SlDrive& operator=(const SlDrive&);


	private:
		SlDriveType m_DriveType;
        long        m_lBusAddr;
        long        m_lSlaveAddr;
        long        m_lDrvObjId;
        SlString    m_sDriveObjName;
        long        m_lAxisNo;
        SlString    m_sAxisName;
        long        m_lDrvHandle;
		
	};


    //////////////////////////////////////////////////////////
    //				SlDrivesSvc Class						//
    //////////////////////////////////////////////////////////
    //	class representing the drives service       		//
    //	providing access to drives (e.g.drives list)	    //
    //////////////////////////////////////////////////////////

	// Callback interface
	class ISlDrivesSvcListCb
	{ 
		public:     
			virtual void SlDrivesSvcListCompleted(long nStatus, SlVector<SlDrive>& drives) = 0;
			virtual void SlDrivesSvcListProgress(int percentage) = 0;

	}; 

    class SL_OPERATE_CPP_API SlDrivesSvc
	{
	public:
		SlDrivesSvc(void);
		~SlDrivesSvc(void);

        SlDrivesSvcError listDrives(SlDriveType, SlVector<SlDrive>&);
        SlDrivesSvcError listDrives(SlVector<SlDrive>&);
        SlDrivesSvcError listDrivesAsync(SlDriveType, ISlDrivesSvcListCb*);
        SlDrivesSvcError listDrivesAsync(ISlDrivesSvcListCb*);
        
        SlDrivesSvcError selectDrive(int machineAxisNumber, SlDrive& drive);
        SlDrivesSvcError selectDrive(SlString machineAxisName, SlDrive& drive);

        SlDrivesSvcError resetControlUnits();
        SlDrivesSvcError resetNcu();
        SlDrivesSvcError resetNcuAndControlUnits();
        SlDrivesSvcError prepareControlUnitsForReset();
        SlDrivesSvcError save();
        SlDrivesSvcError saveAsync(ISlDrivesSvcCb*);
        SlDrivesSvcError saveControlUnits();
        SlDrivesSvcError saveControlUnitsAsync(ISlDrivesSvcCb*);

    private:
		void*			m_p;
	};

    //////////////////////////////////////////////////////////
    //				SlInfraStructSvc Class 			    	//
    //////////////////////////////////////////////////////////
    //	class representing the infrastructure service  		//
    //	providing access to                                 //
    //              * UI language   	                    //
    //              * screen resolution	                    //
    //              * access level  	                    //
    //              * active application                    //
    //              * active channel                        //
    //              * active NCU                            //
    //////////////////////////////////////////////////////////

    typedef long SlInfraStructSvcError;
	const long SL_INFRASTRUCTSVC_OK = 0;

    struct SlScreenResolution
    {
        int X;
        int Y;
    };

	// Callback interface
	class ISlInfraStructSvcCb
	{ 
		public:     
			virtual void SlInfraStructSvcLanguageChanged(SlString /* language */) = 0;
			virtual void SlInfraStructSvcResolutionChanged(SlScreenResolution /*resolution */) = 0;
            virtual void SlInfraStructSvcAccessLevelChanged(SlAccessLevel /*accesslevel*/) = 0;
            virtual void SlInfraStructSvcChannelNumberChanged(int /*channelNo*/) = 0;
	}; 

    class SL_OPERATE_CPP_API SlInfraStructSvc
	{
	public:
		SlInfraStructSvc(void);
		~SlInfraStructSvc(void);

        SlInfraStructSvcError subscribeLanguage(ISlInfraStructSvcCb*);
        SlInfraStructSvcError unSubscribeLanguage(ISlInfraStructSvcCb*);

        SlInfraStructSvcError subscribeResolution(ISlInfraStructSvcCb*);
        SlInfraStructSvcError unSubscribeResolution(ISlInfraStructSvcCb*);

        SlInfraStructSvcError subscribeAccessLevel(ISlInfraStructSvcCb*);
        SlInfraStructSvcError unSubscribeAccessLevel(ISlInfraStructSvcCb*);

        SlInfraStructSvcError subscribeChannelNo(ISlInfraStructSvcCb*);
        SlInfraStructSvcError unSubscribeChannelNo(ISlInfraStructSvcCb*);

        SlString getCurrentLanguage();
        SlInfraStructSvcError setCurrentLanguage(SlString);

        SlScreenResolution getCurrentResolution();
        SlInfraStructSvcError setCurrentResolution(SlScreenResolution);

        SlAccessLevel getCurrentAccessLevel();

        int getCurrentChannelNo();
        SlInfraStructSvcError setChannelNo(int /* channelNo*/);

        SlString getActiveNcu();
        SlInfraStructSvcError setActiveNcu(SlString /*ncu*/, int chanNo=1);

        SlString getActiveArea();
        SlInfraStructSvcError setActiveArea(SlString /*area*/, SlString dialog="", SlString args="");
        SlInfraStructSvcError switchToArea(SlString /*area*/, SlString dialog="", SlString args="");
        SlInfraStructSvcError switchToDialog(SlString /*dialog*/, SlString args="");

        SlInfraStructSvcError shutdownHmi(bool /*force*/);
        SlInfraStructSvcError restartHmi();

    private:
		void*			m_p;
	};


    //////////////////////////////////////////////////////////////
    //				SlArchivingSvcNotifier Class 			    //
    //////////////////////////////////////////////////////////////
    //	class representing the notifier for the archive service //
    //	providing notifies of a running archive service action  //
    //////////////////////////////////////////////////////////////
 	typedef long SlArchivingSvcNotifierError;
	const long SL_ARCHIVINGSVCNOTIFIER_OK = 0;

	enum SlArchivingSvcNotifierFunctionCall_Enum
	{
	  FC_PRE,               // function will be called
	  FC_POST               // function was called and has returned
	};

	enum SlArchivingSvcNotifierFunctionId_Enum
	{
	  FI_NONE                       = 0,
	  FI_CREATEARCHIVEINPUT         = 1,
	  FI_CREATEARCHIVE              = 2,
	  FI_CREATEARCHIVEFROMSELECTION = 3,
	  FI_CREATEPLCUPGARCHIVE        = 4,
	  FI_READARCHIVE                = 5,
	  FI_CONVERTTREETOARCHIVE       = 6,
	  FI_CONVERTARCHIVETOTREE       = 7,
	  FI_READARCHIVETREE            = 8,
	  FI_CREATEARCHIVETREE          = 9,
	  FI_CREATEARD                  = 10,
	  FI_MERGEARD                   = 11,
	  FI_GETARCHIVEENTRIES          = 12,
	  FI_DELETETREEENTRIES          = 13,
	  FI_ANALYSEJOBLIST             = 14,
	  FI_EXECUTEJOBLIST             = 15,
	  FI_LOADPTETOPLC               = 16,
	  FI_CREATEPTARCHIVE            = 17,
	  FI_CREATESNW                  = 18,
	  FI_READSNW                    = 19
	};

	// Callback interface
	class ISlArchivingSvcNotifierCb
	{ 
		public:     
            virtual void ArchivingSvcNotification(SlArchivingSvcNotifierFunctionCall_Enum /* enumCallState */, SlArchivingSvcNotifierFunctionId_Enum /* enumFunctionId */, const SlString& /* strInfo */) = 0;
	}; 
	
	class SL_OPERATE_CPP_API SlArchivingSvcNotifier
	{
	public:
		// ***************  public functions  *********************
		SlArchivingSvcNotifier(void);
		SlArchivingSvcNotifier(SlString /* ncu */);
		~SlArchivingSvcNotifier(void);

		SlArchivingSvcNotifierError subscribe(ISlArchivingSvcNotifierCb* /* ArchivingSvcNotification */);
		SlArchivingSvcNotifierError unSubscribe();

	private:
		void*		m_p;
	};



	//////////////////////////////////////////////////////////
    //				SlArchivingSvc Class 			    	//
    //////////////////////////////////////////////////////////
    //	class representing the archive service  		    //
    //	providing access to archives                        //
    //////////////////////////////////////////////////////////
	typedef long SlArchivingSvcError;
	const long SL_ARCHIVINGSVC_OK = 0;
	const long SL_ARCHIVING_GET_ENTRIES_TIMEOUT = 160000;

	enum SupportedArchiveFormat_Enum
	{
		AF_UNDEFINED = 0,
		AF_ARC,							// 840D sl
		AF_DSF							// Sinumerik ONE
	};

	enum SlArchiveType_Enum
	{
		AT_UNDEFINED = 0,
		AT_SETUP = 1,
		AT_PLCUPGRADE = 2,
		AT_PAPERTAPE = 3,
		AT_USER = 4,
		AT_OTHER = 5,
		AT_DSF_SETUP,
		AT_DSF_BACKUP
	};

	enum SlArchivingSvcRequest_Enum
	{
		A_RQ_NOREQUEST = 0,
		A_RQ_LISTCOMPLETED = 1,
		A_RQ_PROGRESS = 2,
		A_RQ_CANCELED = 3,
		A_RQ_INFO = 4,
		A_RQ_ERROR = 5,
		A_RQ_CONFIRMOVERWRITE = 6,
		A_RQ_CONFIRMREADARCHIVE = 7,
		A_RQ_CONFIRM = 8,
		A_RQ_CONFIRMNCUVERSION = 9,
		A_RQ_NEWFILENAME = 10
	};

	enum SlSetupArchivingComponent_Enum
	{
		AC_NOTSPECIFIED = 0,
		AC_NCU = 1,
		AC_NCUANDCOMPENSATIONDATA = 2,
		AC_PLC = 3,
		AC_COMPILECYCLES = 4,
		AC_DRIVESBINARY = 5,
		AC_DRIVESASCII = 6,
		AC_HMI = 7,
		AC_DSF_HMI,
		AC_DSF_SYS,
		AC_DSF_NCK,
		AC_DSF_PLC,
		AC_DSF_DRIVE,
		AC_DSF_NCextend
	};

	struct StatusError
	{
		SlString    message;
		long		number;
	};

	struct SlArchivingSvcStatus
	{
		SlString					ArchiveItem;
		SlVector<StatusError>		Errors;
		bool						OK;
		long						Percentage;
		SlArchivingSvcRequest_Enum	Request;
	};

	// Callback interface
	class ISlArchivingSvcCb
	{
		public:
			virtual void ArchivingSvcActionCanceled() = 0;
			virtual void ArchivingSvcActionCompleted(SlArchivingSvcStatus status) = 0;
			virtual void ArchivingSvcActionProgress(long percentage, SlString archiveItem) = 0;
			virtual void ArchivingSvcStatusChanged(SlArchivingSvcStatus status, bool& confirm) = 0;
	};

	class SL_OPERATE_CPP_API SlArchivingSvc
	{
	public:
		SlArchivingSvc(void);
		SlArchivingSvc(SlString /*ncu*/);
		~SlArchivingSvc(void);
		SlArchivingSvcError cancelAsync(ISlArchivingSvcCb* ArchivingSvcActionCanceled);
		// methods for creating .arc archives
		SlArchivingSvcError createPaperTapeArchiveAsync(SlString archiveFilename, SlVector<SlString>& components, bool iso, bool crlf, ISlArchivingSvcCb* ArchivingSvcActionCompleted, bool reportProgress = false);
		SlArchivingSvcError createPlcUpgradeArchiveAsync(SlString archiveFilename, SlString creator, SlString comment, ISlArchivingSvcCb* ArchivingSvcActionCompleted, bool reportProgress = false);
		SlArchivingSvcError createSetupArchiveAsync(SlString archiveFilename, SlVector<SlSetupArchivingComponent_Enum>& components, SlVector<SlString>& additionalFiles, SlString creator, SlString comment, ISlArchivingSvcCb* ArchivingSvcActionCompleted, bool reportProgress = false);
		SlArchivingSvcError createUserArchiveAsync(SlString archiveFilename, SlVector<SlString>& components, bool includeHmi, bool includeCompileCycles, SlString creator, SlString comment, ISlArchivingSvcCb* ArchivingSvcActionCompleted, bool reportProgress = false);
		// methods reading attributes of archives
		SlArchivingSvcError getComment(SlString archiveFilename, SlString& comment);
		SlArchivingSvcError getCreator(SlString archiveFilename, SlString& creator);
		SlArchivingSvcError getEntries(SlString archiveFilename, SlVector<SlString>& entries);
		SlArchivingSvcError getNcuSystemSoftwareVersion(SlString archiveFilename, SlString& version);
		SlArchivingSvcError getTimeStampInternal(SlString archiveFilename, time_t& timestamp);
		SlArchivingSvcError getType(SlString archiveFilename, SlArchiveType_Enum& type);
        // method for reading in archive file (.arc, .dsf) 
		// .arc will fail on Sinumerik ONE, .dsf will fail on Sinumerik sl
		SlArchivingSvcError readArchiveAsync(SlString archiveFilename, ISlArchivingSvcCb* ArchivingSvcActionCb, bool reportProgress = false, bool reportStatusChanged = false);
		// method for creating archives, archivename extension will be overwritten
		SlArchivingSvcError createArchiveAsync(SlString archiveFilename, SlArchiveType_Enum type, SlVector<SlSetupArchivingComponent_Enum>& components, SlString creator, SlString comment, ISlArchivingSvcCb* ArchivingSvcActionCompleted, bool reportProgress = false);
		SupportedArchiveFormat_Enum getSupportedArchiveFormat();

	private:
		void*		m_p;
	};


  	//////////////////////////////////////////////////////////
    //				SlTraceDataRecorder Class 			    //
    //////////////////////////////////////////////////////////
    //	class representing the tracedatarecorder  		//
    //////////////////////////////////////////////////////////
	typedef long SlTraceDataRecorderError;
	const long SL_TRACEDATARECORDER_OK = 0;
	const long SL_TRACEDATARECORDER_DATA_NOT_COMPLETE = 160000;

	struct SlTraceDataRecorderErrorInterval
	{
		long ErrorNo;
		double TimeOffset;
	};

	struct SlTraceDataRecorderDataset
	{
		double TimeOffset;
		SlVector<int> Ids;
		SlVector<SlValue> Values;
	};

	struct SlTraceDataRecorderBinData
	{			
		SlVector<SlTraceDataRecorderDataset> Data;
		SlVector<SlTraceDataRecorderErrorInterval> Error;
	};

	struct SlTraceDataRecorderErr
	{
		int ErrorNo;
		SlString Message;
	};

	enum SlTraceDataRecorderState
	{
		Stopped = 0,
		WaitingForTrigger = 1,
		Recording = 2
	};

	enum SlTraceDataOptions
	{
		None = 0,
		IncludeHeader = 1,
		IncludeSignalDefinition = 2,
		IncludeHeaderAndSignalDefinition = 3
	};

	class ISlTraceDataRecorderCb
	{
	public:
		virtual void TraceDataRecorderStateChanged(SlTraceDataRecorderState state) = 0;
		virtual void TraceDataRecorderDataCollectionAborted(SlTraceDataRecorderErr error) = 0;
		virtual void TraceDataRecorderDataCollectionCompleted() = 0;
	};

	class ISlTraceDataRecorderDataCb
	{
	public:
		virtual void TraceDataRecorderNewBinaryData(SlTraceDataRecorderBinData DataBin) = 0;
		virtual void TraceDataRecorderNewXmlData(SlString dataXml) = 0;
	};

	class SL_OPERATE_CPP_API SlTraceDataRecorder
	{
	public:
		SlTraceDataRecorder(void);
		SlTraceDataRecorder(SlString xmlSetup, SlString ncu);
		SlTraceDataRecorder(SlString xmlSetup);
		~SlTraceDataRecorder();
		SlTraceDataRecorderError setup(SlString xmlSetup);
		SlString getXmlSetup();
		SlTraceDataRecorderError reset();
		SlTraceDataRecorderError start();
		SlTraceDataRecorderError stop();
		SlTraceDataRecorderError subscribe(ISlTraceDataRecorderCb* pTraceDataRecorderCb, bool stateChanged = false, 
					                       ISlTraceDataRecorderDataCb* pTraceDataRecorderDataCb = NULL, int minimumRecords = 0); 
		SlTraceDataRecorderError unSubscribe();
		SlTraceDataRecorderError getDataBin(SlTraceDataRecorderBinData& binData);
		SlTraceDataRecorderError getDataXml(SlString& xmlData);
		SlString getNcu();
		void setNcu(SlString Ncu);
		bool getReportsXml();
		void setReportsXml(bool reportsXml);
		SlTraceDataOptions getTraceDataOptions();
		void setTraceDataOptions(SlTraceDataOptions options);
		SlTraceDataRecorderState getState();		
		SlString getLastRecordingHeaderXml();
		SlString getLastRecordingSignalsXml();

	private:				
		void*		m_p;
	};


	//////////////////////////////////////////////////////////
    //				SlTripRecorder Class 		     	    //
    //////////////////////////////////////////////////////////
    //	class representing the triprecorder         		//
    //////////////////////////////////////////////////////////
	typedef long SlTripRecorderError;
	const long SL_TRIPRECORDER_OK = 0;

	enum SlTripEvent
	{
		NoEvent = 0,
		HmiStartup,
		HmiShutdown,
		PlcCrash,
		KeyPressed,
		KeyReleased,
		AlarmComing,
		AlarmAcknowledge,
		AlarmGoing,
		OpenWindowArea,
		NcuChannelStatus,
		NcuToolChange,
		NcuToolChangeName,
		NcuOverride,
		WriteVariable,
		NcuConnectionState,
		NcuOperationMode,
		PiCmd,
		FileUpDownload
	};

	class ISlTripRecorderCb
	{
	public:
		virtual void TripLogProgress(int progress) = 0;
		virtual void TripLogCompleted() = 0;
		virtual void CrashLogProgress(int progress) = 0;
		virtual void CrashLogCompleted() = 0; 
	};

	class ISlTripRecorderStateCb
	{
	public:
		virtual void TripRecorderStatusChanged(bool isRecording) = 0;
	};

	class SL_OPERATE_CPP_API SlTripRecorder
	{
	public:
		SlTripRecorder(void);
		SlTripRecorder(SlString username, SlVector<SlTripEvent > events);
		SlTripRecorder(SlString username);
		~SlTripRecorder(void);	
		SlTripRecorderError start();
		SlTripRecorderError start(SlVector<SlTripEvent > events);
		SlTripRecorderError stop();
		SlTripRecorderError reset();
		SlTripRecorderError write(SlString info);
		SlTripRecorderError write(SlString info, SlString username);
		SlTripRecorderError getTripLog(SlString logFilename);
		SlTripRecorderError getTripLogAsync(SlString logFilename, ISlTripRecorderCb* pCb);
		SlTripRecorderError getCrashLog(SlString logFilename);
		SlTripRecorderError getCrashLogAsync(SlString logFilename, ISlTripRecorderCb* pCb);
		SlTripRecorderError cancel();
		SlTripRecorderError subscribe(ISlTripRecorderStateCb* pStateCb);
		SlTripRecorderError unSubscribe();
		SlTripRecorderError getTripEvents(SlVector<SlTripEvent > &events);
		bool getIsRecording();		
		SlString getUsername();

	private:				
		void*		m_p;
	};

	//////////////////////////////////////////////////////////
    //				SlAstSvc Class      		     	    //
    //////////////////////////////////////////////////////////
    //	class representing the AST functionality       		//
    //////////////////////////////////////////////////////////
	typedef long SlAstSvcError;
	const long SL_ASTSVC_OK = 0;

	enum AstMcpRequest
	{
		NONE = 0,            // no action needed, dismiss existing dialog
		CHAN_RESET = 1,      // issue the channel reset for the provided channel
		NC_START = 2,        // issue a NC start (cycle start) in the provided channel
		RESET = 3,           // issue a Reset in the provided channel
		JOGMODE = 4,         // switch the BAG holding the provided channel to JOG
		NOMODEFUNC = 5,      // switch off modal functions teach, or ref
		FEEDENABLE = 6,      // press feed enable key on MCP
		FEEDOVERRIDE = 7,    // set the feedrate override for the channel to a non-zero value
		SPINDLEENABLE = 8,   // press the spindle enable key on the MCP
		REFAXIS = 9,         // requires that the axis to be measured is referenced
	};


	class ISlAstSvcCb
	{
	public:
		virtual void mcpRequest(AstMcpRequest request, int channelNo) = 0;
	};


	class SL_OPERATE_CPP_API SlAstSvc
	{
	public:
		SlAstSvc();
		~SlAstSvc();
		SlAstSvcError subscribe(ISlAstSvcCb*);
		SlAstSvcError unSubscribe(ISlAstSvcCb*);

	private:				
		void*		m_p;
	};


	//////////////////////////////////////////////////////////
    //				SlToolMngmntSvc Class      		        //
    //////////////////////////////////////////////////////////
    // class offering limited tool management functionality //
	// for a specifed TO area								//
    //////////////////////////////////////////////////////////
	typedef long SlToolMngmntSvcError;
	const long SL_TOOLMNGMNTSVC_OK = 0;
	const long SL_TOOLMNGMNTSVC_NOT_AVAILABLE = 160000;

	typedef enum
	{
		NO_ACTION	=	0,
		TOOL_CREATED,				// new tool
		TOOL_DELETED,				// tool deleted
		TOOL_DATA_CHANGED,			// tool data or tool status changed
		TOOL_MOVED					// loaded to, unloaded from, moved within magazine(s)
	} SlToolAction;

	struct SlToolInfo
	{
		SlToolAction	action;
		SlString		toolIdent;
		long			duploNo;	// in case of multi tool duploNo == -1
		long			tNo;
	};

	class ISlNewToolInfoCb
	{
	public:		
		virtual void onNewToolInfo(SlVector<SlToolInfo>) = 0;
	};

	class SL_OPERATE_CPP_API SlToolMngmntSvc
	{
	public:
		SlToolMngmntSvc(int /* TO area number */);
		~SlToolMngmntSvc();
		SlToolMngmntSvcError subscribe(ISlNewToolInfoCb*);
		SlToolMngmntSvcError unSubscribe(ISlNewToolInfoCb*);

	private:				
		void*		m_p;
	};


    //////////////////////////////////////////////////////////
    //		      SlDisplayManager Class 		            //
    //////////////////////////////////////////////////////////
    //	class representing the display manager              //
    //////////////////////////////////////////////////////////
	typedef long SlDisplayManagerError;
	const long SL_DISPLAYMANAGER_OK = 0;

	class ISlDisplayManagerCb
	{
	public:
        virtual void mirrorModeChanged(bool mirrorMode) = 0;
        virtual void displayChanged(const SlString& sDisplay, const SlVector<SlString>& sVisibleApps, const SlVector<SlString>& sVisibleFrames) = 0;
        virtual void displayConfigurationChanged(const SlString& sDisplayConfig) = 0;
	};

	class SL_OPERATE_CPP_API SlDisplayManager
	{
	public:
		SlDisplayManager(ISlDisplayManagerCb*);
		~SlDisplayManager(void);

        SlDisplayManagerError executeAction(const SlString& sAction);
		SlDisplayManagerError showDisplay(const SlString& sDisplay, bool noRefresh = false);
		SlDisplayManagerError getActiveDisplay(SlString& sDisplay);
		SlDisplayManagerError showApp(const SlString& sDestFrame, const SlString& sApp, bool noRefresh = false);
		SlDisplayManagerError showPopup(const SlString& sDestFrame, const SlString& sApp, bool noRefresh = false);
		SlDisplayManagerError hidePopup(const SlString& sApp, bool noRefresh = false);
		SlDisplayManagerError togglePopup(const SlString& sPopupFrame, const SlString& sApp, bool noRefresh = false);
		SlDisplayManagerError showMenu(const SlString& sDestFrame, const SlString& sMenu, bool noRefresh = false);
		SlDisplayManagerError showPopupMenu(const SlString& sDestFrame, const SlString& sMenu, bool noRefresh = false);
        SlDisplayManagerError hidePopupMenu(const SlString& sMenu, bool noRefresh = false);
        SlDisplayManagerError togglePopupMenu(const SlString& sPopupFrame, const SlString& sMenu, bool noRefresh = false);
        SlDisplayManagerError sendCmd(const SlString& sApp, const SlVector<SlString>& sArgs);
        SlDisplayManagerError setMirrorMode(bool mirror, bool noRefresh = false);
        SlDisplayManagerError getMirrorMode(bool& mirror);
		SlDisplayManagerError refreshDisplay();

	private:				
		void*		m_p;
	};

// (C) Copyright Siemens AG, DF MC MTS R&D, 2014-2017. All rights reserved.
