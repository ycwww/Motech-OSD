// BEGIN SUPPRESS ALL
// this is code from Trolltech, will not be changed!!!
///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmixmlwriter.h
 *  \author Trolltech
 *  \brief  Header file for class SlXmlWriter. (optional)
 *
 *  Copyright (C) 1992-2003 Trolltech AS. All Rights Reserved.
 *
 *  This file ("Example Code"), is part of an example program for Qt,
 *  and is licensed under the Qt Commercial License Agreement,
 *  Agreement version 2.4 and higher as well as under the GPL.
 *
 *  The Example Code is licensed to you "as is" without warranty of
 *  any kind. To the maximum extent permitted by applicable law,
 *  Trolltech on behalf of itself and its suppliers, disclaims all
 *  warranties express or implied, including, but not limited to,
 *  implied warranties of merchantability and fitness for a particular
 *  purpose with regard to the Example Code. Trolltech does not
 *  warrant that the Example Code will satisfy your requirements or
 *  that it is without defect or error or that the operation thereof
 *  will be uninterrupted. All use of and reliance on the Example Code
 *  is at the sole risk of and responsibility of you and your
 *  customers.
 *
 *  If you are a holder of a Qt Commercial License Agreement, you can
 *  use the code under that agreement or you can use it under GPL. If
 *  you are not a holder of a Qt Commercial License Agreement, you can
 *  use the code under the GPL. Regardless of the applicable license
 *  agreement, the Example Code may be used, distributed and modified
 *  without limitation.
 *
 *  This file is part of the HMI Solutionline global classes and utilities
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SL_HMI_XMLWRITER_H
#define SL_HMI_XMLWRITER_H

#include <QtCore/QTextStream>
#include "slhmitemplatesqt.h"

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif


/*! \class <Classname> slxmlwriter.h
 *  \brief  The AttrMap parameter to writeOpenTag(), writeAtomTag(), and
 *          writeTaggedString() stores "name = value" pairs. The class
 *          inherits its functionality from QMap.
*/
class SL_HMI_EXPORT AttrMap : public QMap<QString, QString>
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn AttrMap()
     *
     *  empty constructor
    */
    AttrMap();

    /*! \fn AttrMap(const QString& name, const QString& value)
     *  \param name     name of the attribute
     *  \param value    value of the attribute
     *
     *  constructor
    */
    AttrMap( const QString& name, const QString& value );

    /*! \fn virtual ~AttrMap()
     *
     *  empty destructor
    */
    virtual ~AttrMap();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
};

