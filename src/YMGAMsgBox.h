/*
  Copyright 2014 by Angelo Naselli <anaselli@linux.it>
 
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

  File:         YMGAMessageBox.h

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/

#ifndef YMGAMessageBox_h
#define YMGAMessageBox_h

#include <string>
#include <yui/YTypes.h>

class YMGAMessageBoxPrivate;
class YDialog;
class YReplacePoint;

class YMGAMessageBox
{
public:
  enum DLG_BUTTON {
    /// One button dialog, or button one pressed
    B_ONE = 0, 
    /// two buttons dialog, or button two pressed
    B_TWO = 1
  };
  
  enum DLG_MODE {
    /// Normal dialog
    D_NORMAL,
    /// Info dialog 
    D_INFO,
    /// Warning dialog
    D_WARNING
  };
        
  /**
   * The constructor. Note that this object is not a widget, so you must deleted it, if allocated on the heap. 
   * @param b_num B_ONE: one button only, B_TWO Two buttons dialog.
   * @param dlg_mode NORMAL, INFO, WARNING dialog 
   * @see YMGAMessageBox::DLG_BUTTON
   * @see YMGAMessageBox::DLG_MODE
   */ 
  YMGAMessageBox(DLG_BUTTON b_num    = B_ONE,
                 DLG_MODE   dlg_mode = D_NORMAL
                 );
  /**
   * Destructor.
   **/
  virtual ~YMGAMessageBox();

  /**
   * sets the message box icon (full path)
   * @param icon icon pathname
   */ 
  void setIcon(const std::string& icon);
  
  /**
   * sets the message box title 
   * @param title title text
   */
  void setTitle(const std::string& title);
  
  /**
   * sets the message box text information 
   * @param text dialog content text
   * @param useRichText set text using rich text if true
   */
  void setText(const std::string& text, bool useRichText=false);
  
  /**
   * sets the dilaog box minimum size according to YWidgetFactory::createMinSize()
   * @param minWidth dialog min width
   * @param minHeight dialog min height
   */
  void setMinSize(YLayoutSize_t minWidth, YLayoutSize_t minHeight );
  
  /**
   * sets the message box button name (empty string is assigned by default)
   * @param label button name
   * @param button button to set (B_ONE, or B_TWO if configured for two buttons) 
   */
  void setButtonLabel(const std::string& label, DLG_BUTTON button=B_ONE);
  
  /**
   * sets the message box default button
   * @param button button to set (B_ONE, or B_TWO if configured for two buttons) 
   */
  void setDefaultButton(DLG_BUTTON button=B_ONE);
  
  /**
   * it shows the message box dialog using data set by user. 
   * @return which button has been pressed to leave the dialog (B_ONE or B_TWO)
   */
  DLG_BUTTON show();
        

private:
  YMGAMessageBoxPrivate *priv;
 
  
};


#endif //YMGAMessageBox_h
