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

  File:		YMGA_CBTable.h

  Author:	Angelo Naselli <anaselli@linux.it>

/-*/

#ifndef YMGA_CBTable_h
#define YMGA_CBTable_h

#include <YTable.h>

#include "YTypes.h"
#include "YSelectionWidget.h"
#include "YTableItem.h"
#include "YTableHeader.h"

enum YTableMode {
    YTableSingleLineSelection,
    YTableMultiSelection,
    YTableCheckBoxOnFirstColumn,
    YTableCheckBoxOnLastColumn
  };
  
class YMGA_CBTablePrivate;

/**
 * Table: Selection list with multiple columns. The user can select exactly one
 * row (with all its columns) from that list. Each cell (each column within
 * each row) has a label text and an optional icon (*).
 *
 * This widget is similar to SelectionBox, but it has several columns for each
 * item (each row). If just one column is desired, consider using SelectionBox
 * instead.
 *
 * Note: This is not something like a spread sheet, and it doesn't pretend or
 * want to be. Actions are performed on rows, not on individual cells (columns
 * within one row).
 *
 *
 * (*) Not all UIs (in particular not text-based UIs) support displaying icons,
 * so an icon should never be an exclusive means to display any kind of
 * information.
 **/
class YMGA_CBTable: public YTable 
{
protected:
    /**
     * Constructor.
     *
     * 'header' describes the table's headers: Number of columns, column
     * headings, and column alignment. The widget assumes ownership of this
     * object and will delete it when appropriate. The header cannot be changed
     * after creating the widget.
     *
     * 'multiSelection' indicates whether or not the user can select multiple
     * items at the same time (e.g., with shift-click or ctrl-click). This can
     * only be set in the constructor.
     **/
    YMGA_CBTable( YWidget * parent, YTableHeader * header, YTableMode mode );

public:

    /**
     * Destructor.
     **/
    virtual ~YMGA_CBTable();

    /**
     * Return a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * widgetClass() const { return "YMGA_CBTable"; }

     /**
     * returns the YTable selection mode
     *
     **/ 
    YTableMode selectionMode();

    /**
     * Notification that a cell (its text and/or its icon) was changed from the
     * outside. Applications are required to call this whenever a table cell is
     * changed after adding the corresponding table item (the row) to the table
     * widget.
     *
     * Derived classes are required to implement this and update the display
     * accordingly.
     *
     * Note that the position of this cell can be retrieved with cell->column()
     * and cell->itemIndex().
     **/
    virtual void cellChanged( const YTableCell * cell ) = 0;

   
private:

    ImplPtr<YMGA_CBTablePrivate> priv;
};


#endif // YMGA_CBTable_h
