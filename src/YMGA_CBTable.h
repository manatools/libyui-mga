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

  File:         YMGA_CBTable.h

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/


#ifndef YMGA_CBTable_h
#define YMGA_CBTable_h

#include <yui/YTable.h>
#include <yui/YTypes.h>
#include <yui/ImplPtr.h>
#include <yui/YTableItem.h>
#include <yui/YTableHeader.h>
#include <yui/YEvent.h>

class YCBTableHeaderPrivate;

class YCBTableHeader : public YTableHeader
{
public:
  /**
   * Constructor.
   **/
  YCBTableHeader();

  /**
   * Destructor.
   **/
  virtual ~YCBTableHeader();

  /**
    * Add a column
    *  @param header column header text
    *  @param checkBox column as checkbox
    *  @param alignment column alignment
    **/
  void addColumn( const std::string &	header,
                  bool checkBox,
                  YAlignmentType alignment = YAlignBegin );

  /**
    * Return if column is a checkbox.
    **/
  bool cbColumn( int column ) const;

private:
  ImplPtr<YCBTableHeaderPrivate> priv;
};

class YCBTableCell: public YTableCell
{
public:
  /**
   * Constructor with label, optional checkbox value, optional icon name and optional sort
   * key for cells that don't have a parent item yet (that will be
   * added to a parent later with setParent()).
   **/
  YCBTableCell( const std::string & label,
                const std::string & iconName = "",
                const std::string & sortKey = "" )
    : YTableCell( label , iconName, sortKey )
    , _checked( false )
  {}

  YCBTableCell( const char * label )
    : YTableCell( std::string(label) )
    , _checked( false )
  {}

  YCBTableCell( const bool & checked )
    : YTableCell( "", "", "" )
    , _checked( checked )
  {}

  /**
   * Constructor with parent, column no., label and optional icon name for
   * cells that are created with a parent.
   **/
  YCBTableCell( YTableItem *parent,
                int column,
                const std::string & label= "",
                const bool & checked= false,
                const std::string & iconName = "",
                const std::string & sortKey = "" )
  : YTableCell( parent, column, label , iconName, sortKey )
  , _checked( checked )
  {}

  /**
   * Destructor.
   **/
  virtual ~YCBTableCell() {}

  /**
   * Set this cell's checked value.
   *
   * If this is called after the corresponding table item (table row) is
   * added to the table widget, call YTable::cellChanged() to notify the
   * table widget about the fact. Only then will the display be updated.
   **/
  virtual void setChecked(bool val=true) {_checked=val;}

  /**
   * Return this cells's checked value.
   **/
  virtual bool checked() const {return _checked;}

protected:
  bool _checked;
};

class YCBTableItem : public YTableItem
{
public:
    /**
     * Default constructor. Use addCell() to give it any content.
     **/
    YCBTableItem();


    /**
     * Convenience constructor with max 10 cells.
     * Note that cell ownership is passed to YCBTableItem
     * and null pointers are discarded changing the position
     * of the followed not null pointers.
     *
     **/
    YCBTableItem( YCBTableCell * cell0_disown,
                  YCBTableCell * cell1_disown = NULL,
                  YCBTableCell * cell2_disown = NULL,
                  YCBTableCell * cell3_disown = NULL,
                  YCBTableCell * cell4_disown = NULL,
                  YCBTableCell * cell5_disown = NULL,
                  YCBTableCell * cell6_disown = NULL,
                  YCBTableCell * cell7_disown = NULL,
                  YCBTableCell * cell8_disown = NULL,
                  YCBTableCell * cell9_disown = NULL);

    /**
     * Destructor.
     **/
    virtual ~YCBTableItem() {}

    /**
     * Returns a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * itemClass() const { return "YCBTableItem"; }

    /**
     * Add a cell. This item will assume ownership over the cell and delete it
     * when appropriate (when the table is destroyed or when table items are
     * replaced), at which time the pointer will become invalid.
     *
     * Cells can still be changed after they (and the item they belong to) are
     * added, but in that case, YTable::cellChanged() needs to be called to
     * update the table display accordingly.
     **/
    void addCell( YCBTableCell * cell_disown );


    /**
     * Create a new cell and add it (even if all 'label', 'iconName' and
     * 'sortKey' are empty).
     **/
    void addCell( const std::string & label,
                  const std::string & iconName = std::string(),
                  const std::string & sortKey  = std::string() );

    /**
    * Create a new cell with checked value
    **/
    void addCell(bool checked);

    /**
     * Create a new cell with 'label' and add it (convenient method
     * to avoid confusion with bool)
     **/
    void addCell( const char* label ) {addCell(std::string(label));}

    /**
     * Return if cell no. 'index' is checked (counting from 0 on) or false
     * if there is no cell with that index.
     **/
    virtual bool checked(int index) ;

    /**
     * Return last cell changed or null
     **/
    virtual const YCBTableCell* cellChanged();

    /**
     * set changed column to be retrieved later,
     * or -1 if column is not valid
     **/
    virtual void setChangedColumn(int column);

protected:
  int _changedColumn;
    
};
  
struct YMGA_CBTablePrivate;

/**
 * See document of YTable
 * YCBTable is a YTable with a checkbox column
 *
 **/
class YMGA_CBTable: public YTable
{
protected:
    /**
     * Constructor.
     *
     * 'header' describes the table's headers: Number of columns, column
     * headings, if column is a checkbox and column alignment.
     * Since it is a YTable this widget assumes ownership of header object
     * and will delete it when appropriate. The header cannot be changed
     * after creating the widget.
     * 
     **/
    YMGA_CBTable( YWidget * parent, YCBTableHeader * header );
    
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
     * Return 'true' if this column no. 'column' is a checkbox
     * (counting from 0 on).
     **/
    bool isCheckBoxColumn( int column ) const;


    /**
     * check/uncheck Item from application.
     * 
     * Derived classes are required to implement this and update the display
     * accordingly.
     *
     * Note that setting it from cell with setChecked(true) does not update the table
     * 
     **/
    virtual void setItemChecked( YItem * item, int column, bool checked = true ) = 0;

    /**
     * When derived classes emit YWidgetEvent with reason ValueChanged
     * they have to set which item is changed. Who manages the event 
     * have to use changedItem() to get it.
     * 
     * Derived classes can overwrite this function, but they should call this
     * base class function in the new implementation.
     */
    virtual void setChangedItem( YCBTableItem* pItem );    
    
    /**
     * Return the item which value is changed (e.g. checkbox).
     **/
    virtual YCBTableItem * changedItem();

    // yui bindings problem workarounds:
    /**
     * YSelectionWidget does not implement the increment of iterator
     * and bindings seem not to work with iterator++, next function
     * just returns the iterator icrementation, NOTE that it does not check
     * input parameter, just increment it.
     */  
    YItemIterator nextItem( YItemIterator currentIterator);

    /**
     * Delete all items.
     *
     **/
    virtual void deleteAllItems();

    /**
     * useful cast for bindings.
     * it does not any assunption on iter, so it is up to the user to
     * check if it is valid, it just returns *it.
     */
    YItem* YItemIteratorToYItem(YItemIterator iter); 
    
    /**
     * useful cast for bindings.
     * it just performs a dynamic_cast
     */
    YCBTableItem* toCBYTableItem( YItem* item );

private:

    ImplPtr<YMGA_CBTablePrivate> priv;
};


#endif // YMGA_CBTable_h
