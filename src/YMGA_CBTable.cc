/*
  Copyright (C) 2000-2012 Novell, Inc
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

  File:		YMGA_CBTable.cc

  Author:	Angelo Naselli <anaselli@linux.it>

/-*/


#define YUILogComponent "ui"
#include "YUILog.h"

#include "YUISymbols.h"
#include "YMGA_CBTable.h"

struct YMGA_CBTablePrivate
{
    YMGA_CBTablePrivate( YTableHeader * header )
	:/* header( header )
	, keepSorting( false )
	, immediateMode( false )
        ,*/ mode( YTableSingleLineSelection )
    {
    }

//     YTableHeader *	header;
//     bool		keepSorting;
//     bool		immediateMode;
    YTableMode          mode;
};




YMGA_CBTable::YMGA_CBTable( YWidget* parent, YTableHeader * header, YTableMode mode )
    : YTable( parent, header, mode==YTableSingleLineSelection) // enforceSingleSelection
    , priv( new YMGA_CBTablePrivate( header ) )
{
    YUI_CHECK_PTR( header );
    YUI_CHECK_NEW( priv   );

    priv->mode = mode;
    
    setDefaultStretchable( YD_HORIZ, true );
    setDefaultStretchable( YD_VERT,  true );
}


YMGA_CBTable::~YMGA_CBTable()
{
}


YTableMode YMGA_CBTable::selectionMode()
{
  return priv->mode;
}

