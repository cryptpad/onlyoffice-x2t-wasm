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
#include <utility>
#include <memory>

/// @brief xml tree node
struct XmlNode
{
    /// @brief node name
    std::wstring name;
    /// @brief ancestor node
    std::shared_ptr<XmlNode> parent;
    /// @brief node attributes
    std::set<std::wstring> attributes;
    /// @brief name of the node data column, empty if the node has no data
    std::wstring ValueColumnName;
    /// @brief inherited node columns
    std::set<std::wstring> childColumns;
    /// @brief descendants of the node
    std::set<std::shared_ptr<XmlNode>> childs;
    /// @brief node repetition counter to extend one node instead of using many with the same name
    _UINT32 counter;
    /// @brief all ancestor nodes
    std::set<std::shared_ptr<XmlNode>> parents;
};


/// @brief class that reads an xml file and builds its table structure for further conversion
class XMLMap
{
public:
    /// @brief method that reads the xml file structure
    /// @param reader xmlLiteReader with xml document loaded into it
    /// @param nameController name controller into which column names will be loaded
    /// @param nodeTree pointer to the root element of the node tree that will be filled by this method
    /// @return true if successful, false otherwise
    bool ReadXmlStructure(XmlUtils::CXmlLiteReader &reader, ColumnNameController &nameController, std::shared_ptr<XmlNode> nodeTree,
    std::set<std::wstring> &repeatebleValues);

private:

    /// @brief reads the attributes of the current node
    void readAttributes();

    /// @brief processes a node of type element
    /// @param type type of node being processed
    void openNode();

    /// @brief processes a node of type endelement
    /// @param type type of node being processed
    void closeNode();

    /// @brief inserts a value into a temporary internal structure
    void insertValue();

    /// @brief inserts an attribute into the node's temporary internal structure
    /// @param key the key by which the value will be inserted
    void insertAttribute(const std::wstring &key);

    /// @brief Receiving a unique node name, or searching for it in the passed set
    /// @param name node name read from xml
    /// @param names set containing unique names among which the search will be carried out
    /// @return the found or generated unique node name
    std::wstring getNodeName(const std::wstring &name, std::set<std::wstring> &names);

    /// @brief searches at the top level for a node with the passed name, used to count table rows
    /// @param name node name
   std::shared_ptr<XmlNode> searchSameNode(const std::wstring &name);

    /// @brief pointer to the reader that read the xml data
    XmlUtils::CXmlLiteReader *reader_;

    /// @brief pointer to the table column name controller
    ColumnNameController *colNames_;

    /// @brief vector with parent nodes and names used at their levels
    std::vector<std::shared_ptr<XmlNode>> parents_;

    /// @brief type of the previous node (to search for nodes like <node></node>)
    XmlUtils::XmlNodeType prevType_ = XmlUtils::XmlNodeType::XmlNodeType_None;

    /// @brief columns of values whose nodes were repeated more than once
    std::set<std::wstring> *repeatebleValues_;

};