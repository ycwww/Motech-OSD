///////////////////////////////////////////////////////////////////////////////
/*! \file   slkclogic.h
 *  \author Adam Gorecki
 *  \date   11.05.2011
 *  \brief  Class declaration file for class SlKcLogic
 *
 *  This file is part of the HMI Solutionline, Kinematic Logic Machine/Parameter.
 *
 * (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_KC_LOGIC_H
#define SL_KC_LOGIC_H


#include "slkclogicglobal.h"
#include "slkcbaseobject.h"

#include "slcapdata.h"

#include <QtCore/QObject>
#include <QtCore/QMutex>

class SlKcLogicPrivate;
class SlKcCheckActionCb;
class SlSimConfig;
class NodeInfo;

Q_DECLARE_METATYPE(SlMaBasicLengthUnitEnum);

/*!
 * \class SlKcLogic 
 *
 * This class represents data model of kinematic chains and protection
 * areas of a NC. Obejct of this class will be a singleton.
 */
class SL_KC_LOGIC_EXPORT SlKcLogic : public QObject
{
   Q_OBJECT

   // for reference counting: all function and counter are private here
   // only SlStepSharedPointer<SlKcLogic, SlKcLogic> can access those members
   friend class SlStepSharedPointer<SlKcLogic, SlKcLogic>;

   friend class SlKcLogicPrivate;

   ///////////////////////////
   // PROPERTIES
   ///////////////////////////

   // current basic length unit
   Q_PROPERTY(SlMaBasicLengthUnitEnum basicLengthUnitOfNc READ basicLengthUnitOfNc)

public:
   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC PROPERTIES
   ///////////////////////////////////////////////////////////////////////////

   /*!
    * \fn SlMaBasicLengthUnitEnum basicLengthUnitOfNc() const
    *
    * returns basic length unit of current data in kc logic
    */
   SlMaBasicLengthUnitEnum basicLengthUnitOfNc() const;

   /*!
    * \fn bool collisionAvoidanceAvailable() const
    *
    * returns true if collision avoidance is available, else false.
    */
   bool collisionAvoidanceAvailable() const;

   /////////////////////////////////////////////////////////////////////////////
   // PUBLIC MEMBERS
   /////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn static SlKcLogicPtr Exemplar ()
    *
    *  \retval Pointer to the one and only singleton
    *
    *  Function to get the one and only pointer to the SlKcLogic.
    *
    *  Returned pointer is data model of kinematic chains and protection areas for nc.
    */
   static SlKcLogicPtr Exemplar();

   ///////////////////////////////////////////////////////////////////////////
   // interface to qt model
   ///////////////////////////////////////////////////////////////////////////

   /*!
    * \fn int childCount(qint32 nID) const
    *
    * \param [in] nID      numeric id of element we ask for count of it childrean
    *
    * \return        number of children for element with id \a nID.
    *
    * This function returns number of children for given element \a nID. Is an error occured
    * this function returns -1.
    */
   int childCount(qint32 nID) const;


   /*!
    * \fn QString elementInfo(qint32 nElementID) const
    *
    * \param [in] nElementID     numeric id of element we ask for
    *
    * Returns display string for treeview of given element \a nElementID.
    */
   QString elementInfo(qint32 id) const;

   /*!
    * \fn qint32 childID(qint32 nParentID, int nRow) const
    *
    * \param [in] nParentID   numeric id of parent element
    * \param [in] nRow        child index we ask for
    *
    * \return  numeric id of child element
    * 
    * This function returns numeric id of a child element with parent \a nParentID and index \a nRow.
    * Is an error occured this function returns -1.
    */
   qint32 childID(qint32 nParentID, int nRow) const;

   /*!
    * \fn SlKcGlobalIDList getAllChildren(qint32 nID) const
    *
    * \param [in] nID      numeric id of parent element
    *
    * returns list of id of all children for element.
    */
   SlKcGlobalIDList getAllChildren(qint32 nID) const;

   /*!
    * \fn qint32 parentID(qint32 nChildID) const
    *
    * \param [in] nChildID    numeric id of item we ask for id of parent
    *
    * \return numeric id of parent element.
    *
    * This function returns numeric id of parent element for given item \a nChildID.
    * Is there no parent or an error occurs we return -1.
    */
   qint32 parentID(qint32 nChildID) const;

   /*!
    * \fn void indexOfChild(qint32 nChildID) const
    *
    * \param [in] nChildID    numeric id of item we ask for it index in it parent
    *
    * This function return index of an element \a nChildID inside of it parent element.
    * If an error occurs -1 will be return.
    */
   int indexOfChild(qint32 nChildID) const;

   /*!
    * \fn SlKcGlobalIDList expandedElementList()
    *
    * \return list of global ids for elements to expand
    *
    * this function returns all ids of elements which was marked als expanded
    * are found in new data tree.
    */
   SlKcGlobalIDList expandedElementList();

   /*!
    * \fn void setCollapsedElement(qint32 nId)
    *
    * \param [in] nId   global id of element which would collapsed in tree view
    *
    * this function removes element key from buffer of element which is collapsed in tree view
    */
   void setCollapsedElement(qint32 nId);

   /*!
    * \fn void setExpandedElement(qint32 nId)
    *
    * \param [in] nId      global id of element which would expanded in tree view
    *
    * this function inserts element key into buffer of element which is expanded in tree view
    */
   void setExpandedElement(qint32 nId);

   /*!
    * \fn void updateDataByExpand(qint32 nId)
    *
    * \param [in] nId      global id of element which would expanded in tree view
    *
    * this function check data content of node with \a nId for actuality and updates it
    * if needed.
    * Needed now for directory, drive, and stl file nodes.
    */
   void updateDataByExpand(qint32 nId);

   /*!
    * \fn long statusOfElement(qint32 nId, SlKcErrorID& rnErrorCode) const
    *
    * \param [in] nId               global id of element
    * \param [out] rnErrorCode      reference of string for error code
    *
    * \return 0L if element exists -1L else
    */
   long statusOfElement(qint32 nId, SlKcErrorID& rnErrorCode) const;

   /*!
    * \fn long alarmOfElement(qint32 nId, int& rnAlarm) const
    *
    * \param [in] nId               global Id of element
    * \param [out] rnAlarm          alarm number of element
    *
    * This function returns alarm number for element 
    */
   long alarmOfElement(qint32 nId, int& rnAlarm) const;
   
