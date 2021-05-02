/*
 *  Copyright 2021 by Angelo Naselli <anaselli at linux dot it>
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
//     g++ -I/usr/include/yui -lyui YCBTable.cc -o YCBTable

#include <sstream>      // std::stringstream

#include <yui/YUI.h>
#include <yui/YAlignment.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YEvent.h>
#include <yui/YExternalWidgets.h>
#include <yui/YMenuButton.h>
#include <yui/YPushButton.h>
#include <yui/YLabel.h>
#include <yui/YFrame.h>
#include <yui/YExternalWidgets.h>
#include <yui/mga/YMGA_CBTable.h>
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

  YMGA_CBTable* table;
  YFrame * frame	= YUI::widgetFactory()->createFrame( vbox, "" );

  frame->setWeight( YD_HORIZ, 1 );
  YLayoutBox * align = YUI::widgetFactory()->createVBox( YUI::widgetFactory()->createHVCenter( frame ) );

  auto head = new YCBTableHeader();
  bool checkbox = true;
  head->addColumn( "Day", !checkbox, YAlignCenter );
  head->addColumn( "Meat", checkbox, YAlignBegin );
  head->addColumn( "Vegetables", checkbox, YAlignCenter );
  head->addColumn( "Pasta", checkbox, YAlignEnd );
  head->addColumn( "Note", !checkbox, YAlignBegin );

  table		= pMGAFactory->createCBTable( YUI::widgetFactory()->createRight(align), head );
  table->setNotify( true );

  YItemCollection items;
  bool checked = true;
  YCBTableItem * YCBItem = new YCBTableItem(
    new YCBTableCell("1"),
    new YCBTableCell(checked),
    new YCBTableCell(checked),
    new YCBTableCell(checked),
    new YCBTableCell("First one")
  );
  items.push_back( YCBItem );

  YCBItem = new YCBTableItem();
  YCBItem->addCell("2");
  YCBItem->addCell(!checked);
  YCBItem->addCell(checked);
  YCBItem->addCell(!checked);
  YCBItem->addCell(" - ");
  items.push_back( YCBItem );

  YCBItem = new YCBTableItem();
  YCBItem->addCell("3");
  YCBItem->addCell(!checked);
  YCBItem->addCell(!checked);
  YCBItem->addCell(checked);
  YCBItem->addCell(" - ");
  items.push_back( YCBItem );

  YCBItem = new YCBTableItem();
  YCBItem->addCell("4");
  YCBItem->addCell(!checked);
  YCBItem->addCell(checked);
  YCBItem->addCell(checked);
  YCBItem->addCell(" - ");
  items.push_back( YCBItem );

  YCBItem = new YCBTableItem();
  YCBItem->addCell("5");
  YCBItem->addCell(checked);
  YCBItem->addCell(!checked);
  YCBItem->addCell(checked);
  YCBItem->addCell(" - ");
  items.push_back( YCBItem );

  YCBItem = new YCBTableItem();
  YCBItem->addCell(std::string("6"));
  YCBItem->addCell(checked);
  YCBItem->addCell(!checked);
  YCBItem->addCell(!checked);
  YCBItem->addCell(std::string("Last one"));
  items.push_back( YCBItem );

  table->addItems( items ); // This is more efficient than repeatedly calling cbox->addItem

  YLabel* Text = YUI::widgetFactory()->createLabel(vbox, "----------------------------------------------------------");
  YPushButton* quitButton = YUI::widgetFactory()->createPushButton( vbox, "&Quit");

  while ( true )
  {
    YEvent * event = dialog->waitForEvent();
    YEvent::EventType eventType = event->eventType();
    if (eventType == YEvent::CancelEvent)
      break;
    else if (eventType == YEvent::MenuEvent)
      break;
    else if (eventType == YEvent::WidgetEvent)
    {
      YWidget *wdg = event->widget();
      if (wdg == (YWidget*)quitButton)
        break;
      else if ( wdg == table )
      {
        YWidgetEvent* wEvent = dynamic_cast<YWidgetEvent* >(event);
        if ( wEvent && wEvent->reason() == YEvent::ValueChanged )
        {
            YCBTableItem *changedItem = table->changedItem();
            if (changedItem)
            {
              std::stringstream ss;

              const YCBTableCell * cell = changedItem->cellChanged();
              ss << table->header(0) << " " << changedItem->cell(0)->label();
              if (cell)
              {
                int col = cell->column();
                ss << ": changed column " << col << " " << table->header(col) << " to " << (cell->checked() ? "true" : "false");
              }

              Text->setValue(ss.str());
            }
        }

        yuiMilestone() << "table changed " << std::endl;
      }
    }

  }

  dialog->destroy();
}
