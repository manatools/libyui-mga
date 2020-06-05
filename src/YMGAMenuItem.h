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

  File:		      YMGAMenuItem.h

  Author:       Angelo Naselli <anaselli@linux.it>

/-*/

#ifndef YMGAMenuItem_h
#define YMGAMenuItem_h

#include <yui/YMenuItem.h>



/**
 * Item class for menu items.
 **/
class YMGAMenuItem: public YMenuItem
{
public:
    /**
     * Constructors for toplevel items.
     **/
    YMGAMenuItem( const std::string &	label )
        : YMenuItem( label ), _enabled(true)
    {}

    YMGAMenuItem( const std::string & 	label,
                  const std::string & 	iconName )
        : YMenuItem( label, iconName ), _enabled(true)
    {}

    /**
     * Constructors for items that have a parent item.
     *
     * They will automatically register this item with the parent item. The
     * parent assumes ownership of this item and will delete it in its (the
     * parent's) destructor.
     **/
    YMGAMenuItem( YMGAMenuItem *		parent,
                  const std::string & 	label )
        : YMenuItem( parent, label ), _enabled(true), _hidden(false)
    {}

    YMGAMenuItem( YMGAMenuItem *		parent,
                  const std::string & 	label,
                  const std::string & 	iconName )
        : YMenuItem( parent, label, iconName ), _enabled(true), _hidden(false)
    {}


    /**
     * Destructor.
     *
     * This will delete all children.
     **/
    virtual ~YMGAMenuItem() {}

    /**
     * is Menu item enabled?
     */
    virtual bool enabled() {
        return _enabled;
    }

    /**
     * enable/disable Menu Item
     */
    virtual void enable(bool en=true) {
        _enabled=en;
    }

    /**
     * is Menu item hidden?
     */
    virtual bool hidden() {
        return _hidden;
    }

    /**
     * hide/show Menu Item
     */
    virtual void hide(bool invisibile=true) {
        _hidden=invisibile;
    }


    /**
     * Returns this item's parent item or 0 if it is a toplevel item.
     **/
    YMGAMenuItem * parent() const
    {
        return dynamic_cast<YMGAMenuItem *> ( YMenuItem::parent() );
    }


private:
    YMGAMenuItem( const YMGAMenuItem &	item );

    bool _enabled;
    bool _hidden;
};


#endif // YMGAMenuItem_h