   /*!
    * \fn bool isPopulated(qint32 nId) const
    *
    * \param [in] nId               global Id of element
    *
    * This function returns state of populate
    */
   bool isPopulated(qint32 nId) const;

   /*!
    * \fn bool isSwitchOn(qint32 nId) const
    *
    * \param [in] nId      global Id of element we ask for
    *
    * \return true if element is a switch and his state is active else false
    *
    * this function check is element with \a nId is a kinematic element of type SWITCH
    * and whether its has active state. This function can only return true for elements
    * from the active area data.
    */
   bool isSwitchOn(qint32 nId) const;

   ///////////////////////////////////////////////////////////////////////////
   // interface to edit data
   ///////////////////////////////////////////////////////////////////////////
   
   /*!
    * \fn SlKcDataAreaType areaTypeOfID(qint32 nId) const
    *
    * \param [in] nId  numeric id of element
    *
    * This function returns area type of element with global id \a nId
    * Is element not found this function returns SL_KC_UNKNOWN_DATA_AREA type
    */
   SlKcDataAreaType areaTypeOfID(qint32 nId) const;

   /*!
    * \fn SlKcTypeList newElementList(qint32 nParentID, SlKcDataTypeArea dataType) const
    *
    * \param [in] nParentID      numerical id of parent element we want to create new element on
    * \param [in] dataType       data type for new elements, kinematic chains or protection area
    * \return list of types of elements
    *
    * this function returns type list for new element which could be created on parent \a nParentID.
    *
    * The types are defined as follow:<br>
    *<TABLE>
    * <tr>
    *    <td>0x00000000</td><td>unknown type</td>
    * </tr>
    * <tr>
    *    <td>0x00000001 - 0x0000000f</td><td>data types, it means kinetic chain, kin. chain element, prot. area, etc.</td>
    * </tr>
    * <tr>
    *    <td>0x00000010 - 0x000000f0</td><td>element types, it means explicit type of element, e.g. kin. chain element types: OFFSET, AXIS_LIN. etc. or prot. area types TOOL, MACHINE etc.</td>
    * </tr>
    * <tr>
    *    <td>0x00000100 - 0x00000f00</td><td>sub type, it means whether the element has special meaning as parallel element</td>
    * </tr>
    */
   SlKcTypeList newElementList(qint32 nParentID, SlKcDataTypeArea dataType) const;

   /*!
    * \fn SlKcBaseObjectPtr newObject(qint32 nParentID, int newType)
    *
    * \param [in] nParentID   numeric id of parent element for new object
    * \param [in] newType     Type for new object to create
    * \return Pointer to data object of new element.
    *
    * This function creates new object of type \a newType and with parent \nParentID.
    * Type is explained in \ref newElementList.
    */
   SlKcBaseObjectPtr newObject(qint32 nParentID, int newType);

   /*!
    * \fn SlKcBaseObjectPtr dataObject(qint32 nElementID) const
    *
    * \param [in] nElementID  numeric id of element
    *
    * This function returns data object with data.
    */
   SlKcBaseObjectPtr dataObject(qint32 nElementID) const;

   /*!
    * \fn long changeData(SlKcBaseObjectPtr ptrObject)
    * 
    * \param [in] ptrObject   object of element with changed data
    *
    * \return 0L if succesful -1L else
    * 
    * This function sets temporary changed data from mask into data model in logic.
    */
   long changeData(SlKcBaseObjectPtr ptrObject);

   /*!
    * \fn long acceptData(SlKcBaseObjectPtr ptrObject)
    *
    * \param ptrObject     object of element with data to apply
    *
    * \return 0L if succesful -1L else
    * 
    * This function applys changed data for an object.
    */
   long acceptData(SlKcBaseObjectPtr ptrObject);

   /*!
    * \fn long cancelData(SlKcBaseObjectPtr ptrObject)
    *
    * \param [in] ptrObject      object of element to reject made changes
    * \return  0L if succesful -1L else
    *
    * This function rejects changes made to an element.
    */
   long cancelData(SlKcBaseObjectPtr ptrObject);

   /*!
    * \fn long deleteElement(qint32 nElementID, bool bWithTail = true, SlKcCheckActionCb *pCheckActionCb = 0)
    *
    * \param [in] nElementID     numeric id of element to delete
    * \param [in] bWithTail      flag to decide whether we delete only the element (false) 
    *                            or we delete element with its successors (true)
    * \param [in] pCheckActionCb callback object for user interaction (gui)
    * \return  0L if succesful -1L else
    *
    * This function deletes given element \a nElementID or given element \a nElementID with its successors (default case).
    */
   long deleteElement(qint32 nElementID, bool bWithTail = true, SlKcCheckActionCb *pCheckActionCb = 0);

   /*!
    * \fn long deleteSelection(const SlKcGlobalIDList& rnElementIDList, SlKcCheckActionCb *pCheckActionCb = 0)
    *
    * \param [in] rnElementIDList      list with numeric ids of elements to delete
    * \param [in] pCheckActionCb       callback object for user interaction (gui)
    * \return  0L if succesful -1L else
    *
    * This function deletes given element list \a rnElementIDList with its successors.
    */
   long deleteSelection(const SlKcGlobalIDList& rnElementIDList, SlKcCheckActionCb *pCheckActionCb = 0);

   /*!
    * \fn long copyElement(qint32 nElementID, bool bWithTail = true, SlKcCheckActionCb *pCheckActionCb = 0)
    *
    * \param [in] nElementID     numeric id of element to copy
    * \param [in] bWithTail      flag to decide whether we copy only the element (false) 
    *                            or we copy element with it successors (true)
    * \param [in] pCheckActionCb callback object for user interaction (gui)
    * \return 0L if succesful -1L else
    *
    * This function copy given element \a nElementID or given element \a nElementID with its successors (default case).
    */
   long copyElement(qint32 nElementID, bool bWithTail = true, SlKcCheckActionCb *pCheckActionCb = 0);

   /*!
    * \fn long copySelection(const SlKcGlobalIDList& rListElementID, SlKcCheckActionCb *pCheckActionCb = 0)
    *
    * \param [in] rListElementID       list with numeric ids of selected elements
    * \param [in] pCheckActionCb       callback object for user interaction (gui)
    * \return 0L if succesful -1L else
    *
    * This function copy selected elements and those children.
    */
   long copySelection(const SlKcGlobalIDList& rListElementID, SlKcCheckActionCb *pCheckActionCb = 0);

