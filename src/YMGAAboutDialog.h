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

#include <string>

class YMGAAboutDialogPrivate;
class YDialog;
class YReplacePoint;

class YMGAAboutDialog
{
public:
  enum DLG_MODE {
          CLASSIC,
          TABBED
        };
        
  YMGAAboutDialog(const std::string& name, 
                  const std::string& version, 
                  const std::string& license,
                  const std::string& authors, 
                  const std::string& description, 
                  const std::string& icon,
                  const std::string& credits = std::string(),
                  const std::string& information = std::string()
                 );
  virtual ~YMGAAboutDialog();

  void start(DLG_MODE type = CLASSIC);
        

private:
  YMGAAboutDialogPrivate *priv;
  
  void genAuthorsTab(YReplacePoint* rpoint);
  void genContributorsTab(YReplacePoint* rpoint);
  void genInformationTab(YReplacePoint* rpoint);
  
  void Tabbed();
  void Classic();
  
  void showInformation();
  void showCredits();
};


#endif //YMGAAboutDialog_h
