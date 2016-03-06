/*
  Copyright 2014 by Angelo Naselli

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


// Message Box example.
//
// Compile with:
//
//     g++ -I/usr/include/yui -lyui -libyui-mga MsgBoxDialog.cc -o MsgBox

#include <memory>

#include <yui/YUI.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YEvent.h>
#include <yui/YExternalWidgets.h>
#include "YMGAMsgBox.h"
#include "YMGAWidgetExtensionFactory.h"


int main( int argc, char **argv )
{
    const std::string MageiaPlugin = "mga";
   
    YExternalWidgets * pMGAExternalWidgets = YExternalWidgets::externalWidgets(MageiaPlugin);
    YMGAWidgetFactory* pMGAFactory = (YMGAWidgetFactory*)(pMGAExternalWidgets->externalWidgetFactory());
    const bool useRichText = true;
    std::unique_ptr<YMGAMessageBox> dialog(pMGAFactory->createInfoBox("Info test dialog", 
                                                                    "This is an info text into an info test dialog<br>"
                                                                    "This is the second line into an info test dialog",
                                                                    useRichText,
                                                                    "Ok"));

    dialog->show();
    
    dialog.reset(pMGAFactory->createWarningBox("Warning test dialog", 
                                          "And this is an info text into a warning test dialog",
                                          !useRichText,
                                          "Ok"));
   
    dialog->show();
    
    dialog.reset(pMGAFactory->createDialogBox(YMGAMessageBox::B_TWO, YMGAMessageBox::D_NORMAL));
    dialog->setTitle("Question dialog");
    dialog->setText("Do you want to go on?");
    dialog->setButtonLabel("Yes", YMGAMessageBox::B_ONE);
    dialog->setButtonLabel("No", YMGAMessageBox::B_TWO);
    dialog->setDefaultButton(YMGAMessageBox::B_TWO);
    YMGAMessageBox::DLG_BUTTON btn = dialog->show();
    if (btn == YMGAMessageBox::B_ONE)
    {
      dialog.reset(pMGAFactory->createMessageBox("MessageBox dialog", 
                                          "Last is a normal dialog containing this info text",
                                          useRichText,
                                          "Enjoy"));
   
    dialog->show();
    }
    return 0;
}