   /*!
    * \fn long pasteElement(qint32 nParentID)
    *
    * \param [in] nElementID     numeric id of parent element we paste on
    * \return 0L if succesful -1L else
    *
    * This function pastes containt of system buffer as child of given element \a nParentID.
    */
   long pasteElement(qint32 nParentID, SlKcCheckActionCb *pCheckActionCb = 0);

   /*!
    * \fn long cutElement(qint32 nElementID, bool bWithTail = true)
    *
    * \param [in] nElementID     numeric id of element to cut
    * \param [in] bWithTail      flag to decide whether we cut only the element (false) 
    *                            or we cut element with it successors (true)
    * \return 0L if succesful -1L else
    *
    * This function cuts given element \a nElementID or given element \a nElementID with its successors (default case).
    */
   long cutElement(qint32 nElementID, bool bWithTail = true);

   /*!
    * \fn long cutSelection(const SlKcGlobalIDList& rListElementID, SlKcCheckActionCb *pCheckActionCb = 0)
    *
    * \param [in] rListElementID       list with numeric ids of selected elements
    * \param [in] pCheckActionCb       callback object for user interaction (gui)
    * \return 0L if succesful -1L else
    *
    * This function cuts selected elements and those children. 
    */
   long cutSelection(const SlKcGlobalIDList& rListElementID, SlKcCheckActionCb *pCheckActionCb = 0);

   /*!
    * \fn bool isConnected() const
    *
    * returns malogic connect state to nck
    */
   bool isConnected() const;

   /*!
    * \fn QString ncuName() const
    *
    * returns ncu name according to malogic
    */
   QString ncuName() const;

   /*!
    * \fn SlKcEditAttributes editAttributes(qint32 nId) const
    *
    * \param [in] nId         id of element
    * \return attribute flags with allowed editor operation for element
    *
    * This function returns flags of element to allow editor operations on element like copy or paste etc.
    */
   SlKcEditAttributes editAttributes(qint32 nId) const;

   /*!
    * \fn long successorList(const qint32 nParentID, const SlKcIdCollectMode mode, SlKcGlobalIDList& rIdList) const
    *
    * \param [in] nParentID         global id of parent element
    * \param [in] mode              collecting mode
    * \param [out] rIdList          list of collected ids
    *
    * \return 0L if successful -1L else
    *
    * this function collects all childrens ids according to \a mode.
    */
   long successorList(const qint32 nParentID, const SlKcIdCollectMode mode, SlKcGlobalIDList& rIdList) const;

   /// Returns the element ID of the given type with the given name.
   /**
    * \fn qint32 getByName(const SlKcDataModelID& rModelId, const SlKcElementTypeEnum type, const QString& rsName) const
    *
    * \param [in] rModelId    data model id (area type and data holder id)
    * \param [in] type        element type
    * \param [in] rsName      string with element name
    *
    * @return -1 on failure 
    *
    * returns global id of element
    */
   qint32 getByName(const SlKcDataModelID& rModelId, const SlKcElementTypeEnum type, const QString& rsName) const;

   /// Returns the element ID of the given type with the given NC index.
   qint32 getByNcIndex(const SlKcDataModelID& rModelId, const SlKcElementTypeEnum type, unsigned int index) const;

   /// \brief Get the current values of all relevant model change counters.
   /// \param [out] rKey model change key
   /// \return HMI-sl error code
   long currentModelChangeKey(SlKcModelChangeKey &rKey) const;

   /// \brief Pretend the NC reports an increment in the kinematic model change counter.
   /// \param [out] rKey new model change key
   /// \note Danger, Will Robinson, danger! Only do this if you know what you're doing.
   void incrModelChangeKeyKinematic(SlKcModelChangeKey &rKey);
   /// \brief Set the model change counters as if reported by the NC.
   /// \param [out] rKey new model change key
   /// \note Danger, Will Robinson, danger! Only do this if you know what you're doing.
   void setModelChangeKey(const SlKcModelChangeKey &rModelChangeKey);

   /*!
    * \fn SlKcGlobalIDList activeProtAreas(const SlKcModelChangeKey& rKey = SlKcModelChangeKey()) const
    * 
    * \param [in] rKey        model change counter key for cached value
    * \return list of global ids of protaction which are active.
    *
    * This function returns list of global ids for protection areas which are active.
    */
   SlKcGlobalIDList activeProtAreas(const SlKcModelChangeKey& rKey = SlKcModelChangeKey()) const;

   /// \brief Get inactive protection areas
   /// \param [in] rKey        model change counter key for cached value
   /// \return list of global ids of inactive protection areas
   SlKcGlobalIDList inactiveProtAreas(const SlKcModelChangeKey& rKey = SlKcModelChangeKey()) const;

   /*!
    * \fn long activeStateConditions(SlKcActiveStateCondList& rConditions, const SlKcModelChangeKey& rKey = SlKcModelChangeKey()) const
    *
    * \param [out] rConditions      list with global ids of prot. areas and those active state conditions
    * \param [in] rKey              model change counter key for cached value
    * \return SL_ERR_SUCCESS if ok or SL_ERR_FAIL else
    *
    * returns list of structs with global id of prot. area and its active state condition.
    */
   long activeStateConditions(SlKcActiveStateCondList& rConditions, const SlKcModelChangeKey& rKey = SlKcModelChangeKey()) const;

   /*!
    * \fn SlKcBaseObjectPtr getParentPA(qint32 nPAEId) const
    *
    * \param [in] nPAEId      global id of prot. area element
    *
    * \return object with prot. area data where prot. area element with id \a nPAEId
    *          is build in. or Empty object.
    *
    * this function returns a prot. area object where pae with id \a nPAEId is build in.
    * Wasn't any thing found empty object will be returnd.
    */
   SlKcBaseObjectPtr getParentPA(qint32 nPAEId) const;

   /*!
    * \fn QString onDisableInfo(SlKcEditAttribEnum type, qint32 nId) const
    *
    * \param [in] type        kind of operation which is disabled (copy, paste, etc.)
    * \param [in] nId         global id of element
    *
    * \return  String id with message or empty
    *
    * this function returns message id for that "why" is an operation disabled.
    * Or nothing
    */
   QString onDisableInfo(SlKcEditAttribEnum type, qint32 nId) const;

