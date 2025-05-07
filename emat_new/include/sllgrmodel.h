
///////////////////////////////////////////////////////////////////////////////
/*! \file   slpaintmodel.h
 *  \author Holger Renn
 *  \date   17.07.2007
 *  \brief  Header file for class SlLgrModel, SlLgrShape, SlLgrPoint, SlLgrLine, SlLgrCircle, SlLgrZoomArea
 *
 *
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PAINT_MODEL_INCLUDE
#define SL_PAINT_MODEL_INCLUDE

#include "sllgrdata.h"
#include <QtGui/QPalette>
#include <QtGui/QPainter>
#include <QtCore/QTextStream>
#include <QtGui/QPainterPath>


//Added by qt3to4:
#include <QtGui/QPaintEvent>



//#define SL_PAINT_MODEL
#ifdef _SL_PAINT_MODEL
#  define SL_PAINT_MODEL_EXPORT Q_DECL_EXPORT
#else
#  define SL_PAINT_MODEL_EXPORT Q_DECL_IMPORT
#endif


#define INTMULTIPLIER_SMALL 100
#define INTMULTIPLIER_BIG 1000000



/*! \class SlLgrZoomArea slpaintmodel.h
 *  \brief The Class holds the zoomarea-data for the SlLineGraphicWidget
 */
class SL_PAINT_MODEL_EXPORT SlLgrZoomArea
{

public:
    /*! \fn SlLgrZoomArea(void)
     *
     *  Constructor
     */
   SlLgrZoomArea(void);

   /*! \fn ~SlLgrZoomArea(void)
     *
     *  Destructor
     */
   virtual ~SlLgrZoomArea();

   /*! \fn void checkForZoomArea(VectorType tStart, VectorType tEnd)
     *   \param tStart point to consider in zoomarea
    *   \param tEnd point to consider in zoomarea
    *
     *  funktion takes two point to consider in zoomarea
     */
   void checkForZoomArea(VectorType tStart, VectorType tEnd, ZoomEnum ZoomElementType);

   /*! \fn ZoomAreaType isZoomArea()
     *   \retval ZoomAreaType  zoomarea defined with two point in a struct type
    *
    *   function returns the values for zoomarea of the ZOOM_ELEMENTS
     *
     */
   ZoomAreaType isZoomArea(); //Rückgabe des Zoombereiches

   /*! \fn ZoomAreaType isCompleteArea()
    *   \retval ZoomAreaType  zoomarea defined with two point in a struct type
    *
    *   function returns the values for zoomarea of all elements
    *
    */
   ZoomAreaType isCompleteArea(); //Rückgabe des Zoombereiches

   /*! \fn void clearZoomArea()
    *
    *
    *   function delete the values for zoomareas
    *
    */
   void clearZoomArea();
protected:

private:
   ZoomAreaType m_tZoomArea;
   ZoomAreaType m_tCompleteArea;
   int m_intCntZoomElements;

};

/*! \class SlLgrShape slpaintmodel.h
 *  \brief SlLgrShape ist the baseclass for all the elements of SlLineGraphicWidget
 *
 *
 */
class SL_PAINT_MODEL_EXPORT SlLgrShape
{
public:

   SlLgrShape(void);
   virtual ~SlLgrShape();

   /*! \fn virtual void draw(QPainter* pQPainter) = 0
     *   \param pQPainter  QPainter to draw on
     *
     *   this is a pure virtual function of the baseclass
     */
   virtual void draw(QPainter* pQPainter, QPalette rQPalette, double rScaleFact) = 0;
   
   
   void getColor(ColorEnum rColor, QPen* pQPen);
   void getLineType(LineEnum rLineType, QPen* pQPen);
   
   ZoomAreaType m_tZoomArea;
   QPainter* m_Painter;
   QPen m_Pen;
   QPalette m_Palette;
   double m_dScaleFact;
   int mIntMultiplier;
   int coordinateSystem;
protected:

private:


};

/*! \class slCircle slpaintmodel.h
 *  \brief The Class holds Data for the paintwidget
 */

class SL_PAINT_MODEL_EXPORT SlLgrCircle : public SlLgrShape
{

public:

