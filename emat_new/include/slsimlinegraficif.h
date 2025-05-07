///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimlinegraficif.h
 *  \author Walter Haering
 *  \date   28.09.2009
 *  \brief  Sim Controlthread Class interface file
 *
 *  This file is part of the HMI Solutionline Simlation system
 *
 *  (C) Copyright Siemens AG A&D MC 2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLSIMLINEGRAFICIF_H
#define SLSIMLINEGRAFICIF_H

enum SlsimLineGraficEleEnum    //!< enum for elementtypes
{
    SLSIM_GRAFIC_NONE   = 0,
    SLSIM_GRAFIC_LINE   = 1,
    SLSIM_GRAFIC_CIRCLE = 2,
    SLSIM_GRAFIC_HEADER = 3,
};
enum SlsimOglListStateEnum    //!< enum OGL-list
{
    SLSIM_GL_LIST_STATE_NONE     = 0,
    SLSIM_GL_LIST_STATE_INIT     = 1,
    SLSIM_GL_LIST_STATE_FILLED   = 2,
};

struct SlsimLineGraficElementPosType  //!< type for pos element
{
    double a1;
    double a2;

};


struct SlsimLineGraficElementLineType  //!< type for line element
{
   SlsimLineGraficElementPosType start;
   SlsimLineGraficElementPosType end;
};

struct SlsimLineGraficElementCircleType  //!< type for circle element
{
   SlsimLineGraficElementPosType start;
   SlsimLineGraficElementPosType end;
   SlsimLineGraficElementPosType mpos;
   double r;
   int clockwise;
   int vk;

};
struct SlsimLineGraficElementHeaderType  //!< type for header element
{
    long startIndexHsp; //!<  Index of first element hsp
    long startIndexGsp; //!<  Index of first element gsp
    long listsizetotal; //!<  total count of elements
    long listsizeHsp;   //!<  number of hsp elements
    long listsizeGsp;   //!<  number of gsp elements
    long channel;       //!<  channel
    long useOglLists;   //!<  flag: use opengl-lists
    unsigned char hsp_r;  //!<  color hsp contour
    unsigned char hsp_g;
    unsigned char hsp_b;
    unsigned char gsp_r;  //!<  color gsp contour
    unsigned char gsp_g;
    unsigned char gsp_b;
};
struct SlsimLineGraficElementType       //!< type for grafic element
{
    SlsimLineGraficEleEnum type;
    union 
    {
        SlsimLineGraficElementLineType   line;
        SlsimLineGraficElementCircleType circle;
        SlsimLineGraficElementHeaderType header;
    }u;

    SlsimLineGraficElementType ()
        : type(SLSIM_GRAFIC_NONE)
    {
        memset(&u, 0, sizeof(u));
    }

};



#endif //SLSIMLINEGRAFICIF_H

