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
#include <yui/YApplication.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YLabel.h>
#include <yui/YPushButton.h>
#include <yui/YEvent.h>
#include <yui/YImage.h>
#include <yui/YRichText.h>

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
  std::string appAuthor;
  std::string appDescription;
  std::string appIcon;

  YDialog* mainDialog;
};

YMGAAboutDialog::YMGAAboutDialog(const std::string& name, const std::string& version, const std::string& license, const std::string& description, const std::string& icon) :
    priv ( new YMGAAboutDialogPrivate()) 
{
  YUI_CHECK_NEW ( priv );

  priv->appName = name;
  priv->appVersion = version;
  priv->appLicense = license;
  priv->appDescription = description;
  priv->appIcon = icon;
  priv->mainDialog = YUI::widgetFactory()->createPopupDialog();
}

YMGAAboutDialog::~YMGAAboutDialog()
{
  delete priv;
}

void YMGAAboutDialog::start()
{
  YUI::app()->setApplicationTitle(priv->appName);
  auto vbox = YUI::widgetFactory()->createVBox(priv->mainDialog);
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  if(priv->appIcon.compare("")!=0)
  {
    auto logo = YUI::widgetFactory()->createImage(tophbox,priv->appIcon);
    logo->setAutoScale(false);
    logo->setWeight(YD_HORIZ, 2);
  }
  auto toprightvbox = YUI::widgetFactory()->createVBox(tophbox);
  toprightvbox->setWeight(YD_HORIZ, 5);
  auto lblAppName = YUI::widgetFactory()->createLabel(toprightvbox, "");
  lblAppName->setValue(priv->appName);
  auto lblAppVersion = YUI::widgetFactory()->createLabel(toprightvbox, "");
  lblAppVersion->setValue(priv->appVersion);
  auto rt = YUI::widgetFactory()->createRichText(toprightvbox,"");
  rt->setValue(priv->appDescription);
  
  auto bottomhbox = YUI::widgetFactory()->createHBox(vbox);
  auto infoButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Info");
  auto creditsButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Credits");
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
      else if( event->widget() == infoButton )
      {
	
      }
      else if( event->widget() == creditsButton )
      {
	
      }
    }
  }
  priv->mainDialog->destroy();
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
  priv->appAuthor = author;
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
  return priv->appAuthor;
}

const std::string& YMGAAboutDialog::getAppDescription() const
{
  return priv->appDescription;
}

void YMGAAboutDialog::setAppDescription ( const std::string& description )
{
  priv->appDescription = description;
}

