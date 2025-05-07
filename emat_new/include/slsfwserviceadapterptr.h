///////////////////////////////////////////////////////////////////////////////
/*! \file	slsfwserviceadapterptr.h
 *  \author Gerolf Kuehnel
 *  \date   26.11.2003
 *  \brief	Header file for class SlSmartAdapter
 *
 *  This file is part of the HMI Solutionline Service Framework
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SlSmartAdapter_h)
#define SlSmartAdapter_h

#include "slerror.h"
#include "slhmimakros.h"

/*! \class _NoCreateReleaseOnSmartAdapter slsfwserviceadapterptr.h
 *
 *  makes shure, noone can call createInstance / removeInstance directly
*/
template <class TAdapter>
class _NoCreateReleaseOnServiceAdapterPtr : public TAdapter
{
private:
    ///////////////////////////////////////////////////////////////////////////
    // private forbidden functions
    ///////////////////////////////////////////////////////////////////////////
    /*! you are not allowed to call this function, this it is private */
    static TAdapter* createInstance(void){}
    /*! you are not allowed to call this function, this it is private */
    static void removeInstance(TAdapter*){}
};

/*! \class SlSmartAdapter slsfwserviceadapterptr.h
 *  \brief Smartpointer for Serviceadapters
 *
 *  Smartpointer for Serviceadapters. Retrieves a reference to the service
 *  adapter on creation and releases it on destruction. Access the adapter,
 *  using the operator->. In case of security, using this smart pointer,
 *  it is not possible to call createInstance / removeInstance directly. The
 *  smartpointer does that for you.\n
 *  Use the class like you would use a pointer to the adapter
 *
 *  \code
 *  ... fkt(...)
 *  {
 *      SlSmartAdapter<AnyServiceAdapter> pAdapter;
 *      ...
 *      pAdapter->FktInAdapter(...);
 *      ...
 *  }
 *  \endcode
*/
template<class TAdapter>
class SlSfwServiceAdapterPtr
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlSfwServiceAdapterPtr()
     *
     *  Constructor, connects the ServiceAdapter
     */
    SlSfwServiceAdapterPtr() : 
        m_pInstance(0),
        m_nErrorCode(0)
    {
        m_nErrorCode = TAdapter::getObject(m_pInstance);
    }

    /*! \fn ~SlSfwServiceAdapterPtr()
     *
     *  Destructor, disconnects the ServiceAdapter
     */
    ~SlSfwServiceAdapterPtr()
    {
        if(0 != m_pInstance)
        {
            TAdapter::releaseObject(m_pInstance);
        }
        m_pInstance = 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn operator TAdapter*() const
     *  \retval TAdapter* direct access pointer
     *
     *  Converts a SlSfwServiceAdapterPtr object to a TAdapter*.
     */
	operator TAdapter*() const
	{
		return m_pInstance;
	}

    /*! \fn _NoCreateReleaseOnSmartAdapter<TAdapter>* operator->() const
     *  \retval _NoCreateReleaseOnSmartAdapter<TAdapter>* secure member pointer
     *
     *  Returns the secure member pointer
     *  \sa _NoCreateReleaseOnSmartAdapter
     */
	_NoCreateReleaseOnServiceAdapterPtr<TAdapter>* operator->() const
	{
		Q_ASSERT(0 != m_pInstance);
		return static_cast<_NoCreateReleaseOnServiceAdapterPtr<TAdapter>*>(m_pInstance);
	}

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn bool isValid(void)
     *  \retval bool true, if pointer is valid
     */
    bool isValid(void)
    {
        bool bValid = SL_SUCCEEDED(m_nErrorCode);

        if(0 == m_pInstance)
        {
            bValid = false;
        }

        return bValid;
    }

    /*! \fn long getInitError(void)
     *  \retval long return value from object creation
     */
    long getInitError(void)
    {
        return m_nErrorCode;
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    // private members
    ///////////////////////////////////////////////////////////////////////////
    
    TAdapter*   m_pInstance;    /*!< private member to access the Adapter*/
    long        m_nErrorCode;   /*!< error code from init */

    ///////////////////////////////////////////////////////////////////////////
    // not allowed functions
    ///////////////////////////////////////////////////////////////////////////
    /*! strictly vorbidden */
	SlSfwServiceAdapterPtr(SlSfwServiceAdapterPtr& cpy) : m_pInstance(0), m_nErrorCode(0) {}; // avoid cppcheck uninitMemberVarPrivate
    /*! strictly vorbidden */
    //cppcheck-suppress operatorEqVarError
    SlSfwServiceAdapterPtr& operator= (SlSfwServiceAdapterPtr& cpy) {return *this;};
};


#endif // SlSmartAdapter_h
