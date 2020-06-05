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


/*-/

  File:         YMGAMenuBar.h

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/
#ifndef YMGAMenuBar_h
#define YMGAMenuBar_h

#include <yui/YTypes.h>
#include <yui/YSelectionWidget.h>
#include <yui/YMenuItem.h>
#include <yui/YEvent.h>


class YMGAMenuBar : public YSelectionWidget
{
  protected:
    /**
     * Constructor.
     *
     **/
    YMGAMenuBar( YWidget * parent );

  public:

    /**
     * Destructor.
     **/
    virtual ~YMGAMenuBar();

    /**
     * Return a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * widgetClass() const { return "YMGAMenuBar"; }

    /**
    * Enable YMGAMenuItem (menu name or menu entry) to enable/disable it into menubar or menu
    *
    **/
    virtual void enableItem(YItem * menu_item, bool enable=true);

    /**
    * Hide YMGAMenuItem (menu name or menu entry) to hide/show it into menubar or menu
    *
    **/
    virtual void hideItem(YItem * menu_item, bool invisible=true);

};

#endif //YMGAMenuBar_h

