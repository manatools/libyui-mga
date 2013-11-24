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

  File:         YMGA_CBTable.cc

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/


#define YUILogComponent "ui"
#include "YUILog.h"

#include "YUISymbols.h"
#include "YMGA_CBTable.h"

struct YMGA_CBTablePrivate
{
  YMGA_CBTablePrivate ( YTableHeader * header )
    : header ( header )
    , keepSorting ( false )
    , immediateMode ( false )
    , mode ( YTableCheckBoxOnFirstColumn )
    , item ( 0 )
  {
  }

  YTableHeader* header;
  bool          keepSorting;
  bool          immediateMode;
  YTableMode    mode;
  YItem*        item;
};





YMGA_CBTable::YMGA_CBTable ( YWidget* parent, YTableHeader * header, YTableMode mode )
  :YSelectionWidget ( parent,
                      "",     // label
                      mode==YTableSingleLineSelection ) // enforceSingleSelection
  , priv ( new YMGA_CBTablePrivate ( header ) )
{
  YUI_CHECK_PTR ( header );
  // TODO Remove YTableSingleLineSelection and YTableMultiSelectionvalues to let YTable managing them
  if ( mode != YTableCheckBoxOnFirstColumn && mode != YTableCheckBoxOnLastColumn )
    YUI_THROW ( YUIException() );

  YUI_CHECK_NEW ( priv );

  priv->mode = mode;

  setDefaultStretchable ( YD_HORIZ, true );
  setDefaultStretchable ( YD_VERT,  true );
}


YMGA_CBTable::~YMGA_CBTable()
{
}

YItem* YMGA_CBTable::changedItem()
{
  return priv->item;
}

void YMGA_CBTable::setChangedItem ( YItem* pItem )
{
  priv->item = pItem;
}


YTableMode YMGA_CBTable::selectionMode()
{
  return priv->mode;
}


void YMGA_CBTable::addItem ( YItem* item )
{
  YUI_CHECK_PTR ( item );
  bool selected = item->selected();

  YSelectionWidget::addItem ( item );

  // get rid of YSelectionWidget::addItem that selects first item
  item->setSelected ( selected );
}

void YMGA_CBTable::setTableHeader ( YTableHeader * newHeader )
{
  YUI_CHECK_PTR ( newHeader );

  if ( priv->header->columns() != newHeader->columns() )
    deleteAllItems();

  delete priv->header;
  priv->header = newHeader;
}


int YMGA_CBTable::columns() const
{
  return priv->header->columns();
}


bool YMGA_CBTable::hasColumn ( int column ) const
{
  return priv->header->hasColumn ( column );
}


std::string YMGA_CBTable::header ( int column ) const
{
  return priv->header->header ( column );
}


YAlignmentType YMGA_CBTable::alignment ( int column ) const
{
  return priv->header->alignment ( column );
}


bool YMGA_CBTable::immediateMode() const
{
  return priv->immediateMode;
}


void YMGA_CBTable::setImmediateMode ( bool immediateMode )
{
  priv->immediateMode = immediateMode;

  if ( immediateMode )
    setNotify ( true );
}


bool YMGA_CBTable::keepSorting() const
{
  return priv->keepSorting;
}


void YMGA_CBTable::setKeepSorting ( bool keepSorting )
{
  priv->keepSorting = keepSorting;
}


bool YMGA_CBTable::hasMultiSelection() const
{
  return ! YSelectionWidget::enforceSingleSelection();
}


YItem * YMGA_CBTable::item ( int index ) const
{
  return YSelectionWidget::itemAt ( index );
}

YItemIterator YMGA_CBTable::nextItem( YItemIterator currentIterator)
{
  return ++currentIterator;
}

YItem* YMGA_CBTable::YItemIteratorToYItem ( YItemIterator it )
{
  return *it;
}

const YPropertySet &YMGA_CBTable::propertySet()
{
  static YPropertySet propSet;

  if ( propSet.isEmpty() )
  {
    /*
     * @property itemID             Value           The currently selected item
     * @property itemID             CurrentItem     The currently selected item
     * @property itemList           Items           All items
     * @property itemList           SelectedItems   All currently selected items
     * @property std::string        Cell            One cell (one column of one item)
     * @property integer            Cell            (ChangeWidget only) One cell as integer
     * @property `icon(...)         Cell            Icon for one one cell
     * @property std::string        Item            Alias for Cell
     * @property std::string        Item            QueryWidget only: Return one complete item
     * @property std::string        IconPath        Base path for icons
     * @property bool               MultiSelection  Flag: User can select multiple items (read-only)
     */
    propSet.add ( YProperty ( YUIProperty_Value,              YOtherProperty ) );
    propSet.add ( YProperty ( YUIProperty_CurrentItem,        YOtherProperty ) );
    propSet.add ( YProperty ( YUIProperty_SelectedItems,      YOtherProperty ) );
    propSet.add ( YProperty ( YUIProperty_Items,              YOtherProperty ) );
    propSet.add ( YProperty ( YUIProperty_Cell,               YOtherProperty ) );
    propSet.add ( YProperty ( YUIProperty_Item,               YOtherProperty ) );
    propSet.add ( YProperty ( YUIProperty_IconPath,           YStringProperty ) );
    propSet.add ( YProperty ( YUIProperty_MultiSelection,     YBoolProperty,   true ) ); // read-only
    propSet.add ( YWidget::propertySet() );
  }

  return propSet;
}


bool YMGA_CBTable::setProperty ( const std::string & propertyName, const YPropertyValue & val )
{
  propertySet().check ( propertyName, val.type() ); // throws exceptions if not found or type mismatch

  if ( propertyName == YUIProperty_Value )
    return false; // Needs special handling
  else if ( propertyName == YUIProperty_CurrentItem )
    return false; // Needs special handling
  else if ( propertyName == YUIProperty_SelectedItems )
    return false; // Needs special handling
  else if ( propertyName == YUIProperty_Items )
    return false; // Needs special handling
  else if ( propertyName == YUIProperty_Cell )
    return false; // Needs special handling
  else if ( propertyName == YUIProperty_Item )
    return false; // Needs special handling
  else if ( propertyName == YUIProperty_IconPath )
    setIconBasePath ( val.stringVal() );
  else
  {
    return YWidget::setProperty ( propertyName, val );
  }

  return true; // success -- no special processing necessary
}


YPropertyValue YMGA_CBTable::getProperty ( const std::string & propertyName )
{
  propertySet().check ( propertyName ); // throws exceptions if not found

  if ( propertyName == YUIProperty_Value )
    return YPropertyValue ( YOtherProperty );
  else if ( propertyName == YUIProperty_CurrentItem )
    return YPropertyValue ( YOtherProperty );
  else if ( propertyName == YUIProperty_SelectedItems )
    return YPropertyValue ( YOtherProperty );
  else if ( propertyName == YUIProperty_Items )
    return YPropertyValue ( YOtherProperty );
  else if ( propertyName == YUIProperty_Cell )
    return YPropertyValue ( YOtherProperty );
  else if ( propertyName == YUIProperty_Item )
    return YPropertyValue ( YOtherProperty );
  else if ( propertyName == YUIProperty_IconPath )
    return YPropertyValue ( iconBasePath() );

  return YWidget::getProperty ( propertyName );
}

