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

#ifndef YMGAAboutDialog_h
#define YMGAAboutDialog_h


class YMGAAboutDialogPrivate;
class YDialog;

class YMGAAboutDialog
{
public:
	YMGAAboutDialog(const std::string& name, const std::string& version, const std::string& license, const std::string& description);
	virtual ~YMGAAboutDialog();
	
	void start();
	
	void setAppName(const std::string& name);
	void setAppVersion(const std::string& version);
	void setAppLicense(const std::string& license);
	void setAppAuthor(const std::string& author);
	void setAppDescription(const std::string& description);
	
	const std::string& getAppName() const;
	const std::string& getAppVersion() const;
	const std::string& getAppLicense() const;
	const std::string& getAppAuthor() const;
	const std::string& getAppDescription() const;
	
	YDialog* getYDialog();

private:
        YMGAAboutDialogPrivate *priv;
};


#endif //YMGAAboutDialog_h
