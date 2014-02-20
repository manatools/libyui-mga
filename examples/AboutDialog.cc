/*
  Copyright 2014 by Matteo Pasotti

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
//     g++ -I/usr/include/yui -lyui AboutDialog.cc -o AboutDialog

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YEvent.h>
#include <yui/YExternalWidgets.h>
#include "YMGAAboutDialog.h"
#include "YMGAWidgetExtensionFactory.h"


int main( int argc, char **argv )
{
    const std::string MageiaPlugin = "mga";
    const std::string desc = "This is a <b>demo</b> to show you how <em>beautiful</em> is the <u>builtin</u> AboutDialog<br />";
    YExternalWidgets * pMGAExternalWidgets = YExternalWidgets::externalWidgets(MageiaPlugin);
    YMGAWidgetFactory* pMGAFactory = (YMGAWidgetFactory*)(pMGAExternalWidgets->externalWidgetFactory());
    YMGAAboutDialog    * dialog = pMGAFactory->createAboutDialog("HostManager","1.0.0","GPLv2", desc,"/usr/share/icons/mageia.png");
    //YLayoutBox * vbox   = YUI::widgetFactory()->createVBox( dialog->getYDialog() );
    //YUI::widgetFactory()->createLabel     ( vbox, "Hello, World!" );
    //YUI::widgetFactory()->createPushButton( vbox, "&OK" );

    dialog->start();
    // dialog->getYDialog()->waitForEvent();
    // dialog->getYDialog()->destroy();
}
