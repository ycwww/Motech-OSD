
#ifndef SL_REGISTER_METATYPE_H_INCLUDED
#define SL_REGISTER_METATYPE_H_INCLUDED


/*! This template defines a new class, which registers in its constructor the type T/strClassName for Qt; 
    and unregisters it in its destructor. 
*/
template<class T>
class SlMetaTypeRegistrator { 
public:
  
  SlMetaTypeRegistrator(const char* strClassName)
  { 
    for (int j = 0; j < 1024; ++j)
    {
      m_strClassName[j] = strClassName[j];
      if (strClassName[j] == '\0') { break; }
    }
    m_iId = qRegisterMetaType<T>(m_strClassName);
    qDebug("qRegisterMetaType<%s>(%s) returns %d", m_strClassName, m_strClassName, m_iId);
  }

  ~SlMetaTypeRegistrator() 
  { 
    qDebug("QMetaType::unregisterType(%s)", m_strClassName); 
    QMetaType::unregisterType(m_iId);
  }

  char m_strClassName[1024];
  int  m_iId;
};


#define COMBINE1(X,Y) X##Y  // helper macro
#define COMBINE(X,Y) COMBINE1(X,Y)

/*! Use this makro in a CPP file to create a global object, so that the type T/ClassNameString will be registered for QT when the DLL is loaded; 
    and the type will be unregistered when the DLL is unloaded.
    Usage:
    SL_REGISTER_QT_METATYPE(SlSuDbSiParameters, "SlSuDbSiParameters")
    It is strongly recommended to have _one_ CPP-file for each DLL, where all the type are listed, which need to be registered for QT;
    otherwise the makro might fail, because intern it uses __LINE__ to generate unique names within one DLL. 
*/
#define SL_REGISTER_QT_METATYPE(T, ClassNameString) SlMetaTypeRegistrator<T> COMBINE(SlMetaTypeRegistrator_,__LINE__)(ClassNameString);

#endif
