/*
  Copyright 2013-2021 by Angelo Naselli <anaselli at linux dot it>

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

#include <vector>
#include <string>

#define YUILogComponent "mga-ui"
#include "YUILog.h"

#include "YUISymbols.h"
#include "YMGA_CBTable.h"

using std::vector;
using std::string;

/// define_class YMGA_CBTable

struct YMGA_CBTablePrivate
{
  YMGA_CBTablePrivate (  ) : header( 0 )
    , column ( -1 )
    , item ( 0 )
  {
  }

  YCBTableHeader * header;
  int column;
  YCBTableItem* item;
};

YMGA_CBTable::YMGA_CBTable ( YWidget* parent, YCBTableHeader * header)
  : YTable( parent,
            header,
            false ) // enforceSingleSelection
  , priv ( new YMGA_CBTablePrivate ( ) )
{
  YUI_CHECK_NEW ( priv );

  priv->header = header;

  setDefaultStretchable ( YD_HORIZ, true );
  setDefaultStretchable ( YD_VERT,  true );
}


YMGA_CBTable::~YMGA_CBTable()
{
}

bool YMGA_CBTable::isCheckBoxColumn(int column) const
{
  return priv->header->cbColumn(column);
}

YCBTableItem* YMGA_CBTable::changedItem()
{
  return priv->item;
}

void YMGA_CBTable::setChangedItem ( YCBTableItem* pItem )
{
  priv->item = pItem;
}


YItemIterator YMGA_CBTable::nextItem( YItemIterator currentIterator)
{
  return ++currentIterator;
}

void YMGA_CBTable::deleteAllItems()
{
  priv->item = NULL;
  YTable::deleteAllItems();
}


YItem* YMGA_CBTable::YItemIteratorToYItem ( YItemIterator it )
{
  return *it;
}

YCBTableItem* YMGA_CBTable::toCBYTableItem ( YItem* item )
{
  return dynamic_cast<YCBTableItem*>(item);
}

/// define_class YCBTableHeader

struct YCBTableHeaderPrivate
{
    YCBTableHeaderPrivate()
    {}

    vector<bool> cb_column;
};

YCBTableHeader::YCBTableHeader()
    : priv( new YCBTableHeaderPrivate )
{
    YUI_CHECK_NEW( priv );
}

YCBTableHeader::~YCBTableHeader()
{
    // NOP
}

void YCBTableHeader::addColumn(const std::string& header, bool checkBox, YAlignmentType alignment)
{
  YTableHeader::addColumn(header, alignment);
  priv->cb_column.push_back( checkBox );
}

bool YCBTableHeader::cbColumn(int column) const
{
  if ( column >= 0 && column < (int) priv->cb_column.size() )
    return priv->cb_column[ column ];
  else
    return false;
}

/// define_class YCBTableItem

YCBTableItem::YCBTableItem() :
  YTableItem(),
  _changedColumn(-1)
{

}

YCBTableItem::YCBTableItem( YCBTableCell * cell0_disown,
                            YCBTableCell * cell1_disown,
                            YCBTableCell * cell2_disown,
                            YCBTableCell * cell3_disown,
                            YCBTableCell * cell4_disown,
                            YCBTableCell * cell5_disown,
                            YCBTableCell * cell6_disown,
                            YCBTableCell * cell7_disown,
                            YCBTableCell * cell8_disown,
                            YCBTableCell * cell9_disown )
  : YTableItem()
  , _changedColumn(-1)
{
  vector<YCBTableCell *> vect{ cell1_disown,
                               cell2_disown,
                               cell3_disown,
                               cell4_disown,
                               cell5_disown,
                               cell6_disown,
                               cell7_disown,
                               cell8_disown,
                               cell9_disown };

  // if first cell is null addCell will correctly crash
  // so at least that must not be null
  addCell(cell0_disown);

  for (YCBTableCell * cell : vect)
  {
    if (cell)
      addCell(cell);
  }
}

void YCBTableItem::addCell(YCBTableCell* cell_disown)
{
  YTableItem::addCell(cell_disown);
}

bool YCBTableItem::checked(int index)
{
  bool isChecked = false;

  if (hasCell( index ) )
  {
    YTableCell *cell = YTableItem::cell(index);
    YCBTableCell *pCell = dynamic_cast<YCBTableCell *>(cell);
    if (pCell)
      isChecked = pCell->checked();
  }

  return isChecked;
}


void YCBTableItem::addCell(bool checked)
{
  YCBTableCell * cell = new YCBTableCell( checked );
  YUI_CHECK_NEW( cell );

  addCell( cell );
}

void YCBTableItem::addCell(const std::string& label, const std::string& iconName, const std::string& sortKey)
{
  YCBTableCell * cell = new YCBTableCell( label, iconName, sortKey);
  YUI_CHECK_NEW( cell );

  addCell( cell );
}

const YCBTableCell * YCBTableItem::cellChanged()
{
  return dynamic_cast<const YCBTableCell*>(cell(_changedColumn));
}

void YCBTableItem::setChangedColumn(int column)
{
  _changedColumn = hasCell(column) ? column : -1;
}
