#include <iostream>
#include "../../../DesktopEditor/xml/include/xmlutils.h"
#include "../../../DesktopEditor/common/File.h"

int main()
{
    // sax reader
    XmlUtils::CXmlLiteReader oLightReader;
    /*
    Conclusions:
    Returns the success of opening a file
    Reads a file into the m_pStream stream
    Stream length in m_lStreamLen
    Forms reader
    After reading the file is closed
    Thoughts:
    xmlreader.h - functions for working with xml
    */
    bool res1 = oLightReader.FromFile(NSFile::GetProcessDirectory() + L"/../../../examples/test.xml");
    std::wcout << res1 << std::endl; // true

    /*
    Returns the node's ordinal number (I think not)
    Thoughts:
    Returns XmlNodeType_None(0)
    */
    XmlUtils::XmlNodeType res2 = oLightReader.GetNodeType();
    std::wcout << res2<< " " << oLightReader.GetName() << std::endl; // Index 0 is unused because current node is missing

    /*
    GetName() - returns the name of the current node
    GetDepth() - returns the depth of the current node
    */

    /*
    Returns the success of reading a node of the specified type
    By reference, saves the node type
    Thoughts:
    The value XmlNodeType_None(0) is converted to XmlNodeType_Element(1)
    */
    bool res3 = oLightReader.Read(res2); // Will read company
    std::wcout << res3 << " " << res2 << " " << oLightReader.GetName() << std::endl; // true 1

    /*
    Thoughts:
    Returns the success of reading the next node
    In the reader, the depth changes if the node is nested
    And the current node
    */
    bool res4 = oLightReader.ReadNextNode(); // Will read staff
    std::wcout << res4 << " " << oLightReader.GetName() << std::endl; // true
    bool res5 = oLightReader.ReadNextNode(); // Will read firstname
    std::wcout << res5 << " " << oLightReader.GetName() << std::endl; // true

    /*
    Returns the success of reading the next node at the same depth - 1
    External tag does not count
    */
    bool res6 = oLightReader.ReadNextSiblingNode(1); // Read lastname
    std::wcout << res6 << " " << oLightReader.GetName() << std::endl; // true
    //bool res7 = oLightReader.ReadNextSiblingNode(1); // Read the closing staff
    //std::wcout << res7 << std::endl; // false, because read node at a different depth

    /*
    Thoughts:
    Forces reading of a node at the same depth
    If there is no node, then creates a text node
    */
    bool res7 = oLightReader.ReadNextSiblingNode2(1); // Read the text node; its grandparent will be staff
    std::wcout << res7 << " " << oLightReader.GetName() << std::endl; // true

    return 0;
}
