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

#include "YMGA_CBTable.h" // YCBTableMode
#include "YMGAMsgBox.h"   // DLG_BUTTON, DLG_MODE

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
  /**
   * creates an About Dialog providing the information passed as arguments.
   * Remember to remove this instance after.
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
  YMGAAboutDialog* createAboutDialog ( const std::string& appname,
                                               const std::string& appversion,
                                               const std::string& applicense,
                                               const std::string& appauthors,
                                               const std::string& appdescription,
                                               const std::string& appicon,
                                               const std::string& appcredits = std::string(),
                                               const std::string& appinfo = std::string()
                                             );

  /**
   * creates a check boxed table 
   * @param parent parent widget
   * @param header_disown YTable header
   * @param mode check box position (YCBTableCheckBoxOnFirstColumn, YCBTableCheckBoxOnLastColumn)
   * @return YMGA_CBTable widget instance
   **/
  virtual YMGA_CBTable* createCBTable ( YWidget * parent, YTableHeader * header_disown, YCBTableMode mode = YCBTableCheckBoxOnFirstColumn ) = 0;

  /**
   * creates a dialog box dialog, use the instance to set dialog information and call show() to use it. 
   * Remember to remove this instance after.
   * @param button_number one button (such as "ok" for instance) B_ONE or two buttons (such as "ok" and "cancel") B_TWO
   * @param dialog_mode   dialog type (D_NORMAL, D_INFO, D_WARNING)
   * @return YMGAMessageBox dialog instance
   **/
  YMGAMessageBox* createDialogBox ( YMGAMessageBox::DLG_BUTTON button_number=YMGAMessageBox::B_ONE,
                                             YMGAMessageBox::DLG_MODE   dialog_mode=YMGAMessageBox::D_NORMAL );
  
  /**
   * creates an messagebox dialog, use the instance to set dialog information and call show() to use it. 
   * Remember to remove this instance after.
   * @param title dialog title 
   * @param text  dialog content text
   * @param btn_label button label (such as Ok, for instance)
   * @return YMGAMessageBox dialog instance
   **/
  YMGAMessageBox* createMessageBox ( const std::string& title, const std::string& text, const std::string& btn_label );
  
   /**
   * creates an Info messagebox dialog, use the instance to set dialog information and call show() to use it. 
   * Remember to remove this instance after.
   * @param title dialog title 
   * @param text  dialog content text
   * @param btn_label button label (such as Ok, for instance)
   * @return YMGAMessageBox dialog instance
   **/
  YMGAMessageBox* createInfoBox ( const std::string& title, const std::string& text, const std::string& btn_label );
  
  /**
   * creates an Warning messagebox dialog, use the instance to set dialog information and call show() to use it. 
   * Remember to remove this instance after.
   * @param title dialog title 
   * @param text  dialog content text
   * @param btn_label button label (such as Ok, for instance)
   * @return YMGAMessageBox dialog instance
   **/
  YMGAMessageBox* createWarningBox ( const std::string& title, const std::string& text, const std::string& btn_label );
  
  /**
   * casts useful for bindings from YExternalWidgetFactory* to YMGAWidgetFactory*
   *
   **/
  static YMGAWidgetFactory* getYMGAWidgetFactory ( YExternalWidgetFactory* instance );

  // event conversions
  /**
   * casts useful for bindings from YEvent* to YWidgetEvent*
   *
   **/
  static YWidgetEvent*  getYWidgetEvent ( YEvent *event );
  
  /**
   * casts useful for bindings from YEvent* to YKeyEvent*
   *
   **/
  static YKeyEvent*     getYKeyEvent ( YEvent *event );
  
  /**
   * casts useful for bindings from YEvent* to YMenuEvent*
   *
   **/
  static YMenuEvent*    getYMenuEvent ( YEvent *event );
 
  /**
   * casts useful for bindings from YEvent* to YCancelEvent*
   *
   **/
  static YCancelEvent*  getYCancelEvent ( YEvent *event );
 
  /**
   * casts useful for bindings from YEvent* to YDebugEvent*
   *
   **/
  static YDebugEvent*   getYDebugEvent ( YEvent *event );
  
  /**
   * casts useful for bindings from YEvent* to YTimeoutEvent*
   *
   **/
  static YTimeoutEvent* getYTimeoutEvent ( YEvent *event );

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
