#ifndef YMGAAboutDialog_h
#define YMGAAboutDialog_h

#include <yui/YUI.h>
#include <yui/YApplication.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YLabel.h>
#include <yui/YPushButton.h>
#include <yui/YEvent.h>

class YMGAAboutDialog
{
public:
	YMGAAboutDialog(const std::string& name, const std::string& version, const std::string& license, const std::string& description);
	~YMGAAboutDialog();
	
	void start();
	
	void setAppName(const std::string& name);
	void setAppVersion(const std::string& version);
	void setAppLicense(const std::string& license);
	void setAppAuthor(const std::string& author);
	void setAppDescription(const std::string& description);
	
	std::string getAppName();
	std::string getAppVersion();
	std::string getAppLicense();
	std::string getAppAuthor();
	std::string getAppDescription();
	
	YDialog* getYDialog();

private:
	std::string appName;
	std::string appVersion;
	std::string appLicense;
	std::string appAuthor;
	std::string appDescription;
	
	YDialog* mainDialog;
};


#endif //YMGAAboutDialog_h
