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
#include "YMGA_CBTable.h"
#include "YMGAMsgBox.h"

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

YMGAAboutDialog* YMGAWidgetFactory::createAboutDialog ( const std::string& appname,
                                                        const std::string& appver,
                                                        const std::string& applicense,
                                                        const std::string& appauthors,
                                                        const std::string& appdescription,
                                                        const std::string& applogo,
                                                        const std::string& appicon,
                                                        const std::string& appcredits,
                                                        const std::string& appinfo
                                                      )
{
    YMGAAboutDialog *ad = new YMGAAboutDialog(appname, appver, applicense, appauthors, appdescription, applogo, appicon, appcredits, appinfo);
    return ad; 
}


YMGAMessageBox* YMGAWidgetFactory::createDialogBox ( YMGAMessageBox::DLG_BUTTON button_number,
                                                      YMGAMessageBox::DLG_MODE   dialog_mode )
{
  YMGAMessageBox *msgBox = new YMGAMessageBox(button_number, dialog_mode);
  return msgBox;
}

YMGAMessageBox* YMGAWidgetFactory::createMessageBox ( const std::string& title, const std::string& text, bool useRichText, const std::string& btn_label )
{
  YMGAMessageBox *msgBox = new YMGAMessageBox(YMGAMessageBox::B_ONE, YMGAMessageBox::D_NORMAL);
  msgBox->setTitle(title);
  msgBox->setText(text, useRichText);
  msgBox->setButtonLabel(btn_label, YMGAMessageBox::B_ONE);
  return msgBox;
}

YMGAMessageBox* YMGAWidgetFactory::createInfoBox ( const std::string& title, const std::string& text, bool useRichText, const std::string& btn_label )
{
  YMGAMessageBox *msgBox = new YMGAMessageBox(YMGAMessageBox::B_ONE, YMGAMessageBox::D_INFO);
  msgBox->setTitle(title);
  msgBox->setText(text, useRichText);
  msgBox->setButtonLabel(btn_label, YMGAMessageBox::B_ONE);
  return msgBox;
}

YMGAMessageBox* YMGAWidgetFactory::createWarningBox ( const std::string& title, const std::string& text, bool useRichText, const std::string& btn_label )
{
  YMGAMessageBox *msgBox = new YMGAMessageBox(YMGAMessageBox::B_ONE, YMGAMessageBox::D_WARNING);
  msgBox->setTitle(title);
  msgBox->setText(text, useRichText);
  msgBox->setButtonLabel(btn_label, YMGAMessageBox::B_ONE);
  return msgBox;
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

YMGAMenuItem* YMGAWidgetFactory::toYMGAMenuItem( YItem* item )
{
  return dynamic_cast<YMGAMenuItem*>(item);
}

YMenuSeparator* YMGAWidgetFactory::toYMenuSeparator( YItem* item )
{
    return dynamic_cast<YMenuSeparator*>(item);
}
  