    ///////////////////////////////////////////////////////////////////////////
   // CAP CALLBACK MEMBER
   ///////////////////////////////////////////////////////////////////////////

   //! Antwort Funktion für den ProtA Dienst.
   /*!
    * \fn void piCap(SlKcCapCB::PiServiceType type, SlCapErrorEnum eError, const QVector<QVariant>& outArgs, const QDateTime& timestamp)
    *
    * Das ist ein Platzhalter für spätere Entwicklung, wenn z.B. ProtA Dienst Fehlermeldungen zurück liefert.
    *
    * reuturn function for cap callback for pi start
    */
   void piCap(int type, SlCapErrorEnum eError, const QVector<QVariant>& outArgs, const QDateTime& timestamp);


   /*!
    * \fn void adviseCap(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResults)
    *
    * 
    *
    * 
    */
   void adviseCap(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResults);

   ///////////////////////////////////////////////////////////////////////////
   // MTS MEMBER
   ///////////////////////////////////////////////////////////////////////////

   /*!
    * \fn void getKcObjectsForSim(const SlKcModelChangeKey& rKey, const SlKcDataModelID& rModelID,
    *                              SlKcSimComponents& rComponents, SlKcSimComponents& rTreeRoot) const
    *
    * \param [in] rKey              model change key for which the data is wanted
    * \param [in] rModelID          data model id for objects
    * \param [out] rComponents      list with of all components of kinematic chains
    * \param [out] rTreeRoot        root of data tree with components as nodes and leafs
    *
    * This function returns in one time all components and kinematic chain as tree.
    */
   virtual void getKcObjectsForSim(const SlKcModelChangeKey& rKey, const SlKcDataModelID& rModelID,
                                   SlKcSimComponents& rComponents, SlKcSimComponentNode& rTreeRoot) const;

   /*!
    * \fn long getSimComponent(SlKcSimComponent& rComponent, qint32 nDataID) const
    *
    * \param [out] rlComponents        components for simulation of element with \a nDataID
    * \param [in] nDataID              data model id for needed component
    *
    * \return SL_ERR_SUCCESS if we could get needed component SL_ERR_FAIL else
    *
    * This function creates a component for simulation for an element with model id \a nDataID
    */
   long getSimComponent(SlKcSimComponents& rlComponent, qint32 nDataID) const;

   /*!
    * \fn QStringList getStlContent(const QString& rsStlName) const
    *
    * \param [in] rsStlName      String with name of stl file
    * \return string list with content of stl file \a rsStlName
    *
    * this function returns string list with stl definition from file with name \a rsStlName.
    */
   QStringList getStlContent(const QString& rsStlName) const;

   /*!
    * \fn long fileAttributes(const QString& rsFileName, NodeInfo& rFileAttrib) const
    *
    * \param [in] rsFileName        string with file name
    * \param [out] rFileAttrib      NodeInfo with found file attributes
    *
    * \return 0L if successful -1L else
    *
    * This function returns file attributes of \a rsFileName.
    */
   long fileAttributes(const QString& rsFileName, NodeInfo& rFileAttrib) const;

   /*!
    * \fn SlKcDataModelID dataModelID(qint32 nElementID) const
    *
    * \param [in] nElementID     global element ID of current element
    *
    * This function returns data model id for an element \a nElementID
    */
   SlKcDataModelID dataModelID(qint32 nElementID) const;

   /*!
    * \fn void setCameraForModel(const SlKcDataModelID& rModelID, const SlKcSimCamera& rCamera)
    *
    * \param [in] rModelID             model id we have to store camera settings
    * \param [in] rCamera              camera settings to store
    *
    * Function stores camera setting coming from graphics view for given model \a rModelID.
    */
   void setCameraForModel(const SlKcDataModelID& rModelID, const SlKcSimCamera& rCamera);

   /*!
    * \fn SlKcSimCamera cameraForModel(const SlKcDataModelID& rModelID) const
    *
    * \param [in] rModelID             model id for which we want camera settings
    * 
    * \return camera settings for a data model.
    * 
    * Function returns camera settings strored for a data model \a rModelID. if there isn't any stored 
    * data we return invalid object.
    */
   SlKcSimCamera cameraForModel(const SlKcDataModelID& rModelID) const;

   /// Whether any chain elements are defined in the given area.
   bool modelExists(SlKcDataAreaType area) const;

   void protA() const;

   /*!
    * \fn QString copyStlToSimUrl(const SlKcDataModelID& rModelID, const QString& rsStlFile, const QString& rsSimUrl, const QString& rsToolFileName=QString()) const
    *
    * \param [in] rModelID          model id for stl files
    * \param [in] rsStlFile         file name to copy. Usal real file path only in case of tool logical file path.
    * \param [in] rsSimUrl          destination path for stl file
    * \param [in] rsToolFileName    real path name of tool stl/npp file in case of tool element else is empty
    *
    * function copy a stl file from nc to destination accessible for mts.
    * \a rsStlFile has usal real file path of 3d file on nc but in case of 3d file of tool there is logical file path.
    * The problem is we need every time real file path. So in case of tool 3d file we get in \a rsToolFileName 
    * real file path of tool 3d data. In all other cases is \a rsToolFileName not defined (.isNull() == true)
    */
   QString copyStlToSimUrl(const SlKcDataModelID& rModelID, const QString& rsStlFile, const QString& rsSimUrl, const QString& rsToolFileName=QString()) const;

   /*!
    * \fn SlKcFileCacheInfoList getActiveStlList(const SlKcDataModelID& rModelID, const SlKcModelChangeKey &rKey, const QString& rsPath) const
    *
    * \param [in] rModelId          model id for stl files
    * \param [in] rKey              model change counter for current model
    * \param [in] rsPath            base path for file cache
    *
    * \return list with pairs of stl files including in model \a rModelID and its cache destination
    *
    * This function returns list of all stl files in model \a rModelID and its path in file cache.
    * At the moment in this function implemented only for active data area.
    */
   SlKcFileCacheInfoList getActiveStlList(const SlKcDataModelID& rModelID, const SlKcModelChangeKey &rKey, const QString& rsPath) const;

