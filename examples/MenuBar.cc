/*
  Copyright (c) 2016 SUSE LCC

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


// Menu Button example demonstrating also shortcut resolver.
//
// Compile with:
//
//     g++ -I/usr/include/yui -lyui MenuButtons.cc -o MenuButtons

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YEvent.h>
#include <yui/YExternalWidgets.h>
#include <yui/YMenuButton.h>
#include <yui/YLabel.h>
#include <yui/YMenuItem.h>
#include <yui/YExternalWidgets.h>
#include <mga/YMGAMenuBar.h>
#include <mga/YMGAWidgetExtensionFactory.h>

int main( int argc, char **argv )
{
    YDialog    * dialog = YUI::widgetFactory()->createPopupDialog();
    YLayoutBox * vbox   = YUI::widgetFactory()->createVBox( dialog );
    const std::string MageiaPlugin = "mga";
    // Plugin can be loaded by using YExternalWidgets::externalWidgets(name) or
    // YUILoader::loadExternalWidgets(name); //default symbol "_Z21createExternalWidgetsPKc"
    YExternalWidgets * pMGAExternalWidgets = YExternalWidgets::externalWidgets(MageiaPlugin);
    YMGAWidgetFactory* pMGAFactory = (YMGAWidgetFactory*)(pMGAExternalWidgets->externalWidgetFactory());

    YMGAMenuBar *menu = pMGAFactory->createMenuBar(vbox);
    YMenuItem *top = new YMenuItem("&Menu");
    new YMenuItem(top, "&submenu1");
    new YMenuItem(top, "&submenu2");
    new YMenuItem(top, "&submenu3");
    new YMenuItem(top, "&submenu4");
    menu->addItem(top);
    
    top = new YMenuItem("Menu &1");
    new YMenuItem( new YMenuItem(top, "m1"), "sm1" );
    new YMenuItem(top, "m2");
    new YMenuItem(top, "m3");
    menu->addItem(top);



    YLabel *label = YUI::widgetFactory()->createLabel( vbox, "Hello, World!" );
    YPushButton* quitButton = YUI::widgetFactory()->createPushButton( vbox, "&Quit");

    while ( true )
    {
        YEvent * event = dialog->waitForEvent();
	YEvent::EventType eventType = event->eventType();
	if (eventType == YEvent::CancelEvent) 
		break;
	else if (eventType == YEvent::MenuEvent) 
	{
            YItem *item = event->item();
	    label->setValue(item->label());
	}
	else if (eventType == YEvent::WidgetEvent) 
	{
//	    YWidgetEvent * ywe = dynamic_cast<YWidgetEvent *>(event)
            if (event->widget() == (YWidget*)quitButton)
	       break;
	}

    }

    dialog->destroy();
}
