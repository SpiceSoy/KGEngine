# 필터 제네레이터 버전 2

import os
import xml.dom.minidom
from xml.etree.ElementTree import Element, SubElement, ElementTree


project_file_dir = "..\\..\\"
project_file_path = r"..\..\KGEngine.vcxproj"
project_filter_path = r"..\..\KGEngine.vcxproj.filters"
src_root_dir_path = r"..\..\Source"
relative_path = os.path.relpath(src_root_dir_path, project_file_dir)
extensions = "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx;h;hh;hpp;hxx;hm;inl;inc;ipp;xsd;rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms;"

file_list = []

os.chdir(os.path.dirname(os.path.abspath(__file__)))


# XML 에 필터 등록
def add_filter(in_element_item_group, in_folder_name):
    element_filter = Element("Filter")
    element_filter.set("Include", in_folder_name)

    element_extensions = Element("Extensions")
    element_extensions.text = extensions

    element_filter.append(element_extensions)

    in_element_item_group.append(element_filter)
    return


# XML 에 파일 추가
def add_file(in_element_item_group, in_file_name, in_filter_name):
    element_file = Element("ClCompile")
    element_file.set("Include", in_file_name)

    element_filter = Element("Filter")
    element_filter.text = in_filter_name

    element_file.append(element_filter)

    in_element_item_group.append(element_file)
    return


root_element = Element("Project")
root_element.set("ToolsVersion", "4.0")
root_element.set("xmlns", "http://schemas.microsoft.com/developer/msbuild/2003")

filter_item_group = Element("ItemGroup")
root_element.append(filter_item_group)

include_item_group = Element("ItemGroup")
root_element.append(include_item_group)

for (root, directories, files) in os.walk(src_root_dir_path):
    for d in directories:
        d_path = os.path.join(root, d)
        folder_name = d_path.replace(src_root_dir_path, "").lstrip("\\")
        add_filter(filter_item_group, folder_name)
        print(f"Add filter [ {folder_name} ]")

    for file in files:
        file_path = os.path.join(root, file)
        replaced_path = file_path.replace(src_root_dir_path, "").lstrip("\\")
        file_name = replaced_path[replaced_path.rfind("\\") + 1:]
        if replaced_path == file_name:
            filter_name = "root"
        else:
            filter_name = replaced_path[:replaced_path.rfind("\\")]
        extension = file_name[file_name.rfind(".") + 1:]
        add_file(include_item_group, relative_path + "\\" + filter_name + "\\" + file_name, filter_name)
        added_name = (relative_path + "\\" + filter_name + "\\" + file_name)
        file_list.append(added_name)
        print(f"Add File [ {added_name} ] In  Filter [ {filter_name} ]")
        print(file_list)

tree = ElementTree(root_element)

print(f"Open Project Filter from {project_filter_path}")

with open(project_filter_path, "wb") as file:
    tree.write(file, encoding='utf-8', xml_declaration=True)

dom = xml.dom.minidom.parse(project_filter_path)
pretty_xml_as_string = dom.toprettyxml()

with open(project_filter_path, "wb") as file:
    file.write(pretty_xml_as_string.encode('utf-8'))

print(f"Save Project Filter to {project_filter_path}")

print(f"Open Project File From {project_file_path}")

xml.etree.ElementTree.register_namespace('', "http://schemas.microsoft.com/developer/msbuild/2003")

project_tree = ElementTree()
project_tree.parse(project_file_path)


project_root = project_tree.getroot()


for project_item_group in project_root.findall("{http://schemas.microsoft.com/developer/msbuild/2003}ItemGroup"):
    if len(project_item_group.attrib) == 0:
        project_item_group.clear()
        for project_add_file in file_list:
            print(f"Add File {project_add_file} In Project File")
            project_file_element = Element("ClCompile")
            project_file_element.set("Include", project_add_file)
            project_item_group.append(project_file_element)


with open(project_file_path, "wb") as file:
    project_tree.write(file, encoding='utf-8')



print(f"Save Project File To {project_file_path}")