   /*!
    * \fn QStringList getCachedStlList(const SlKcDataModelID& rModelID, const QString& rsPath) const;
    *
    * \param [in] rModelId          model id for stl files
    * \param [in] rsPath            base path for file cache
    *
    * \return list of all stl files found in cache directories
    *
    * This function returns a list of all stl files found in cache directories as full pathname.
    * At the moment in this function implemented only for active data area.
    */
   QStringList getCachedStlList(const SlKcDataModelID& rModelID, const QString& rsPath) const;

   /*!
    * \fn QString uniqueCacheFilename(const SlKcDataModelID& rModelID, const SlKcModelChangeKey &rKey, const QString& rsFilename) const
    *
    * \param [in] rModelId          model id for stl files
    * \param [in] rKey              model change counter for current model
    * \param [in] rsFilename     source file name
    * \return                    file name with padded checksum or empty string
    *
    *  This function computes a checksum of the given filename and returns a filename padded with this checksum.
    *  At the moment in this function implemented only for active data area, because only those are cached.
    */
   QString uniqueCacheFilename(const SlKcDataModelID& rModelID, const SlKcModelChangeKey &rKey, const QString& rsFilename) const;

   /*!
    * \fn long getNppComponentsForSim(const QString& rsCachedFileName, const SlKcSimComponent& rNppFile,
    *                                 SlKcSimComponents& rComponents, SlKcSimComponentNode& rTreeRoot) const
    *
    * \param [in] rsCachedFileName        name of cached npp file to read
    * \param [in] rNppFile                sim component of npp file needed for correct naming of npp content
    * \param [out] rComponents            list of components for simulation from npp file
    * \param [out] rTreeRoot              tree structure of npp content
    *
    * \return  SL_ERR_SUCCESS if all went well SL_ERR_FAIL else
    *
    * This function read content of given npp file \a rsCachedFileName 
    * interpret it and retruns componets for simulation as list and tree
    */
   long getNppComponentsForSim(const QString& rsCachedFileName, const SlKcSimComponent& rNppFile,
                               SlKcSimComponents& rComponents, SlKcSimComponentNode& rTreeRoot) const;

   /// \brief Whether we have already read the data for the given key.
   /// \details If false, we don't know the key (yet), or a reload is already in progress.
   bool hasReadDataForModelChangeKey(const SlKcModelChangeKey& rKey) const;

   /*!
    * \fn SlKcLogicPtr getSimCopyOfLogic() const
    *
    * This function creates copy object of active data from current logic.
    * This copy object is for simulation and has to be deleted there.
    */
   SlKcLogicPtr getSimCopyOfLogic() const;

   /// \brief Reloads switch data from NC directly without waiting.
   /// \note Use this function for SNCK only.
   void updateSwitchData(const SlKcModelChangeKey& rKey);

   /*!
    * \fn void updateSwitchData()
    *
    * This function has to be called if update of switch states is necessary.
    * NK_SWITCH will be reread from nc or snc.
    */
   void updateSwitchData();

   /// \brief Reloads all data from NC directly without waiting.
   /// \note Use this function for SNCK only.
   void reloadNcDataDirectly(const SlKcModelChangeKey& rKey);

   ///////////////////////////////////////////////////////////////////////////
   // FUNCTIONS FOR KIN. TRANSFORMATIONS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    * \fn SlKcBaseObjectPtr kinematicDataObjectByName(const QString& rsName) const
    *
    * \param [in] rsName  name of kin. element from active data (nc)
    *
    * This function returns data object with data of a kinematic chain element from nc data
    * model or empty object if nothing found.
    */
   SlKcBaseObjectPtr kinematicDataObjectByName(const QString& rsName) const;

   /*!
    * \fn long getKinElementLocation(const QString& rsElementName, const QString& rsTableChainEndName, 
    *                                const QString& rsToolChainEndName, QString& rsChainName) const
    *
    * \param [in] rsElementName           name of kinematic chain element we look for
    * \param [in] rsTableChainEndName     name of last kin. chain element of kinematic chain for table
    * \param [in] rsToolChainEndName      name of last kin. chain element of kinematic chain for tool
    * \param [out] rsChainName            name of last kin. chain element of kin. chain where \a rsElementName was found
    *                                     is empty if not found
    *
    * \return  0L if succesful or SL_ERR_FAIL else
    *
    * This function search name \a rsElementName in table and tool chain. Is nothing found empty string
    * will be returned or either \a rsTableChainEndName or \a rsToolChainendName.
    * if \a rsElement is in both chains we return name of first chain we find it, \a rsTableChainEndName.
    *
    * this function works only on active data, nc data, not in examples or net/usb.
    */
   long getKinElementLocation(const QString& rsElementName, const QString& rsTableChainEndName, 
                              const QString& rsToolChainEndName, QString& rsChainName) const;


   /*!
    * \fn long getToolDirection(const QString& rsToolChainEndName, double &rnDirX, double& rnDirY, double& rnDirZ) const
    *
    * \param [in] rsToolChainEndName         name of last element tool kinematic chain
    * \param [out] rnDirX                    x value of tool direction
    * \param [out] rnDirY                    y value of tool direction
    * \param [out] rnDirZ                    z value of tool direction
    *
    * \return -1 if end element of tool chain not found or rnDir vector is shorter than 1.0 else 0
    *
    * This function traverse through kinematic chain and use every constant rotation on given 
    * vector rnDirX, rnDirY, rnDirZ. Given direction rnDir must have at least length of 1.0
    */
   long getToolDirection(const QString& rsToolChainEndName, double &rnDirX, double& rnDirY, double& rnDirZ) const;

   /*!
    * \fn long getToolRotation(const QString& rsToolChainEndName, double &rnDirX, double& rnDirY, double& rnDirZ, double& rnAngle) const
    *
    * \param [in] rsToolChainEndName         name of last element tool kinematic chain
    * \param [out] rnDirX                    x value of tool rotation
    * \param [out] rnDirY                    y value of tool rotation
    * \param [out] rnDirZ                    z value of tool rotation
    * \param [out] rnAngle                   angle value of tool rotation
    *
    * \return -1 if end element of tool chain not found or rnDir vector is shorter than 1.0 else 0
    *
    * This function traverse through kinematic chain and use every constant rotation on given 
    * vector rnDirX, rnDirY, rnDirZ. Given direction rnDir must have at least length of 1.0
    */
   long getToolRotation(const QString& rsToolChainEndName, double &rnDirX, double& rnDirY, double& rnDirZ, double& rnAngle) const;