/*! \class SlXmlWriter slxmlwriter.h
 *  \brief The XmlWriter class provides a basic API for generating XML files.
 *         First, let's see the definition of the class:
 *
 *  The AttrMap parameter to writeOpenTag(), writeAtomTag(), and
 *  writeTaggedString() stores "name = value" pairs. The class inherits its
 *  functionality from QMap.
 *
 *  ***************************************************************************
 *
 *  For example, the XML line
 *
 *  \<animal age="25"\>Elephant\</animal\>
 *  can be generated using this code:
 *
 *  XmlWriter xw( device );
 *  xw.writeTaggedString( "animal", "Elephant",
 *                        AttrMap("age", "25") );
 *
 *  Generating an XML File
 *
 *
 *  ***************************************************************************
 *
 *  Before we examine XmlWriter's implementation, we will see how to use it to
 *  generate an XML file. For the purpose of our example, we will use a Qt
 *  Designer .ui file.
 *
 *  ***************************************************************************
 *
 *  \<!DOCTYPE UI\>\<UI version="3.1"\>
 *  \<class\>Form1\</class\>
 *  \<widget class="QDialog"\>
 *      \<property name="name"\>
 *          \<cstring\>Form1\</cstring\>
 *      \</property\>
 *      \<property name="caption"\>
 *          \<string\>Form1\</string\>
 *      \</property\>
 *      \<vbox\>
 *          \<widget class="QLabel"\>
 *              \<property name="name"\>
 *                  \<cstring\>label\</cstring\>
 *              \</property\>
 *              \<property name="text"\>
 *                  \<string\>Rock &amp;&amp; Roll\</string\>
 *              \</property\>
 *          \</widget\>
 *      \</vbox\>
 *  \</widget\>
 *  \<layoutdefaults margin="11" spacing="6"/\>
 *  \</UI\>
 *  ***************************************************************************
 *
 *  The program that generates the above .ui file follows. It may seem like overkill since it is longer than the output it produces. But in more realistic scenarios where the output is dependent on the input and on the program's state, the XmlWriter class will save significant time and effort, and will eliminate many annoying bugs because it handles XML escaping automatically.
 *
 *  void writeProperty( XmlWriter& xw, const QString& name,
 *                      const QString& type,
 *                      const QString& value )
 *  {
 *      xw.writeOpenTag( "property", AttrMap("name", name) );
 *      xw.writeTaggedString( type, value );
 *      xw.writeCloseTag( "property" );
 *  }
 *
 *  int main()
 *  {
 *      QFile file;
 *      file.open( IO_WriteOnly, stdout );
 *      XmlWriter xw( &file );
 *      xw.setAutoNewLine( true );
 *      xw.writeRaw( "<!DOCTYPE UI><UI version=\"3.1\">" );
 *      xw.newLine();
 *      xw.writeTaggedString( "class", "Form1" );
 *      xw.writeOpenTag( "widget",
 *                       AttrMap("class", "QDialog") );
 *      writeProperty( xw, "name", "cstring", "Form1" );
 *      writeProperty( xw, "caption", "string", "Form1" );
 *      xw.writeOpenTag( "vbox" );
 *      xw.writeOpenTag( "widget",
 *                       AttrMap("class", "QLabel") );
 *      writeProperty( xw, "name", "cstring", "label" );
 *      writeProperty( xw, "text", "string", "Rock && Roll" );
 *      xw.writeCloseTag( "widget" );
 *
 *      xw.writeCloseTag( "vbox" );
 *      xw.writeCloseTag( "widget" );
 *      AttrMap attrs;
 *      attrs.insert( "spacing", "6" );
 *      attrs.insert( "margin", "11" );
 *      xw.writeAtomTag( "layoutdefaults", attrs );
 *      xw.writeRaw( "</UI>" );
 *      return 0;
 *  }
 *
 *  ***************************************************************************
 *
 *  By using the XmlWriter class, we obtain a result that is formatted prettily
 *  without effort (indentation and line breaks), and we don't need to think
 *  about special characters that must be written as XML entities (e.g. "&"amp;)
 *  or about Unicode; everything is taken care of, either by XmlWriter or by
 *  QTextStream.
*/
class SL_HMI_EXPORT SlXmlWriter
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlXmlWriter( QIODevice *device, QTextCodec *codec = 0 );
     *  \param device   normally the QFile of the XML - File
     *  \param codec    Textcodec to use, if not set, UTF8 is used
     *
     *  creates an SlXmlWriter object
    */
    SlXmlWriter( QIODevice *device, QTextCodec *codec = 0 );

    /*! \fn SlXmlWriter( QTextStream *stream, QTextCodec *codec = 0 );
     *  \param stream   Textstream, usually working on the XML - File
     *  \param codec    Textcodec to use, if not set, UTF8 is used
     *
     *  creates an SlXmlWriter object
    */
    SlXmlWriter( QTextStream *stream, QTextCodec *codec = 0 );

    /*! \fn SlXmlWriter( QString* string, QTextCodec *codec = 0 );
     *  \param string   String to fill with XML
     *  \param codec    Textcodec to use, if not set, UTF8 is used
     *
     *  creates an SlXmlWriter object
    */
    SlXmlWriter( QString* string, QTextCodec *codec = 0 );

    /*! \fn ~SlXmlWriter();
     *
     *  The destructor appends a `"\n"' to the file in "auto new-line" mode.
    */
    ~SlXmlWriter();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    QString alternativeEndOfLineIdent( void );
    void setAlternativeEndOfLineIdent( const QString& aeoli );

    /*! \fn void writeRaw(const QString& xml );
     *  \param xml  XML - String to write
     *
     *  outputs raw XML.
    */
    void writeRaw(const QString& xml );

    /*! \fn void writeComment(const QString& comment );
     *  \param comment comment to write
     *
     *  writes a coment; a comment is ended by a new line
    */
    void writeComment(const QString& comment );

    /*! \fn void writeString(const QString& string );
     *  \param string   string to write
     *
     *  outputs a string, replacing special characters with entities
    */
    void writeString(const QString& string );

    /*! \fn void writeOpenTag(const QString& name,
                              const AttrMap& attrs = AttrMap() );
     *  \param name     tag name
     *  \param attrs    attributes of the tag
     *
     *  outputs an opening tag with optional "name = value" attributes,
     *  e.g. \<item id="X23"\>
    */
    void writeOpenTag(  const QString& name, const AttrMap& attrs = AttrMap() );

    /*! \fn void writeCloseTag( const QString& name );
     *  \param name Tag to close
     *
     *  Closing tags are output by writeCloseTag(), e.g. \</item\>:
    */
    void writeCloseTag( const QString& name );

    /*! \fn void writeAtomTag(const QString& name,
                              const AttrMap& attrs = AttrMap() );
     *  \param name     tag name
     *  \param attrs    attributes of the tag
     *
     *  outputs an opening-and-closing tag, e.g. \<item id=X23/\>
    */
    void writeAtomTag(  const QString& name, const AttrMap& attrs = AttrMap() );

    /*! \fn void writeTaggedString(const QString& name, const QString& string,
                                   const AttrMap& attrs = AttrMap() );
     *  \param name     tag name
     *  \param string
     *  \param attrs    attributes of the tag
     *
     *  The writeTaggedString() is a convenience function that outputs an
     *  opening tag, a string, and a closing tag, e.g.:
     *  \<item id=X23\>
     *      Text
     *  \</item\>
    */
    void writeTaggedString( const QString& name, const QString& string,
                            const AttrMap& attrs = AttrMap() );

    /*! \fn void newLine();
     *
     *  Now we'll review the public functions. The newLine() function can be
     *  used to force a new line.
    */
    void newLine();

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn void setIndentSize( int size )
     *  \param size number of idents
     *
     *  sets the count of indents used for identation
    */
    void setIndentSize( int size ) { indentSize = size; }

    /*! \fn void setAutoNewLine( bool on )
     *  \param on   on / off
     *
     *  enables AutoNewLine for automatical new lines
    */
    void setAutoNewLine( bool on ) { autoNewLine = on; }

