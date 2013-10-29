/*
  Copyright (C) 2013 Angelo Naselli <anaselli at linux dot it>
  
  This file is a YWidgetExtensionFactory implementation 
  
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

#ifndef YMGAWidgetExtensionFactory_h
#define YMGAWidgetExtensionFactory_h

#include <string>

#include <yui/YWidgetExtensionFactory.h>
#include <yui/YTypes.h>
#include "YMGA_CBTable.h"


class YWidget;




/**
 * Abstract extension widget factory to create widget extensions.
 *
 * Refer to the respective widget's documentation (in the header file) for
 * documentation about the function parameters.
 **/
class YMGAWidgetFactory : public YWidgetExtensionFactory
{
public:

    virtual YMGA_CBTable * createTable ( YWidget * parent, YTableHeader * header_disown, YTableMode mode = YTableSingleLineSelection ) = 0;

    // usefull for bindings where casts are not easy to use.
    static YMGAWidgetFactory* getYMGAWidgetFactory(YWidgetExtensionFactory* instance);

protected:

    friend class YWE;

    /**
     * Constructor.
     *
     * Use YWE::widgetExtensionFactory() to get the singleton for this class.
     **/
    YMGAWidgetFactory();

    /**
     * Destructor.
     **/
    virtual ~YMGAWidgetFactory();

}; // class YMGAWidgetFactory


#endif // YMGAWidgetExtensionFactory_h
