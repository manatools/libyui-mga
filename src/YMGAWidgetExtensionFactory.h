/*
  Copyright (C) 2013 Angelo Naselli <anaselli at linux dot it>
  
  This file is a YExternalWidgetFactory implementation 
  
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) version 3.0 of the License. This library
  is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details. You should have received a copy of the GNU
  Lesser General Public License along with this library; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
  Floor, Boston, MA 02110-1301 USA
*/

/*-/

  File:         YMGAWidgetFactory.h

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/

#ifndef YMGAWidgetExtensionFactory_h
#define YMGAWidgetExtensionFactory_h

#include <string>

#include <yui/YExternalWidgetFactory.h>
#include <yui/YTypes.h>
#include <yui/YEvent.h>

#include "YMGA_CBTable.h"

struct stat;

class YWidget;
class YMGAAboutDialog;

/**
 * Abstract extension widget factory to create widget extensions.
 *
 * Refer to the respective widget's documentation (in the header file) for
 * documentation about the function parameters.
 **/
class YMGAWidgetFactory : public YExternalWidgetFactory
{
public:
    YMGAAboutDialog * createAboutDialog( const std::string& appname, 
					 const std::string& appversion, 
					 const std::string& applicense, 
					 const std::string& appdescription,
					 const std::string& appicon
				       );
    virtual YMGA_CBTable * createCBTable ( YWidget * parent, YTableHeader * header_disown, YCBTableMode mode = YCBTableCheckBoxOnFirstColumn ) = 0;

    /**
     * casts useful for bindings
     * 
     **/
    // cast to get YMGAWidgetFactory 
    static YMGAWidgetFactory* getYMGAWidgetFactory(YExternalWidgetFactory* instance);
    
    // event conversions
    static YWidgetEvent*  getYWidgetEvent(YEvent *event);
    static YKeyEvent*     getYKeyEvent(YEvent *event);
    static YMenuEvent*    getYMenuEvent(YEvent *event);
    static YCancelEvent*  getYCancelEvent(YEvent *event);
    static YDebugEvent*   getYDebugEvent(YEvent *event);
    static YTimeoutEvent* getYTimeoutEvent(YEvent *event);
    
protected:

    friend class YExternalWidgets;

    /**
     * Constructor.
     *
     * Use YExternalWidgets::widgetExtensionFactory() to get the singleton for this class.
     **/
    YMGAWidgetFactory();

    /**
     * Destructor.
     **/
    virtual ~YMGAWidgetFactory();

}; // class YMGAWidgetFactory


#endif // YMGAWidgetExtensionFactory_h
