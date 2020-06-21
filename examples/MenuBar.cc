/*
 *  Copyright 2020 by Angelo Naselli <anaselli at linux dot it>
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation; either version 2.1 of the
 *  License, or (at your option) version 3.0 of the License. This library
 *  is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 *  License for more details. You should have received a copy of the GNU
 *  Lesser General Public License along with this library; if not, write
 *  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 *  Floor, Boston, MA 02110-1301 USA
 */


// Menu Button example demonstrating also shortcut resolver.
//
// Compile with:
//
//     g++ -I/usr/include/yui -lyui MenuButtons.cc -o MenuButtons

#include "YUI.h"
#include "YWidgetFactory.h"
#include "YDialog.h"
#include "YLayoutBox.h"
#include "YEvent.h"
#include "YExternalWidgets.h"
#include "YMenuButton.h"
#include "YPushButton.h"
#include "YLabel.h"
#include "YMGAMenuItem.h"
#include "YExternalWidgets.h"
#include "YMGAMenuBar.h"
#include "YMGAWidgetExtensionFactory.h"
#define YUILogComponent "YMenuBar"
#include "YUILog.h"


int main( int argc, char **argv )
{
  // If you need logging uncommment next two lines
  YUILog::setLogFileName( "/tmp/libyui-mga-examples.log" );
  YUILog::enableDebugLogging();

  YDialog    * dialog = YUI::widgetFactory()->createPopupDialog();
  YLayoutBox * vbox   = YUI::widgetFactory()->createVBox( dialog );
  const std::string MageiaPlugin = "mga";
  // Plugin can be loaded by using YExternalWidgets::externalWidgets(name) or
  // YUILoader::loadExternalWidgets(name); //default symbol "_Z21createExternalWidgetsPKc"
  YExternalWidgets * pMGAExternalWidgets = YExternalWidgets::externalWidgets(MageiaPlugin);
  YMGAWidgetFactory* pMGAFactory = (YMGAWidgetFactory*)(pMGAExternalWidgets->externalWidgetFactory());

  YMGAMenuBar *menuBar = pMGAFactory->createMenuBar(vbox);
  YMGAMenuItem *top = new YMGAMenuItem("&Menu");
  YMGAMenuItem *m1 = new YMGAMenuItem(top, "&Enable submenu4");
  m1->enable(false);
  YMGAMenuItem *enM1Item = new YMGAMenuItem(top, "&Enabler/disable Menu 1");
  new YMGAMenuItem(top, "submenu&3");
  YMGAMenuItem *m4 = new YMGAMenuItem(top, "Enable &submen1");
  YMGAMenuItem *hideM2Item = new YMGAMenuItem(top, "&Hide/Show Menu 2");
  menuBar->addItem(top);

  YMGAMenuItem *menu1Item = new YMGAMenuItem("Menu &1");
  new YMGAMenuItem( new YMGAMenuItem(menu1Item, "m&1"), "sm1" );
  new YMGAMenuItem(menu1Item, "m&2");
  new YMGAMenuItem(menu1Item, "m&3");
  menu1Item->enable(false);
  menuBar->addItem(menu1Item);

  YMGAMenuItem *hiddenMenu = new YMGAMenuItem("Menu &2");
  YMGAMenuItem *showNextMenuItem = new YMGAMenuItem(hiddenMenu, "&Show/Hide next item");
  YMGAMenuItem *hiddenMenuItem = new YMGAMenuItem( hiddenMenu, "&Hidden menu" );
  hiddenMenuItem->hide();
  hiddenMenu->hide();
  menuBar->addItem(hiddenMenu);

  YMGAMenuItem* mItem = new YMGAMenuItem("Menu &3");
  YMGAMenuItem *tmi = new YMGAMenuItem(mItem, "m3 &1");
  new YMGAMenuItem( tmi, "sm1" );
  new YMGAMenuItem( tmi, "m3 sm2" );
  new YMGAMenuItem(mItem, "m3 &2");
  new YMGAMenuItem(mItem, "m3 &3");
  new YMGAMenuItem(mItem, "m3 &4");
  new YMGAMenuItem(mItem, "m3 &5");
  new YMGAMenuItem(mItem, "m3 &6");
  new YMGAMenuItem(mItem, "m3 &7");
  new YMGAMenuItem(mItem, "m3 &8");
  new YMGAMenuItem(mItem, "m3 &9");
  new YMGAMenuItem(mItem, "m3 &10");
  new YMGAMenuItem(mItem, "m3 &11");
  new YMGAMenuItem(mItem, "m3 &12");
  menuBar->addItem(mItem);

  mItem = new YMGAMenuItem("Menu &4");
  new YMGAMenuItem(mItem, "m4 &1");
  new YMGAMenuItem(mItem, "m4 &2");
  menuBar->addItem(mItem);
  YLabel *label = YUI::widgetFactory()->createLabel( vbox, "Here you'll see chosen menu item  " );
  YLayoutBox * hbox   = YUI::widgetFactory()->createHBox( vbox );
  YPushButton* changeMenuButton = YUI::widgetFactory()->createPushButton( hbox, "&Change Menu");
  YPushButton* quitButton = YUI::widgetFactory()->createPushButton( hbox, "&Quit");

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
      if (item == enM1Item)
      {
        menuBar->enableItem(menu1Item, !menu1Item->enabled());
      }
      else if (item == m1)
      {
        menuBar->enableItem(m4, true);
        menuBar->enableItem(m1, false);
      }
      else if (item == m4)
      {
        menuBar->enableItem(m1, true);
        menuBar->enableItem(m4, false);
      }
      else if (item == showNextMenuItem)
      {
        menuBar->hideItem(hiddenMenuItem, !hiddenMenuItem->hidden());
      }
      else if (item == hideM2Item)
      {
        menuBar->hideItem(hiddenMenu, !hiddenMenu->hidden());
      }
    }
    else if (eventType == YEvent::WidgetEvent)
    {
      YWidget *wdg = event->widget();
      if (wdg == (YWidget*)quitButton)
        break;
      else if (wdg == (YWidget*)changeMenuButton)
      {
        menuBar->startMultipleChanges();
        menuBar->deleteAllItems();
        menuBar->doneMultipleChanges();
        changeMenuButton->setEnabled(false);
        YItemCollection itemCollection;
        YMGAMenuItem* mItem = new YMGAMenuItem("Menu &1");
        YMGAMenuItem *tmi = new YMGAMenuItem(mItem, "m1 &1");
        new YMGAMenuItem( tmi, "m1 sm1" );
        new YMGAMenuItem( tmi, "m1 sm2" );
        new YMGAMenuItem(mItem, "m1 &2");
        new YMGAMenuItem(mItem, "m1 &3");
        itemCollection.push_back(mItem);

        YMGAMenuItem* mItem1 = new YMGAMenuItem("Menu &2");
        new YMGAMenuItem(mItem1, "m2 &1");
        new YMGAMenuItem(mItem1, "m2 &2");
        itemCollection.push_back(mItem1);

        menuBar->addItems(itemCollection);
      }
    }

  }

  dialog->destroy();
}
