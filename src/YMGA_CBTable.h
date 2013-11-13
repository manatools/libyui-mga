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

  File:         YMGA_CBTable.h

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/


#ifndef YMGA_CBTable_h
#define YMGA_CBTable_h

#include <yui/YTable.h>

#include <yui/YTypes.h>
#include <yui/YSelectionWidget.h>
#include <yui/YTableItem.h>
#include <yui/YTableHeader.h>

enum YTableMode {
    YTableSingleLineSelection,
    YTableMultiSelection,
    YTableCheckBoxOnFirstColumn,
    YTableCheckBoxOnLastColumn
  };
  
class YMGA_CBTablePrivate;

/**
 * See document of YMGA_CBTable
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
class YMGA_CBTable: public YSelectionWidget
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
     * Return the number of columns of this table.
     **/
    int columns() const;

    /**
     * Return 'true' if this table has a column no. 'column'
     * (counting from 0 on).
     **/
    bool hasColumn( int column ) const;

    /**
     * Return the header text for the specified column.
     **/
    std::string header( int column ) const;

    /**
     * Return the alignment for the specified column.
     **/
    YAlignmentType alignment( int column ) const;

    /**
     * Deliver even more events than with notify() set.
     *
     * With "notify" alone, a table widget sends an ActivatedEvent when the
     * user double-clicks an item or presses the "space" key on it. It does
     * not send an event when the user just sends another item.
     *
     * With "immediate", it also sends a SelectionChangedEvent when the user
     * selects another item. "immediate" implicitly includes "notify".
     **/
    bool immediateMode() const;

    /**
     * Set immediateMode() on or off.
     **/
    void setImmediateMode( bool immediateMode = true );

    /**
     * Return 'true' if the sort order is to be kept in item insertion order,
     * i.e. if sorting the table by clicking on a column header should be
     * disabled.
     **/
    bool keepSorting() const;

    /**
     * Switch between sorting by item insertion order (keepSorting: true) or
     * allowing the user to sort by an arbitrary column (by clicking on the
     * column header).
     *
     * Derived classes can overwrite this function, but they should call this
     * base class function in the new implementation.
     **/
    virtual void setKeepSorting( bool keepSorting );

    /**
     * Return 'true' if the user can select multiple items  at the same time
     * (e.g., with shift-click or ctrl-click).
     **/
    bool hasMultiSelection() const;

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

    /**
     * Set a property.
     * Reimplemented from YWidget.
     *
     * This function may throw YUIPropertyExceptions.
     *
     * This function returns 'true' if the value was successfully set and
     * 'false' if that value requires special handling (not in error cases:
     * those are covered by exceptions).
     **/
    virtual bool setProperty( const std::string & propertyName,
			      const YPropertyValue & val );

    /**
     * Get a property.
     * Reimplemented from YWidget.
     *
     * This method may throw YUIPropertyExceptions.
     **/
    virtual YPropertyValue getProperty( const std::string & propertyName );

    /**
     * Return this class's property set.
     * This also initializes the property upon the first call.
     *
     * Reimplemented from YWidget.
     **/
    virtual const YPropertySet & propertySet();


    /**
     * The name of the widget property that will return user input.
     * Inherited from YWidget.
     **/
    const char * userInputProperty() { return YUIProperty_CurrentItem; }

     /**
     * Add one item. This widget assumes ownership of the item object and will
     * delete it in its destructor.
     *
     * NOTE: For tree items, call this only for the toplevel items; all
     * non-toplevel items are already owned by their respective parent
     * items. Adding them to the parent widget will clash with this ownership.
     *
     * Reimplementation of YSelectionWidget::addItem.
     **/
//     virtual void addItem( YItem * item_disown );

    /**
     * Exchange the previous table header with a new one. This will delete the
     * old YTableHeader object.
     *
     * If the new header has a different number of columns than the old one,
     * all items will implicitly be deleted.
     **/
    void setTableHeader( YTableHeader * newHeader );

private:

    ImplPtr<YMGA_CBTablePrivate> priv;
};


#endif // YMGA_CBTable_h
