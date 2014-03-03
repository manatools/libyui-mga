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

void YMGAAboutDialog::showInformation()
{
  auto infoDialog = YUI::widgetFactory()->createPopupDialog();
  auto vbox = YUI::widgetFactory()->createVBox(infoDialog);
  YUI::widgetFactory()->createLabel(vbox,"Information");
  auto rtcontent = YUI::widgetFactory()->createRichText(vbox);
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

void YMGAAboutDialog::showCredits()
{
  auto creditDialog = YUI::widgetFactory()->createPopupDialog();
  auto vbox = YUI::widgetFactory()->createVBox(creditDialog);
  YUI::widgetFactory()->createLabel(vbox,"Credits");
  auto rtcontent = YUI::widgetFactory()->createRichText(vbox);
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

void YMGAAboutDialog::genAuthorsTab(YReplacePoint* rpoint)
{
  rpoint->deleteChildren();
  auto hbox = YUI::widgetFactory()->createHBox(rpoint);
  YUI::widgetFactory()->createRichText(hbox,priv->appAuthors);
  rpoint->showChild();
  priv->mainDialog->recalcLayout();
}

void YMGAAboutDialog::genContributorsTab(YReplacePoint* rpoint)
{
  rpoint->deleteChildren();
  auto hbox = YUI::widgetFactory()->createHBox(rpoint);
  YUI::widgetFactory()->createRichText(hbox,priv->appDescription);
  rpoint->showChild();
  priv->mainDialog->recalcLayout();
}

void YMGAAboutDialog::Tabbed()
{
  priv->mainDialog = YUI::widgetFactory()->createPopupDialog();
  YUI::app()->setApplicationTitle("About " + priv->appName);
  auto vbox = YUI::widgetFactory()->createVBox(priv->mainDialog);
  
  /*
   * Layout 
   * _____________
   * |             |
   * |___CREDITS___|
   * |_a_|_b_|_c___|
   * |             |
   * |             |
   * |_____________|
   */
  
  YUI::widgetFactory()->createSpacing(vbox,YD_VERT,false,1.0);
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,2.0);
  YUI::widgetFactory()->createLabel(tophbox,priv->appCredits);
  YUI::widgetFactory()->createSpacing(tophbox,YD_HORIZ,false,2.0);
  YUI::widgetFactory()->createSpacing(vbox,YD_VERT,false,1.0);
  
  if(YUI::optionalWidgetFactory()->hasDumbTab())
  {
    auto dumbTab = YUI::optionalWidgetFactory()->createDumbTab(vbox);
    dumbTab->addItem(new YItem("Authors"));
    dumbTab->addItem(new YItem("Description"));
    
    auto bottomvbox = YUI::widgetFactory()->createVBox(vbox);
    auto rpoint = YUI::widgetFactory()->createReplacePoint(bottomvbox);
    
    this->genAuthorsTab(rpoint);
    
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
	}
      }
    }
    priv->mainDialog->destroy();
  }
  else
  {
    // handle it
  }
}

void YMGAAboutDialog::Classic()
{
  YPushButton* creditsButton = nullptr;
  YPushButton* infoButton = nullptr;
  priv->mainDialog = YUI::widgetFactory()->createPopupDialog();
  YUI::app()->setApplicationTitle("About " + priv->appName);
  auto vbox = YUI::widgetFactory()->createVBox(priv->mainDialog);
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  if(!priv->appIcon.empty())
  {
    auto logo = YUI::widgetFactory()->createImage(tophbox,priv->appIcon);
    logo->setAutoScale(false);
    logo->setWeight(YD_HORIZ, 2);
  }
  auto toprightvbox = YUI::widgetFactory()->createVBox(tophbox);
  toprightvbox->setWeight(YD_HORIZ, 5);
  auto lblAppName = YUI::widgetFactory()->createLabel(toprightvbox, "");
  lblAppName->setValue("About " + priv->appName);
  auto lblAppVersion = YUI::widgetFactory()->createLabel(toprightvbox, "");
  lblAppVersion->setValue(priv->appVersion);
  auto rt = YUI::widgetFactory()->createRichText(toprightvbox,"");
  rt->setValue(priv->appDescription);
  
  auto bottomhbox = YUI::widgetFactory()->createHBox(vbox);
  if(!priv->appInformation.empty())
  {
    infoButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Info");
  }
  
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
}

void YMGAAboutDialog::start(int type)
{
  if(type == 0)
  {
    this->Classic();
  }
  else
  {
   this->Tabbed(); 
  }
}

YDialog* YMGAAboutDialog::getYDialog()
{
  return priv->mainDialog;
}

void YMGAAboutDialog::setAppName(const std::string& name)
{
  priv->appName = name;
}
void YMGAAboutDialog::setAppVersion(const std::string& version)
{
  priv->appVersion = version;
}
void YMGAAboutDialog::setAppLicense(const std::string& license)
{
  priv->appLicense = license;
}
void YMGAAboutDialog::setAppAuthor(const std::string& author)
{
  priv->appAuthors = author;
}

const std::string& YMGAAboutDialog::getAppName() const
{
  return priv->appName;
}
const std::string& YMGAAboutDialog::getAppVersion() const
{
  return priv->appVersion;
}
const std::string& YMGAAboutDialog::getAppLicense() const
{
  return priv->appLicense;
}
const std::string& YMGAAboutDialog::getAppAuthor() const
{
  return priv->appAuthors;
}

const std::string& YMGAAboutDialog::getAppDescription() const
{
  return priv->appDescription;
}

void YMGAAboutDialog::setAppDescription ( const std::string& description )
{
  priv->appDescription = description;
}