private:
    ///////////////////////////////////////////////////////////////////////////
    // internal member functions
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn QString protect( const QString& string );
     *  \param string   original string
     *  \retval QString replaced string
     *
     *  Although private, the protect() function is by far the most important.
     *  It replaces special characters with entities:
    */
    QString protect( const QString& string );

    /*! \fn QString opening( const QString& tag, const AttrMap& attrs = AttrMap() );
     *  \param tag      new Tag to open
     *  \param attrs    attributes of the tag
     *  \retval QString string to add to the file
     *
     *  The opening() private function constructs an opening tag from the name of
     *  the tag and the "name = value" attributes:
    */
    QString opening( const QString& tag, const AttrMap& attrs = AttrMap() );

    /*! \fn void writePendingIndent();
     *
     *  The writePendingIndent() private function indents a tag:
    */
    void writePendingIndent();

    ///////////////////////////////////////////////////////////////////////////
    // Member variables
    ///////////////////////////////////////////////////////////////////////////
    /*! Strem to use for writing */
    QTextStream* pOutStream;
    /*! String used for identation */
    QString indentStr;
    /*! number of indentStr, inserted before idented tags */
    int indentSize;
    /*! should a new line be added at the end automatically */
    bool autoNewLine;
    /*! indicates, that the current position is the first charater of a line */
    bool atBeginningOfLine;
    /*! indicates, that the internal used TextStream was given by the special constructor */
    bool bTextStreamGiven;
    /* ! holds an alternative end of line identifier. 
    Default: "endl" ist used
    Caution: "endl" means on Linux: '\n' and on Windows : "\r\n" */
    QString sAlternativeEndOfLineIdent;
};

#endif // SL_HMI_XMLWRITER_H

// END SUPPRESS
