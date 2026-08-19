/*
 * (c) Copyright Ascensio System SIA 2010-2023
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#pragma once

#include "XMLMap.h"
#include "XLSXTableController.h"

#include "../../../../../DesktopEditor/xml/include/xmlutils.h"
#include "../../../../Base/Base.h"

#include <string>
#include <vector>
#include <set>
#include <map>

/// @brief class - a wrapper over xmlLiteReader for turning xml nodes into table rows
class XMLConverter
{
public:

    /// @brief constructor that loads the reader with the read xml into the object
    /// @param reader xmlLiteReader with xml document loaded into it
    /// @param xmlStruct pointer to the root node of the xml document structure
    /// @param nameController a name controller filled with column names
    /// @param repeatebleValues a set with repeating columns intended to form table rows
    XMLConverter(XmlUtils::CXmlLiteReader &reader, std::shared_ptr<XmlNode> xmlStruct, ColumnNameController &nameController,
    std::set<std::wstring> &repeatebleValues);

    /// @brief method converting xml to table view
    /// @param table xlsx table controller
    void ConvertXml(XLSXTableController &table);

private:

    /// @brief reads the attributes of the current node
    void readAttributes();

    /// @brief handles opening the current node
    void openNode();

    /// @brief handles closing the current node
    void closeNode();

    /// @brief checking the node for the ability to insert its data into the table and then inserting it if successful
    /// @param type type of node being processed
    void storeData(const XmlUtils::XmlNodeType &type);

    /// @brief fills the passed map with data
    /// @param row map into which the data and corresponding column numbers will be placed
    /// @return the number of the inserted row
    void insertRow(std::map<_UINT32, std::wstring> &row);

    /// @brief inserts a value into a temporary internal structure
    /// @param key the key by which the value will be inserted
    /// @param value the value to be inserted
    void insertValue(const std::wstring &key, const std::wstring &value);

    /// @brief Getting a unique node name
    /// @param name node name read from xml
    /// @return the found or generated unique node name
    std::wstring getNodeName(const std::wstring &name);

    /// @brief populates a table row with attributes
    /// @param table xlsx table controller
    /// @param attribNode the node from which the attributes will be taken
    /// @param filledValues set which stores the names of the filled columns
    /// @param arowNumber row number in the xlsx table
    void fillAttribures(XLSXTableController &table, std::shared_ptr<XmlNode> attribNode, std::set<std::wstring> &filledValues,
        const _UINT32 &rowNumber);

    /// @brief filling the attributes of child nodes with parent ones if the parent node doesn't appear as a separate line
    /// @param childs child nodes whose attributes need to be filled with parent ones
    /// @param inheritersCount number of nodes to which the parent's attributes will be distributed
    void moveParentAttributes(const std::shared_ptr<XmlNode> parent, const std::set<std::shared_ptr<XmlNode>>childs, const _UINT32 inheritersCount);

    /// @brief pointer to the reader that read the xml data
    XmlUtils::CXmlLiteReader *reader_;

    /// @brief vector with parent nodes
    std::vector<std::shared_ptr<XmlNode>> parents_;

    /// @brief map with a set of keys in the form of unique names and their values for insertion into the table
    std::map<std::wstring, std::vector<std::wstring>> data_;

    /// @brief table column name controller
    ColumnNameController *colNames_;

    /// @brief a set containing a list of columns of nodes that occur several times
    std::set<std::wstring> *listableColumns_;

    /// @brief node tree of xml document
    std::shared_ptr<XmlNode> nodeTree_;

    /// @brief pointer to the current node in the structure
    std::shared_ptr<XmlNode> nodePointer_;

    /// @brief type of the previous node (to search for nodes like <node></node>)
    XmlUtils::XmlNodeType prevType_ = XmlUtils::XmlNodeType::XmlNodeType_None;

    /// @brief vector with nodes of the lines being written
    std::vector<std::shared_ptr<XmlNode>> writingRows_;
    /// @brief vector with pointers to duplicate nodes that were currently open
    std::map<std::shared_ptr<XmlNode>, _UINT32> openednodes_;

};
