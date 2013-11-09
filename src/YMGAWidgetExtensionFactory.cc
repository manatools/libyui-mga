/*
  Copyright 2013 by Angelo Naselli <anaselli at linux dot it>
 
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

  File:         YMGAWidgetFactory.cc

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/


#include "YMGAWidgetExtensionFactory.h"
#include "YAlignment.h"
#include "YPushButton.h"
#include "YUI.h"
#include "YApplication.h"


YMGAWidgetFactory::YMGAWidgetFactory()
{
    // NOP
}

YMGAWidgetFactory::~YMGAWidgetFactory()
{
    // NOP
}

YMGAWidgetFactory* YMGAWidgetFactory::getYMGAWidgetFactory ( YWidgetExtensionFactory* instance )
{
    return dynamic_cast<YMGAWidgetFactory*>(instance);
}