   /*! \fn SlLgrCircle::SlLgrCircle(VectorType start, VectorType middle, VectorType end, DirectionEnum DirectionEnum, bool isFullCircle, SlLgrZoomArea* pZoomArea)
     *
     *  Constructor
     */
   SlLgrCircle::SlLgrCircle(VectorType start, VectorType middle, VectorType end, DirectionEnum DirectionEnum, bool isFullCircle, CircleEnum CircleType, LineEnum LineType, ColorEnum Color, ZoomEnum ZoomElementType , SlLgrZoomArea* pZoomArea, int coordinateType);
   
   virtual ~SlLgrCircle();
   /*! \fn virtual void draw(QPainter* pQPainter)
     *
     *
     */
   virtual void draw(QPainter* pQPainter, QPalette rQPalette, double rScaleFact);

   /*! \fn double getAngle(VectorType tPoint, VectorType tMidPoint)
    *    Calculates the angle of a vector in a circle with the data of the middlepoint and a point on the circle
    *
    */
   double getAngle(VectorType tPoint, VectorType tMidPoint);

   /*! \fn double getRad(VectorType tPoint, VectorType tMidPoint)
    *    Calculates the radius of a circle with the data of the middlepoint and a point on the circle
    *
    */
   double getRad(VectorType tPoint, VectorType tMidPoint);

   /*! \fn double getSpanAngle(double startAngle, double endAngle, DirectionEnum direction);
    *    Callculates the angle between two angles
    *
    *
    */
   double getSpanAngle(double startAngle, double endAngle, DirectionEnum direction);

private:
   VectorType tStart;
   VectorType tEnd;
   VectorType tMiddle;
   DirectionEnum mDirection;
   StraightEnum mStraightType;
   LineEnum mLineType;
   ColorEnum mColor;
   ZoomEnum mZoomElementType;
   bool m_bFullCircle;
};


/*! \class slLine slpaintmodel.h
 *  \brief The Class holds Data for the paintwidget
 */
class SL_PAINT_MODEL_EXPORT SlLgrLine : public SlLgrShape
{

public:
   SlLgrLine::SlLgrLine(VectorType start, VectorType end, StraightEnum StraightType, LineEnum LineType, ColorEnum color, ZoomEnum ZoomElementType, SlLgrZoomArea* pZoomArea, int coordinateType);
   virtual ~SlLgrLine();
   virtual void draw(QPainter* pQPainter, QPalette rQPalette, double rScaleFact);
private:
   VectorType tStart;
   VectorType tEnd;
   StraightEnum mStraightType;
   LineEnum mLineType;
   ColorEnum mColor;
   ZoomEnum mZoomElementType;


};


/*! \class slPoint slpaintmodel.h
 *  \brief The Class holds Data for the paintwidget
 */

class SL_PAINT_MODEL_EXPORT SlLgrPoint : public SlLgrShape
{

public:
   SlLgrPoint::SlLgrPoint(VectorType point, PointEnum PointType, ColorEnum color, ZoomEnum ZoomElementType, SlLgrZoomArea* pZoomArea, int coordinateType);
   virtual ~SlLgrPoint();
   virtual void draw(QPainter* pQPainter, QPalette rQPalette, double rScaleFact);
private:
   VectorType tPoint;
   PointEnum mPointType;
   ColorEnum mColor;
   ZoomEnum mZoomElementType;
};




/*! \class slGrafModel slpaintmodel.h
 *  \brief The Class holds Data for the paintwidget
 */
class SL_PAINT_MODEL_EXPORT SlLgrModel //Model-class. Management of QList for the slShape-class
{

public:
   SlLgrModel(void) ;
   virtual ~SlLgrModel() ;

   void clearModelData();
   void setCoordinatInfo(QString axname1, QString axname2, int intPosCoordinatesystem);
   QString isAxName1();
   QString isAxName2();
   int isPosCoordinatesystem();
   void addLine(VectorType start, VectorType end, StraightEnum StraightType, LineEnum LineType, ColorEnum color, ZoomEnum ZoomElementType);
   void addCircle(VectorType start, VectorType middle, VectorType end, DirectionEnum DirectionEnum, bool isFullCircle, CircleEnum CircleType, LineEnum LineType, ColorEnum Color, ZoomEnum ZoomElementType);
   void addPoint(VectorType point, PointEnum PointType, ColorEnum color, ZoomEnum ZoomElementType);
   QList<SlLgrShape*> ShapeList;
   SlLgrZoomArea* ZoomArea;

private:
   QString m_strAxName1;
   QString m_strAxName2;
   int m_intPosCoordinatesystem;
   
   

};



#endif // !defined(SL_PAINT_MODEL_INCLUDE)
