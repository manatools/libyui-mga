/*
  Copyright 2014-2016 by Matteo Pasotti

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
  SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
  OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


// YMGAAboutDialog example.
//
// Compile with:
//
//     g++ -I/usr/include/yui -lyui -libyui-mga AboutDialog.cc -o AboutDialog

#include <memory>
#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YEvent.h>
#include <yui/YExternalWidgets.h>
#include <yui/YCommandLine.h>
#include "YMGAAboutDialog.h"
#include "YMGAWidgetExtensionFactory.h"


int main( int argc, char **argv )
{
    const std::string MageiaPlugin = "mga";
    const std::string appName = "About dialog"; 
    const std::string version = "1.0.0";
    const std::string desc = "This is a <b>demo</b> to show you how <em>beautiful</em> is the <u>builtin</u> AboutDialog<br />";
    const std::string authors = "<h3>Developers</h3><ul><li>Angelo Naselli</li><li>Matteo Pasotti</li></ul><h3>Translators</h3>";
    const std::string credits = "(C) 2013-2014 Angelo Naselli\n(C) 2013-2014 Matteo Pasotti";
    const std::string logo = "/usr/lib/libDrakX/icons/IC-Dhost-48.png";
    const std::string icon = "";
    const std::string info = "Displaying <strong>useful</strong> information";

    YCommandLine cmdline;
    if (cmdline.find("--help") > 0 || cmdline.find("-h") > 0 )
    {
        std::cout << appName << " " << version << std::endl;
        std::cout << std::endl;
        std::cout << "AboutDialog [OPTIONS]" << std::endl;
        std::cout << "OPTIONS" << std::endl;
        std::cout << "--help | -h       run this help" << std::endl;
        std::cout << "--tabbed          run tabbed about dialog" << std::endl;
        return 0;
    }

    YExternalWidgets * pMGAExternalWidgets = YExternalWidgets::externalWidgets(MageiaPlugin);
    YMGAWidgetFactory* pMGAFactory = (YMGAWidgetFactory*)(pMGAExternalWidgets->externalWidgetFactory());
    std::unique_ptr<YMGAAboutDialog> dialog(pMGAFactory->createAboutDialog(
                                                                          appName,
                                                                          version,
                                                                          "GPLv2",
                                                                          authors,
                                                                          desc,
                                                                          icon,
                                                                         logo,
                                                                          credits,
                                                                          info
                                                                         )
                                         );

    if ( cmdline.find("--tabbed") > 0 )
        dialog->show(YMGAAboutDialog::TABBED);
    else
        dialog->show(YMGAAboutDialog::CLASSIC);

    return 0;
}
