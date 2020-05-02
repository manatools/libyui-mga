/*
  Copyright 2020 by Angelo Naselli <anaselli at linux dot it>

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
    new YMenuItem(top, "submenu&2");
    new YMenuItem(top, "submenu&3");
    new YMenuItem(top, "submenu&4");
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