   /*!
    * \fn long getToolTranslation(const QString& rsToolChainEndName, double &rnTransX, double& rnTransY, double& rnTransZ) const
    *
    * \param [in] rsToolChainEndName         name of last element tool kinematic chain
    * \param [out] rnTransX                  x value of tool translation
    * \param [out] rnTransY                  y value of tool translation
    * \param [out] rnTransZ                  z value of tool translation
    *
    * \return -1 if end element of tool chain not found or rnDir vector is shorter than 1.0 else 0
    *
    * This function traverse through kinematic chain and adds every constant offset on given 
    * vector rnTransX, rnTransY, rnTransZ.
    */
   long getToolTranslation(const QString& rsToolChainEndName, double &rnTransX, double& rnTransY, double& rnTransZ) const;

   /*!
    * \fn long getOffset(const QString& rsStartElemName, const QString& rsEndElemName, double& rnOffX, double& rnOffY, double& rnOffZ) const
    *
    * \param [in] rsStartElemName   name of start element in kin. chain. can be empty so we start with root
    * \param [in] rsEndElemName     name of end element in kin. chain. cannot be empty and be a child of start element
    * \param [out] rnOffX           x coordinate of calculated offset
    * \param [out] rnOffY           y coordinate of calculated offset
    * \param [out] rnOffZ           z coordinate of calculated offset
    *
    * \return  SL_ERR_SUCCESS if we could calculate an offset vector else SL_ERR_FAIL.
    *
    * this function calculates offset between given start and end element in chain.
    */
   long getOffset(const QString& rsStartElemName, const QString& rsEndElemName, double& rnOffX, double& rnOffY, double& rnOffZ) const;

public slots:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC SLOTS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    * \fn void adviseCap(SlKcCapCB::PiServiceTypes type, SlCapErrorEnum eError, const QVariant& vData, const SlCapSupplementInfoType& suppl)
    *
    * 
    *
    * reuturn function for cap callback for pi start
    */
   void adviseCap(int type, int eError, const QVariant& vData/*, const SlCapSupplementInfoType& suppl*/);

   //! notification from file service about mount
   /*!
    * \fn void logicalDriveMounted(const QString& rsPath)
    *
    * \param [in] rsPath      path to logical drive been mounted
    *
    * This slot has to be connected to file service object in network/usb area object
    * to get information about mount of logical drives.
    */
   void logicalDriveMounted(const QString& rsPath);

   //! notification from file service about unmount
   /*!
    * \fn void logicalDriveUnmounted(const QString& rsPath)
    *
    * \param [in] rsPath      path to logical drive been unmounted
    *
    * This slot has to be connected to file service object in network/usb area object
    * to get information about unmount of logical drives.
    */
   void logicalDriveUnmounted(const QString& rsPath);

   //! rebuild data tree and notify all listener
   /*!
    * \fn void updataDataTree()
    *
    * This function builds new data tree and emit changed signals.
    */
   void updateDataTree();
   
   /*!
    * \fn void currentIdChangedSlot(const qint32 nID)
    *
    * \param [in] nID      global id of element which became current
    *
    * slot to set element as current one in qt model
    */
   void currentIdChangedSlot(const qint32 nID);

   /// \brief Sets the maximum cache size.
   /// \see startCache
   void setMaxCacheSize(int nMaxCacheSize);

   /*!
    * \fn void startCache()
    *
    * this function starts caching of kinematic data.
    */
   void startCache();

   /*!
    * \fn void stopCache()
    *
    * this function stops caching of kinematic data.
    * already cached data will be deleted.
    */
   void stopCache();

signals:
   ///////////////////////////////////////////////////////////////////////////
   // SIGNALS OF INTERFACE TO EDIT DATA
   ///////////////////////////////////////////////////////////////////////////
   /*!
    * \fn void errorStatusSignal(const QString& rsMessage)
    *
    * \param [in] rsMessage      string with error message
    *
    * signal emitted if an error occurs in data consistence check
    */
   void errorStatusSignal(const QString& rsMessage);

   /*!
    * \fn void errorMessage(const QString& rsMessage)
    *
    * \param [in] rsMessage      string with error message
    *
    * signal emitted if an error occurs in data consistence check
    */
   void errorMessageSignal(const QString& rsMessage);

   /*!
    * \fn void datamodelChangedSignal(const qint32 nCurrentId = -1)
    *
    * signal emitted if data model has changed and datatree has to be rebuild.
    * this signal implys reset of qt model.
    */
   void datamodelChangedSignal(const qint32 nCurrentId = -1);

   /// @brief Emitted when an element in $AN_COLL_STATE[] has changed.
   /// @note Not emitted if datamodelChangedSignal is emitted.
   void activationChangedSignal();

   /// @brief Emitted when an element in $AN_COLL_STATE_COND[] has changed.
   /// @note Not emitted if datamodelChangedSignal is emitted.
   void activationConditionChangedSignal();

   /*!
    * \fn void attribChangedSignal(const qint32 nId, const int nItems)
    *
    * \param [in] nId         global id of element would be changed
    * \param [in] nItems      item flags of element which have changed
    *
    * signal to inform world of changing an element
    */
   void attribChangedSignal(const qint32 nId, const int nItems);

   /*!
    * \fn void modelAlarmChangedSignal()
    *
    * signal emited due changing nc alarm by model changed counter
    */
   void modelAlarmChangedSignal();

   /*!
    * \fn void expandElementAndAncestorsSignal(const qint32 nId)
    *
    * \param [in] nId      global id of element which tiggered alarm
    *
    * signal to expand element and its ancestors.
    */
   void expandElementAndAncestorsSignal(const qint32 nId);

   /*!
    * \fn void connectionToNcLostSignal()
    *
    * Signal to post nck connection lost event
    */
   void connectionToNcLostSignal();

protected:
   ///////////////////////////////////////////////////////////////////////////
   // PROTECTED ACCESSORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlKcLogicPrivate* data() const
    *
    *  \return the pointer to the private kc logic
    */
   SlKcLogicPrivate* data() const;

private:   
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   SlKcLogicPrivate*  m_pData;    //!< d-pointer pattern

   static QMutex m_exemplarMutex;

