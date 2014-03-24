/*
  Copyright 2014 by Matteo Pasotti
 
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

  File:         YMGAAboutDialog.cc

  Author:       Matteo Pasotti <matteo.pasotti@gmail.com>

/-*/

#define YUILogComponent "mga-ui"
#include "YUILog.h"

#include <yui/YUI.h>
#include <yui/YOptionalWidgetFactory.h>
#include <yui/YApplication.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YLabel.h>
#include <yui/YPushButton.h>
#include <yui/YEvent.h>
#include <yui/YImage.h>
#include <yui/YRichText.h>
#include <yui/YDumbTab.h>
#include <yui/YReplacePoint.h>

#include <boost/algorithm/string/trim.hpp>

#include "YMGAAboutDialog.h"

using std::endl;

class YMGAAboutDialogPrivate {
public:
  YMGAAboutDialogPrivate() {}
  virtual ~YMGAAboutDialogPrivate(){}
  
  std::string appName;
  std::string appVersion;
  std::string appLicense;
  std::string appAuthors;
  std::string appDescription;
  std::string appIcon;
  std::string appCredits;
  std::string appInformation;

  YDialog* mainDialog;
};

/**
 * The constructor. Note that this object is not a widget, so you must deleted it, if allocated on the heap.
 * @param name the application name
 * @param version the application version
 * @param license the application license, the short length one (e.g. GPLv2, GPLv3, LGPLv2+, etc)
 * @param authors the string providing the list of authors; it could be html-formatted
 * @param description the string providing a brief description of the application
 * @param icon the string providing the file path for the application icon
 * @param credits optional, the application credits, they can be html-formatted
 * @param information optional, other extra informations, they can be html-formatted
 */
YMGAAboutDialog::YMGAAboutDialog(const std::string& name, 
				 const std::string& version, 
				 const std::string& license, 
				 const std::string& authors,
				 const std::string& description, 
				 const std::string& icon,
                 const std::string& credits,
                 const std::string& information
				) :
    priv ( new YMGAAboutDialogPrivate()) 
{
  YUI_CHECK_NEW ( priv );

  priv->appName = name;
  priv->appVersion = version;
  priv->appLicense = license;
  priv->appAuthors = authors;
  priv->appDescription = description;
  priv->appIcon = icon;
  priv->appCredits = credits;
  priv->appInformation = information;
  boost::algorithm::trim(priv->appIcon);
}

YMGAAboutDialog::~YMGAAboutDialog()
{
  delete priv;
}

/**
  * invoked by pressing the information button inside the Classic dialog, it shows a popup dialog providing the information passed to the constructor
  * @see YMGAAboutDialog()
  * @see Classic()
  */
void YMGAAboutDialog::showInformation()
{
  auto infoDialog = YUI::widgetFactory()->createPopupDialog();
  auto vbox = YUI::widgetFactory()->createVBox(infoDialog);
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,10.0);
  YUI::widgetFactory()->createLabel(tophbox,"Information");
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,10.0);
  auto bottomhbox = YUI::widgetFactory()->createHBox(vbox);
  YUI::widgetFactory()->createSpacing(bottomhbox,YD_HORIZ,false,1.0);
  auto rtcontent = YUI::widgetFactory()->createRichText(bottomhbox);
  YUI::widgetFactory()->createSpacing(bottomhbox,YD_HORIZ,false,1.0);
  rtcontent->setText(priv->appInformation);
  auto closeButton = YUI::widgetFactory()->createPushButton(vbox,"Close");
  while(true)
  {
    YEvent* event = infoDialog->waitForEvent();
    if(event)
    {
      // window manager "close window" button
      if ( event->eventType() == YEvent::CancelEvent
        || event->widget() == closeButton )
        break; // leave event loop
    }
  }
  infoDialog->destroy();
}

/**
 * invoked by pressing the credits button inside the Classic dialog, it shows a popup dialog providing the credit list passed to the constructor
 * @see YMGAAboutDialog()
 * @see Classic()
 */
void YMGAAboutDialog::showCredits()
{
  auto creditDialog = YUI::widgetFactory()->createPopupDialog();
  auto vbox = YUI::widgetFactory()->createVBox(creditDialog);
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,16.0);
  YUI::widgetFactory()->createLabel(tophbox,"Credits");
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,16.0);
  auto rtcontent = YUI::widgetFactory()->createLabel(vbox,"");
  rtcontent->setText(priv->appCredits);
  auto closeButton = YUI::widgetFactory()->createPushButton(vbox,"Close");
  while(true)
  {
    YEvent* event = creditDialog->waitForEvent();
    if(event)
    {
      // window manager "close window" button
      if ( event->eventType() == YEvent::CancelEvent
        || event->widget() == closeButton )
        break; // leave event loop
    }
  }
  creditDialog->destroy();
}

