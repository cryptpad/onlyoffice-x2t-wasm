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

#include "columnNamesController.h"

#include "../../../../../DesktopEditor/xml/include/xmlutils.h"
#include "../../../../Base/Base.h"

#include <string>
#include <vector>
#include <set>
#include <map>
#include  <utility>

/// @brief class - a wrapper over xmlLiteReader for turning xml nodes into table rows
class XML2TableConverter
{
public:

    /// @brief constructor that loads the reader with the read xml into the object
    /// @param reader xmlLiteReader with xml document loaded into it
    XML2TableConverter(XmlUtils::CXmlLiteReader &reader);

    /// @brief method that reads the next row from xml
    /// @param string map with string data as keys and their column numbers to insert as values
    /// @return line number in case of successful reading or -1 in case of error
    bool ReadNextElement(std::map<_UINT32, std::wstring> &string);

private:

    /// @brief reads the attributes of the current node
    void readAttributes();

    /// @brief handles the current node
    /// @param type type of node being processed
    /// @return true if the nodes within the line have been read and it can exit, otherwise false
    void processNode(const XmlUtils::XmlNodeType &type);

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

    /// @brief inserts the name of an empty node
    /// @param key node name
    void insertEmptyNode(const std::wstring &key);

    /// @brief inserts a node attribute into a temporary internal structure
    /// @param key the key by which the value will be inserted
    /// @param value the value to be inserted
    void insertAttribute(const std::wstring &key, const std::wstring &value);

    /// @brief populates the map with the collected column names to insert them into the table
    /// @param names map with column names
    void insertColumnNames(std::map<_UINT32, std::wstring> &names);

    /// @brief Receiving a unique node name, or searching for it in the passed set
    /// @param name node name read from xml
    /// @param names set containing unique names among which the search will be carried out
    /// @return the found or generated unique node name
    std::wstring getNodeName(const std::wstring &name, std::set<std::wstring> &names);

    /// @brief pointer to the reader that read the xml data
    XmlUtils::CXmlLiteReader *reader_;

    /// @brief vector with parent nodes and names used at their levels
    std::vector<std::pair<std::wstring, std::set<std::wstring>>> parents_;

    /// @brief map with a set of keys in the form of unique names and their values for insertion into the table
    std::map<std::wstring, std::wstring> keyvalues_;

    /// @brief table column name controller
    ColumnNameController colNames_;

    /// @brief map into which data is output when reading a node
    std::map<_UINT32, std::wstring> stringBuffer_;

    /// @brief type of the previous node (to search for nodes like <node></node>)
    XmlUtils::XmlNodeType prevType_ = XmlUtils::XmlNodeType::XmlNodeType_None;

};