   QAtomicInt  m_refCnt;          //!< the reference counter
  
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE CREATORS TO AVOID UNCONTROLED INSTATIATION AND DELETION
   ///////////////////////////////////////////////////////////////////////////
   
   /*! 
    * \fn SlKcLogic(void)
    *
    * Default constructor
    */
   SlKcLogic();

   /*!
    * \fn virtual ~SlKcLogic(void)
    *
    * Default destructor
    */
   virtual ~SlKcLogic(void);

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlKcLogic (const SlKcLogic& rCopy);

   /*! assignment operator not allowed */
   SlKcLogic& operator=(const SlKcLogic& rCopy);

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBER
   ///////////////////////////////////////////////////////////////////////////
   
   /*!
    *  \fn void addRef (void)
    *  
    *  Adds a reference to this shared data object.
    */
   void addRef (void)
   {
      m_refCnt.ref();
   }

   /*!
    *  \fn void removeRef (void)
    *  
    *  Removes a reference from this shared data object. If reference counter
    *  decreases to 0 it destroys this shared data object. 
    */
   void removeRef (void)
   {
      Q_ASSERT(0 < m_refCnt);

      bool bNonZero = m_refCnt.deref();
      if (false == bNonZero)
      {
         delete this;
      }
   }

   /*!
    * \fn bool isValid() const
    * 
    * \return true if data model has been initialized successfuly, false else
    *
    */
   bool isValid() const;

   /*!
    * \fn void setValid (bool bValid)
    *
    * \param [in] bValid   state value of logic to set
    *
    * This function sets status of kc logic.
    */
   void setValid(bool bValid);

   /*!
    * \fn void init()
    *
    * initializing of data model.
    */
   void init();

   /*!
    * \fn void connectToNc();
    *
    * This function sets active channel to nc state tracker 
    * for initialising.
    */
   void connectToNc();

   /*!
    * \fn void makeSafetyReloadSingleShot()
    *
    * This funcion registers and starts a single shot to reloadNcData.
    */
   void makeSafetyReloadSingleShot();

private slots:
   //////////////////////////////////////////////////
   // PRIVATE SLOTS
   //////////////////////////////////////////////////
   /*!
    * \fn void receiverRelaodSingleShot()
    *
    * this function is called as single shot to reload nc data if 
    * reload data is needed in a period of 500 msec and doesn't happen
    * yet.
    */
   void receiverReloadSingleShot();

   /*!
    * \fn void reloadNcData(const SlKcModelChangeKey& rKey)
    *
    * \param [in] rKey                          model change key for which we want reload data
    *
    * slot for reloading collision avoidness data of nc without scaning for
    * 3d files on nc.
    */
   void reloadNcData(const SlKcModelChangeKey& rKey);

   /*!
    * \fn void updateToolStlFiles()
    * 
    * slot for updating informations and data of tool prot. files from nc file system
    */
   void updateToolStlFiles();

   /// Read $AN_COLL_STATE[] from NC.
   void readActivationStates();

   /// Read $AN_COLL_STATE_COND[] from NC.
   void readActivationStateConditions();

}; // <-- class SlKcLogic

/*!
 * \class SlKcCheckActionCb 
 *
 * This class represents data model of kinematic chains and protection
 * areas of a NC. Obejct of this class will be a singleton.
 */
class SL_KC_LOGIC_EXPORT SlKcCheckActionCb
{
public:
   ///////////////////////////////////////////////////////////////////////////
   // ENUMS
   ///////////////////////////////////////////////////////////////////////////

   enum SlKcCheckCbReturns
   {
     SlKcCbRetActionOk,
     SlKcCbRetCancel,
     SlKcCbRetWithTailOk,
     SlKcCbRetWithoutTailOk,
     SlKcCbRetSkipAct,
     SlKcCbRetSkipAll,
     SlKcCbRetOvrAct,
     SlKcCbRetOvrAll,
     SlKcCbRetPasteNext,
     SlKcCbRetPasteParallel,
     SlKcCbRetPasteCopy,
     SlKcCbRetPasteLink,
     SlKcCbRetPasteNextLink,
     SlKcCbRetPasteParallelLink,
     SlKcCbRetImperialUnit,
     SlKcCbRetMetricalUnit,
     SlKcCbRetNotImplemented
   };

   enum SlKcCheckCbMessageTypes
   {
      SlKcCbDeleteQuestion1,
      SlKcCbDeleteQuestion2,
      SlKcCbDeleteQuestion3,
      SlKcCbDeleteQuestion4,
      SlKcCbDeleteQuestion5,
      SlKcCbDeleteQuestion6, // ja nein Messagebox for delete

      SlKcCbCopyExistingFile, // SlKcCbCopyFileQuestion1,
      SlKcCbOverwriteExistingModel,//!< for pasting data into an existing model
      SlKcCbOverwriteExistingFile, // SlKcCbCopyFileQuestion1,
      SlKcCbCopyFileQuestion2,

      SlKcCbCopyQuestion1,
      SlKcCbCopyQuestion2,          //!< ask for data ini file name only
      SlKcCbCopyQuestion3,          //!< ask for data ini file name and 3d subdirectory name
      SlKcCbCopyQuestion4,          //!< ask for 3d subdirectory name only
      SlKcCbCopyQuestion5,          //!< ask for data npp file name only


      SlKcCbCopyFileFailed1,
      SlKcCbCopyFileFailed2,
      SlKcCbCopyFileFailed3,        //!< error message for copy stl files not directly into mm or inch directory
      SlKcCbDeleteDirNotEmpty,
      SlKcCbFileSysDeleteFailedFile,         //!< error message for delete failed because of file system
      SlKcCbFileSysDeleteFailedDir,          //!< error message for delete failed because of file system
      SlKcCbFileSysDeleteFailedDirNotEmpty,  //!< error message for delete failed because of file system
      SlKcCbFileSysSaveFailedFile            //!< error message for saving failed because of file system
   };

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   
   /*! 
    * \fn SlKcCheckActionCb(void)
    *
    * Default constructor
    */
   SlKcCheckActionCb(void)
   {
   }

   /*!
    * \fn virtual ~SlKcCheckActionCb(void)
    *
    * Default destructor
    */
   virtual ~SlKcCheckActionCb(void)
   {
   }

   /////////////////////////////////////////////////////////////////////////////
   // PUBLIC MEMBERS
   /////////////////////////////////////////////////////////////////////////////