/**
 * it generates the layout and the widgets providing the authors info
 * @param rpoint the replace point inside the Tabbed dialog
 * @see YMGAAboutDialog()
 * @see Tabbed()
 */

void YMGAAboutDialog::genAuthorsTab(YReplacePoint* rpoint)
{
  rpoint->deleteChildren();
  auto hbox = YUI::widgetFactory()->createHBox(rpoint);
  YUI::widgetFactory()->createRichText(hbox,priv->appAuthors);
  rpoint->showChild();
  priv->mainDialog->recalcLayout();
}

/**
 * it generates the layout and the widgets providing the contributors info
 * @param rpoint the replace point inside the Tabbed dialog
 * @see YMGAAboutDialog()
 * @see Tabbed()
 */
void YMGAAboutDialog::genContributorsTab(YReplacePoint* rpoint)
{
  rpoint->deleteChildren();
  auto hbox = YUI::widgetFactory()->createHBox(rpoint);
  YUI::widgetFactory()->createRichText(hbox,priv->appDescription);
  rpoint->showChild();
  priv->mainDialog->recalcLayout();
}

/**
 * it generates the layout and the widgets providing extra information
 * @param rpoint the replace point inside the Tabbed dialog
 * @see YMGAAboutDialog()
 * @see Tabbed()
 */
void YMGAAboutDialog::genInformationTab(YReplacePoint* rpoint)
{
  rpoint->deleteChildren();
  auto hbox = YUI::widgetFactory()->createHBox(rpoint);
  YUI::widgetFactory()->createRichText(hbox,priv->appInformation);
  rpoint->showChild();
  priv->mainDialog->recalcLayout();
}

/**
 * it builds the tabbed version for the about dialog box. 
 * @see YMGAAboutDialog()
 * @see Classic()
 */
void YMGAAboutDialog::Tabbed()
{
  std::string oldTitle = YUI::app()->applicationTitle();
  YUI::app()->setApplicationTitle("About " + priv->appName);
  if(priv->appIcon.length())
    YUI::app()->setApplicationIcon(priv->appIcon);
  priv->mainDialog = YUI::widgetFactory()->createPopupDialog();
  auto vbox = YUI::widgetFactory()->createVBox(priv->mainDialog);
  
  /*
   * Layout 
   * ______________________
   * | ICON  APPNAME VER  |
   * |___CREDITS__________|
   * |_a_|_b_|_c__________|
   * |                    |
   * |                    |
   * |____________________|
   */
  
  YUI::widgetFactory()->createSpacing(vbox,YD_VERT,false,1.0);
  auto upperhbox = YUI::widgetFactory()->createHBox(vbox);
  
  // the icon, if defined, if available
  if(priv->appIcon.length())
  {
    YUI::widgetFactory()->createSpacing(upperhbox,YD_HORIZ,false,3.0);
    YUI::widgetFactory()->createImage(upperhbox,priv->appIcon);
    YUI::widgetFactory()->createSpacing(upperhbox,YD_HORIZ,false,3.0);
  }
  
  // app name and version
  YUI::widgetFactory()->createSpacing(upperhbox,YD_HORIZ,false,3.0);
  YUI::widgetFactory()->createLabel(upperhbox,priv->appName + " " + priv->appVersion);
  YUI::widgetFactory()->createSpacing(upperhbox,YD_HORIZ,false,5.0);
  YUI::widgetFactory()->createSpacing(vbox,YD_VERT,false,1.0);
  
  // credits
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,3.0);
  YUI::widgetFactory()->createLabel(tophbox,priv->appCredits);
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,3.0);
  YUI::widgetFactory()->createSpacing(vbox,YD_VERT,false,0.5);
  
  // license
  auto licensehbox = YUI::widgetFactory()->createHBox(vbox);
  YUI::widgetFactory()->createSpacing(licensehbox,YD_HORIZ,false,3.0);
  YUI::widgetFactory()->createLabel(licensehbox,priv->appLicense);
  YUI::widgetFactory()->createSpacing(licensehbox,YD_HORIZ,false,3.0);
  YUI::widgetFactory()->createSpacing(vbox,YD_VERT,false,0.5);
  
  if(YUI::optionalWidgetFactory()->hasDumbTab())
  {
    auto dumbTab = YUI::optionalWidgetFactory()->createDumbTab(vbox);
    
    if(priv->appAuthors.length())
    {
      dumbTab->addItem(new YItem("Authors"));
    }
    if(priv->appDescription.length())
    {
      dumbTab->addItem(new YItem("Description"));
    }
    if(priv->appInformation.length())
    {
      dumbTab->addItem(new YItem("Information"));
    }
    
    auto bottomvbox = YUI::widgetFactory()->createVBox(vbox);
    auto rpoint = YUI::widgetFactory()->createReplacePoint(bottomvbox);
    
    if(priv->appAuthors.length())
    {
      this->genAuthorsTab(rpoint);
    }
    
    auto cancelButton = YUI::widgetFactory()->createPushButton(vbox,"Close");
    
    while(true)
    {
      YEvent* event = priv->mainDialog->waitForEvent();
      if(event)
      {
        // window manager "close window" button
        if ( event->eventType() == YEvent::CancelEvent
          || event->widget() == cancelButton )
          break; // leave event loop
        if ( event->eventType() == YEvent::MenuEvent )
        {
          if( event->item()->label().replace(event->item()->label().find("&"),1,"").compare("Authors")==0 )
          {
            this->genAuthorsTab(rpoint);
          }
          else if( event->item()->label().replace(event->item()->label().find("&"),1,"").compare("Description")==0 )
          {
            this->genContributorsTab(rpoint);
          }
          else if( event->item()->label().replace(event->item()->label().find("&"),1,"").compare("Information")==0 )
          {
            this->genInformationTab(rpoint);
          }
        }
      }
    }
    priv->mainDialog->destroy();
  }
  else
  {
    // handle it
  }
  YUI::app()->setApplicationTitle(oldTitle);
}

