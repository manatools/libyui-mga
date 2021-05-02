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

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YEvent.h>
#include <yui/YExternalWidgets.h>
#include <yui/YMenuButton.h>
#include <yui/YPushButton.h>
#include <yui/YLabel.h>
#include <yui/mga/YMGAMenuItem.h>
#include <yui/YExternalWidgets.h>
#include <yui/mga/YMGAMenuBar.h>
#include <yui/mga/YMGAWidgetExtensionFactory.h>
#define YUILogComponent "YMenuBar"
#include <yui/YUILog.h>


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
  YMGAMenuItem *quitMenu = NULL;

  while ( true )
  {
    YEvent * event = dialog->waitForEvent();
    YEvent::EventType eventType = event->eventType();
    if (eventType == YEvent::CancelEvent)
      break;
    else if (eventType == YEvent::MenuEvent)
    {
      YItem *item = event->item();
      if (item)
      {
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
        else if (item == quitMenu)
          break;
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

        // next items have been removed but are still managed into loop
        // this is a simple exmaple so let's avoid to test them wrongly
        // setting to NULL
        enM1Item = NULL;
        hiddenMenu = NULL;
        hiddenMenuItem = NULL;
        showNextMenuItem = NULL;
        m1 = m4 = NULL;
        menu1Item = hideM2Item = NULL;

        YItemCollection itemCollection;
        YMGAMenuItem* mItem = new YMGAMenuItem("&File");
        YMGAMenuItem *tmi = new YMGAMenuItem(mItem, "&New");
        new YMGAMenuItem( tmi, "New &1" , "document-new");
        new YMGAMenuItem( tmi, "New &2" , "contact-new");
        new YMenuSeparator(mItem);
        new YMGAMenuItem(mItem, "&Open", "document-open.png");
        new YMenuSeparator(mItem);
        new YMGAMenuItem(mItem, "&Save", "document-save.png");
        new YMGAMenuItem(mItem, "&Save as", "document-save-as");
        new YMenuSeparator(mItem);
        // You can set absolute or relative pathname instead
//      new YMGAMenuItem(mItem, "&Quit", "my_path_to_quit.png");
        quitMenu = new YMGAMenuItem(mItem, "&Quit", "application-exit");
        itemCollection.push_back(mItem);

        YMGAMenuItem* mItem1 = new YMGAMenuItem("&Edit");
        new YMGAMenuItem(mItem1, "&Undo", "edit-undo.png");
        new YMGAMenuItem(mItem1, "&Redo", "edit-redo.png");
        new YMenuSeparator(mItem1);
        new YMGAMenuItem(mItem1, "Cu&t", "edit-cut.png");
        new YMGAMenuItem(mItem1, "&Copy", "edit-copy.png");
        new YMGAMenuItem(mItem1, "&Paste", "edit-paste.png");
        itemCollection.push_back(mItem1);

        menuBar->addItems(itemCollection);
      }
    }

  }

  dialog->destroy();
}
