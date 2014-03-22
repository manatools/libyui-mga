/*
  Copyright 2013 by Angelo Naselli <anaselli at linux dot it>
 
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

  File:         YMGAWidgetFactory.cc

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/


#include "YMGAWidgetExtensionFactory.h"
#include "YAlignment.h"
#include "YPushButton.h"
#include "YUI.h"
#include "YApplication.h"

#include "YMGAAboutDialog.h"

#define YUILogComponent "ew"
#include <yui/YUILog.h>


YMGAWidgetFactory::YMGAWidgetFactory()
{
    // NOP
}

YMGAWidgetFactory::~YMGAWidgetFactory()
{
    // NOP
  yuiMilestone() << "Factory removed" << std::endl;
}
/**
 * creates an About Dialog providing the information passed as arguments
 * @param appname the application name
 * @param appver the application version
 * @param applicense the application license, short-length (e.g. GPLv2, GPLv3, LGPL, LGPLv2+, etc)
 * @param appauthors the application authors
 * @param appdescription a brief description of the application
 * @param appicon the file path to the application icon
 * @param appcredits optional, the credits
 * @param appinfo optional, other extra information
 * @return YMGAAboutDialog instance
 */

YMGAAboutDialog* YMGAWidgetFactory::createAboutDialog(const std::string& appname, 
						      const std::string& appver, 
						      const std::string& applicense, 
						      const std::string& appauthors, 
						      const std::string& appdescription, 
						      const std::string& appicon,
						      const std::string& appcredits,
						      const std::string& appinfo
 						    )
{
    YMGAAboutDialog *ad = new YMGAAboutDialog(appname, appver, applicense, appauthors, appdescription, appicon, appcredits, appinfo);
    return ad; 
}

///< casts
YMGAWidgetFactory* YMGAWidgetFactory::getYMGAWidgetFactory ( YExternalWidgetFactory* instance )
{
    return dynamic_cast<YMGAWidgetFactory*>(instance);
}

YWidgetEvent*  YMGAWidgetFactory::getYWidgetEvent(YEvent *event)
{
    return dynamic_cast<YWidgetEvent*>(event);
}

YKeyEvent*     YMGAWidgetFactory::getYKeyEvent(YEvent *event)
{
    return dynamic_cast<YKeyEvent*>(event);
}

YMenuEvent*    YMGAWidgetFactory::getYMenuEvent(YEvent *event)
{
    return dynamic_cast<YMenuEvent*>(event);
}

YCancelEvent*  YMGAWidgetFactory::getYCancelEvent(YEvent *event)
{
    return dynamic_cast<YCancelEvent*>(event);
}

YDebugEvent*   YMGAWidgetFactory::getYDebugEvent(YEvent *event)
{
    return dynamic_cast<YDebugEvent*>(event);
}

YTimeoutEvent* YMGAWidgetFactory::getYTimeoutEvent(YEvent *event)
{
    return dynamic_cast<YTimeoutEvent*>(event);
}

  