/**
 * it builds the classic version for the about dialog box. 
 * @see YMGAAboutDialog()
 * @see Tabbed()
 */
void YMGAAboutDialog::Classic()
{
  YPushButton* creditsButton = nullptr;
  YPushButton* infoButton = nullptr;
  std::string oldTitle = YUI::app()->applicationTitle();
  YUI::app()->setApplicationTitle(priv->appName);
  if(priv->appIcon.length())
    YUI::app()->setApplicationIcon(priv->appIcon);
  priv->mainDialog = YUI::widgetFactory()->createPopupDialog();
  auto vbox = YUI::widgetFactory()->createVBox(priv->mainDialog);
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  
  // icon, if defined, if available
  if(priv->appIcon.length())
  {
    YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,2.0);
    YUI::widgetFactory()->createImage(tophbox,priv->appIcon);
  }
  
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,8.0);
  auto headvbox = YUI::widgetFactory()->createVBox(tophbox);
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,12.0);
  
  // app name and version
  auto lblAppName = YUI::widgetFactory()->createLabel(headvbox, "");
  lblAppName->setValue(priv->appName);
  auto lblAppVersion = YUI::widgetFactory()->createLabel(headvbox, "");
  lblAppVersion->setValue(priv->appVersion);
  auto lblLicense = YUI::widgetFactory()->createLabel(headvbox, "");
  lblLicense->setValue(priv->appLicense);
  
  auto midhbox = YUI::widgetFactory()->createHBox(vbox);  
  // app description
  auto toprightvbox = YUI::widgetFactory()->createVBox(midhbox);
  toprightvbox->setWeight(YD_HORIZ, 5);
  YUI::widgetFactory()->createSpacing(toprightvbox,YD_HORIZ,false,5.0);
  auto rt = YUI::widgetFactory()->createRichText(toprightvbox,"");
  YUI::widgetFactory()->createSpacing(toprightvbox,YD_HORIZ,false,5.0);
  rt->setValue(priv->appDescription);
  
  // info button, if information are defined
  auto bottomhbox = YUI::widgetFactory()->createHBox(vbox);
  if(priv->appInformation.length())
  {
    infoButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Info");
  }
  
  // credits button, if credits are defined
  if(!priv->appCredits.empty())
  {
    creditsButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Credits");
  }
  
  auto cancelButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Close");
  while(true)
  {
    YEvent* event = priv->mainDialog->waitForEvent();
    if(event)
    {
      // window manager "close window" button
      if ( event->eventType() == YEvent::CancelEvent
        || event->widget() == cancelButton )
        break; // leave event loop
      else if( ( infoButton != nullptr ) && event->widget() == infoButton )
      {
        this->showInformation();
      }
      else if( ( creditsButton != nullptr ) && event->widget() == creditsButton )
      {
        this->showCredits();
      }
    }
  }
  priv->mainDialog->destroy();
  YUI::app()->setApplicationTitle(oldTitle);
}

/**
 * it actually shows the about dialog
 * @param type optional, DLG_MODE: defaulting to CLASSIC if not defined
 * @see Classic()
 * @see Tabbed()
 * @see YMGAAboutDialog::DLG_MODE
 */
void YMGAAboutDialog::show(YMGAAboutDialog::DLG_MODE type)
{
  if(type == TABBED)
  {
    this->Tabbed();
  }
  else
  {
    this->Classic(); 
  }
}
