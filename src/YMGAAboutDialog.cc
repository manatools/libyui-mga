#define YUILogComponent "mga-ui"
#include "YUILog.h"
#include <yui/YLayoutBox.h>
#include <yui/YLabel.h>
#include <yui/YPushButton.h>
#include <yui/YRichText.h>
#include <yui/YImage.h>
#include <yui/YEvent.h>

#include "YMGAAboutDialog.h"

using std::endl;

YMGAAboutDialog::YMGAAboutDialog(const std::string& name, const std::string& version, const std::string& license, const std::string& description)
{
  this->appName = name;
  this->appVersion = version;
  this->appLicense = license;
  this->appDescription = description;
  this->mainDialog = YUI::widgetFactory()->createPopupDialog();
}

void YMGAAboutDialog::start()
{
  YUI::app()->setApplicationTitle(this->appName);
  auto vbox = YUI::widgetFactory()->createVBox(this->mainDialog);
  auto tophbox = YUI::widgetFactory()->createHBox(vbox);
  auto logo = YUI::widgetFactory()->createImage(tophbox,"/usr/share/icons/mageia.png");
  logo->setAutoScale(false);
  logo->setWeight(YD_HORIZ, 2);
  auto toprightvbox = YUI::widgetFactory()->createVBox(tophbox);
  toprightvbox->setWeight(YD_HORIZ, 5);
  auto lblAppName = YUI::widgetFactory()->createLabel(toprightvbox, "");
  lblAppName->setValue(this->appName);
  auto lblAppVersion = YUI::widgetFactory()->createLabel(toprightvbox, "");
  lblAppVersion->setValue(this->appVersion);
  auto rt = YUI::widgetFactory()->createRichText(toprightvbox,"");
  rt->setValue(this->appDescription);
  
  auto bottomhbox = YUI::widgetFactory()->createHBox(vbox);
  auto infoButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Info");
  auto creditsButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Credits");
  auto cancelButton = YUI::widgetFactory()->createPushButton(bottomhbox, "Close");
  while(true)
  {
    YEvent* event = this->mainDialog->waitForEvent();
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
  this->mainDialog->destroy();
}

YDialog* YMGAAboutDialog::getYDialog()
{
  return this->mainDialog;
}

void YMGAAboutDialog::setAppName(const std::string& name)
{
  this->appName = name;
}
void YMGAAboutDialog::setAppVersion(const std::string& version)
{
  this->appVersion = version;
}
void YMGAAboutDialog::setAppLicense(const std::string& license)
{
  this->appLicense = license;
}
void YMGAAboutDialog::setAppAuthor(const std::string& author)
{
  this->appAuthor = author;
}

std::string YMGAAboutDialog::getAppName()
{
  return this->appName;
}
std::string YMGAAboutDialog::getAppVersion()
{
  return this->appVersion;
}
std::string YMGAAboutDialog::getAppLicense()
{
  return this->appLicense;
}
std::string YMGAAboutDialog::getAppAuthor()
{
  return this->appAuthor;
}