   /*!
    * \fn virtual SlKcCheckCbReturns askDeleteElement(const QString& rszDelName, bool bWithTail)
    *
    * \param [in] rszDelName     name of the element to delete
    * \param [in] bRecourse      flag to decide whether we delete only the element (false) 
    *                            or we delete element with its successors (true)
    *
    * \return \sa SlKcCheckCbReturns
    *
    * This function asks delete the given element
    */
   virtual SlKcCheckCbReturns askDeleteElement(SlKcCheckCbMessageTypes type, const QString& rszDelName, const QString& rszDelContext, const QString& rszMessage)
   {
      return SlKcCbRetNotImplemented;
   }

   /*!
    * \fn virtual SlKcCheckCbReturns askOverwriteElement(const QString& rszOldName, QString& rszNewName)
    *
    * \param [in]  rszOldName     original file name
    * \param [out] rszNewName     new file name
    *
    * \return \sa SlKcCheckCbReturns
    *
    * This function asks to overwrite, skip or rename the given element
    */
   virtual SlKcCheckCbReturns askOverwriteElement(const QString& rszOldName, QString& rszNewName)
   {
      return SlKcCbRetNotImplemented;
   }

   /*!
    * \fn virtual SlKcCheckCbReturns askPasteElementNextOrParallel(bool bExisting, bool bNextIsLeaf, 
    *                                                              bool bParallelIsLeaf, bool bExistsParallel,
    *                                                              bool bRecursivePaste)
    *
    * \param [in] bExisting         name of element to paste exists already
    * \param [in] bNextIsLeaf       parent of paste hasn't next element
    * \param [in] bParallelIsLeaf   parent of paset hasn't parallel element
    * \param [in] bExistsParallel   there is no need for asking about next or parallel
    * \param [in] bRecursivePaste   do we paste an element into him self or its follower
    *
    * \return \sa SlKcCheckCbReturns
    *
    * This function asks how to paste elements as next or parallel
    */
   virtual SlKcCheckCbReturns askPasteElementNextOrParallel(bool bExisting, bool bNextIsLeaf, 
                                                            bool bParallelIsLeaf, bool bExistsParallel,
                                                            bool bRecursivePaste)
   {
      Q_UNUSED(bExisting)
      Q_UNUSED(bNextIsLeaf)
      Q_UNUSED(bParallelIsLeaf)
      Q_UNUSED(bExistsParallel)
      Q_UNUSED(bRecursivePaste)

      return SlKcCbRetNotImplemented;
   }

   /*!
    * \fn SlKcCheckCbReturns askCopyFile(SlKcCheckCbMessageTypes type, QString& rszFileName) const
    *
    * \param [in] type           type of message
    * \param [in\out] rszFileName    name of copied file
    *
    * \return status of answer
    *
    * This function is used for interact with user in case of copying stl files
    */
   virtual SlKcCheckCbReturns askCopyFile(SlKcCheckCbMessageTypes type, QString& rszFileName) const
   {
      return SlKcCbRetNotImplemented;
   }

   /*!
    * \fn SlKcCheckCbReturns infoMessage(SlKcCheckCbMessageTypes type, const QString& sName = QString()) const
    *
    * \param [in] type           type of message
    * \param [in] sName          optional element name for info message
    *
    * this function gives info message for user
    */
   virtual SlKcCheckCbReturns infoMessage(SlKcCheckCbMessageTypes type, const QString& sName = QString()) const
   {
      Q_UNUSED(sName);
      return SlKcCbRetNotImplemented;
   }

   /*!
    * \fn SlKcCheckCbReturns askCopyElement(SlKcCheckCbMessageTypes type, const QString& rszMessage) const
    *
    * \param [in] type           type of message
    * \param [in] rszMessage     text id of message
    *
    * \return status of answer
    *
    * This function is used for interact with user in case of copying elements
    */
   virtual SlKcCheckCbReturns askCopyElement(SlKcCheckCbMessageTypes type, const QString& rszFileName) const
   {
      return SlKcCbRetNotImplemented;
   }

   /*!
    * \fn SlKcCheckCbReturns askCopyElements(SlKcCheckCbMessageTypes type, QString& rszModelFile, QString& rsz3DDir) const
    *
    * \param [in] type                 type of question
    * \param [in] rszModelFile         name of ini data file we want to copy
    * \param [in] rsz3DDir             name of stl file subdirectory
    *
    * \return status of answer
    *
    * This function is used for interact with user in case of copying elements into a directory or a drive.
    * We get in \a rszModelFile and \a rsz3DDir names for ini data file and sub directory name for stl files.
    * if we preset those variables our settings will appear in user dialog as default settings.
    * With \a type we can decide whether we ask for ini file or 3d directory or both.
    */
   virtual SlKcCheckCbReturns askCopyElements(SlKcCheckCbMessageTypes type, QString& rszModelFile, QString& rsz3DDir) const
   {
      return SlKcCbRetNotImplemented;
   }

   /*!
    * \fn virtual void startProgress( ) const
    *
    * This function is used to showProgressBar in dialog.
    */
   virtual void startProgress(const QString& rsCaption) const
   {
      Q_UNUSED(rsCaption);
   }

   /*!
    * \fn virtual void setProgressValue(int nProgressValue, const QString& rsParam = QString()) const
    *
    * \param [in] nProgressValue     reached progress state
    * \param [in] rsParam            extra parameter to display with message
    *
    * This function is used to set new value on progress bar in dialog.
    */
   virtual void setProgressValue(int nProgressValue, const QString& rsParam = QString()) const
   {
      Q_UNUSED(nProgressValue);
      Q_UNUSED(rsParam);
   }

   /*!
    * \fn virtual void stopProgress( ) const
    *
    * This function is used to hideProgressBar in dialog.
    */
   virtual void stopProgress( ) const
   {
   }

protected:
   ///////////////////////////////////////////////////////////////////////////
   // PROTECTED ACCESSORS
   ///////////////////////////////////////////////////////////////////////////

private:   
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlKcCheckActionCb (const SlKcCheckActionCb& rCopy);

   /*! assignment operator not allowed */
   SlKcCheckActionCb& operator=(const SlKcCheckActionCb& rCopy);

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBER
   ///////////////////////////////////////////////////////////////////////////

}; // <-- class SlKcCheckActionCb


#endif // SL_KC_LOGIC_H
