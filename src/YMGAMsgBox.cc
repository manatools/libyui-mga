/*
  Copyright 2014 by Angelo Naselli 
 
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

  File:         YMGAMessageBox.cc

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/

#define YUILogComponent "mga-ui"
#include <yui/YUILog.h>

#include <yui/YUI.h>
#include <yui/YTypes.h>
#include <yui/YApplication.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YAlignment.h>
#include <yui/YPushButton.h>
#include <yui/YEvent.h>
#include <yui/YRichText.h>
#include <yui/YButtonBox.h>

#include <boost/algorithm/string/trim.hpp>
#include <vector>

#include "YMGAMsgBox.h"

using std::endl;

class YMGAMessageBoxPrivate {
public:
  YMGAMessageBoxPrivate() : title(), text(),
                            icon(), useRichText(false),
                            minWidth(40), minHeight(15),
                            buttons(YMGAMessageBox::B_ONE),
                            mode(YMGAMessageBox::D_NORMAL), 
                            default_button(YMGAMessageBox::B_ONE) {}
                            
  virtual ~YMGAMessageBoxPrivate(){}
  
  std::string title;
  std::string text;
  std::string icon;
  bool useRichText;
  YLayoutSize_t minWidth;
  YLayoutSize_t minHeight;
  YMGAMessageBox::DLG_BUTTON  buttons;
  YMGAMessageBox::DLG_MODE    mode;
  YMGAMessageBox::DLG_BUTTON  default_button;
  std::vector<std::string> label;
};

YMGAMessageBox::YMGAMessageBox(YMGAMessageBox::DLG_BUTTON b_num, 
                               YMGAMessageBox::DLG_MODE dlg_mode) :
     priv ( new YMGAMessageBoxPrivate()) 
{
  YUI_CHECK_NEW ( priv );
  
  priv->buttons = b_num;
  priv->mode    = dlg_mode;
  priv->label.resize((b_num==B_TWO ? 2 : 1));
}



YMGAMessageBox::~YMGAMessageBox()
{
  delete priv;
}


void YMGAMessageBox::setIcon(const std::string& icon)
{
  priv->icon = icon;
  boost::algorithm::trim(priv->icon);
}

void YMGAMessageBox::setTitle(const std::string& title)
{
  priv->title = title;
}

void YMGAMessageBox::setText(const std::string& text, bool useRichText)
{
  priv->text = text;
  priv->useRichText = useRichText;
}

void YMGAMessageBox::setMinSize(YLayoutSize_t minWidth, YLayoutSize_t minHeight)
{
  // limit dialog to a reasonable size
  if ( minWidth > 80 || minHeight > 25 )
  {
      minWidth  = 80;
      minHeight = 25;
  }
  priv->minHeight = minHeight;
  priv->minWidth  = minWidth;
}

void YMGAMessageBox::setButtonLabel(const std::string& label, DLG_BUTTON button)
{
  if ( priv->buttons != B_TWO && button == B_TWO) 
    YUI_THROW( YUIException( "Only one button configured" ) );
  
  priv->label[button] = label;
}

void YMGAMessageBox::setDefaultButton(DLG_BUTTON button)
{
  if ( priv->buttons != B_TWO && button == B_TWO) 
    YUI_THROW( YUIException( "Only one button configured" ) );
  
  priv->default_button = button;
}


YMGAMessageBox::DLG_BUTTON YMGAMessageBox::show()
{
  DLG_BUTTON btn = priv->default_button;
  
  std::string oldTitle = YUI::app()->applicationTitle();
  YUI::app()->setApplicationTitle(priv->title);
  if(priv->icon.length())
    YUI::app()->setApplicationIcon(priv->icon);
   
  YDialogColorMode colorMode;
  if (priv->mode == D_INFO) {
    colorMode = YDialogInfoColor;
  }
  else if (priv->mode == D_WARNING) {
    colorMode = YDialogWarnColor;
  }
  else { //D_NORMAL
    colorMode = YDialogNormalColor;
  }
      
  YDialog *pDialog = YUI::widgetFactory()->createPopupDialog(colorMode);
  YAlignment* minSize = YUI::widgetFactory()->createMinSize( pDialog, priv->minWidth, priv->minHeight );
  auto vbox           = YUI::widgetFactory()->createVBox( minSize );
 
  auto midhbox = YUI::widgetFactory()->createHBox(vbox);  
  // app description
  auto toprightvbox = YUI::widgetFactory()->createVBox(midhbox);
  toprightvbox->setWeight(YD_HORIZ, 5);
  YUI::widgetFactory()->createSpacing(toprightvbox,YD_HORIZ,false,5.0);
  YUI::widgetFactory()->createRichText(toprightvbox, priv->text, !priv->useRichText);
  YUI::widgetFactory()->createSpacing(toprightvbox,YD_HORIZ,false,5.0);
  
  // info button, if information are defined
  auto bottomhbox = YUI::widgetFactory()->createHBox(vbox);
  YPushButton *pB1=nullptr, *pB2=nullptr;
  if (priv->buttons == B_ONE) {
    pB1 = YUI::widgetFactory()->createPushButton(bottomhbox, priv->label[B_ONE]);
  }
  else { // B_TWO
    auto alignRight = YUI::widgetFactory()->createRight(bottomhbox);
    auto buttonBox = YUI::widgetFactory()->createHBox( alignRight );
    pB1 = YUI::widgetFactory()->createPushButton(buttonBox, priv->label[B_ONE]);
    pB2 = YUI::widgetFactory()->createPushButton(buttonBox, priv->label[B_TWO]);
  }
  if (priv->default_button == B_TWO)
    pDialog->setDefaultButton(pB2);
  else
    pDialog->setDefaultButton(pB1);
  
  while(true)
  {
    YEvent* event = pDialog->waitForEvent();
    if(event)
    {
      // window manager "close window" button
      if ( event->eventType() == YEvent::CancelEvent) {
        break; // leave event loop -> return default_button
      }
      else if( event->widget() == pB1 ) {
        btn = B_ONE;
        break;
      }
      else if (pB2 != nullptr && event->widget() == pB2) {
        btn = B_TWO;
        break;
      }
    }
  }
  
  pDialog->destroy();
  YUI::app()->setApplicationTitle(oldTitle);
  
  return btn;
}
