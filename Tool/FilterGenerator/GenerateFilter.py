# 필터 제네레이터
# GenerateFilter project_name, project_root_dir, src_root

import os
import sys
import xml.dom.minidom
from xml.etree.ElementTree import Element, ElementTree

# if len(sys.argv) != 4:
#     print("argument must 4 count (project_name, project_root_dir, src_root)")
#     print(f"current count = {len(sys.argv)}")
#     exit(0)
#
# project_name, project_root_dir, src_root = [sys.argv[1], sys.argv[2], sys.argv[3]]

project_root_dir = r"F:\Workspace\KGEngine\Project"
project_name = r"KGEngine"
src_root = r"F:\Workspace\KGEngine\Source"

project_dir = project_root_dir + "\\" + project_name
project_path = project_dir + "\\" + project_name + ".vcxproj"
src_dir = src_root + "\\" + project_name
filter_file_path = project_path + ".filters"
rel_path = os.path.relpath(src_dir, project_dir)
extensions = "cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx;h;hh;hpp;hxx;hm;inl;inc;ipp;xsd;"

file_list = []


def add_filter(item_group_element, in_folder_name):
    filter_element = Element("Filter")
    filter_element.set("Include", in_folder_name)

    extensions_element = Element("Extensions")
    extensions_element.text = extensions

    filter_element.append(extensions_element)

    item_group_element.append(filter_element)
    return


def add_file(item_group_include, in_file_name, in_filter_name):
    file_element = Element("ClCompile")
    file_element.set("Include", in_file_name)

    filter_element = Element("Filter")
    filter_element.text = in_filter_name

    file_element.append(filter_element)

    item_group_include.append(file_element)
    return


root_element = Element("Project")
root_element.set("ToolsVersion", "4.0")
root_element.set("xmlns", "http://schemas.microsoft.com/developer/msbuild/2003")

filter_item_group = Element("ItemGroup")
root_element.append(filter_item_group)

include_item_group = Element("ItemGroup")
root_element.append(include_item_group)

for (root, directories, files) in os.walk(src_dir):
    for d in directories:
        d_path = os.path.join(root, d)
        folder_name = d_path.replace(src_dir, "").lstrip("\\")
        add_filter(filter_item_group, folder_name)
        print(f"Add filter [ {folder_name} ]")

    for file in files:
        file_path = os.path.join(root, file)
        replaced_path = file_path.replace(src_dir, "").lstrip("\\")
        file_name = replaced_path[replaced_path.rfind("\\") + 1:]
        if replaced_path == file_name:
            filter_name = "root"
        else:
            filter_name = replaced_path[:replaced_path.rfind("\\")]
        extension = file_name[file_name.rfind(".") + 1:]
        add_file(include_item_group, rel_path + "\\" + filter_name + "\\" + file_name, filter_name)
        added_name = (rel_path + "\\" + filter_name + "\\" + file_name)
        file_list.append(added_name)
        print(f"Add File [ {added_name} ] In  Filter [ {filter_name} ]")
        print(file_list)

tree = ElementTree(root_element)

print(f"Open Project Filter from {filter_file_path}")

with open(filter_file_path, "wb") as file:
    tree.write(file, encoding='utf-8', xml_declaration=True)

dom = xml.dom.minidom.parse(filter_file_path)
pretty_xml_as_string = dom.toprettyxml()

with open(filter_file_path, "wb") as file:
    file.write(pretty_xml_as_string.encode('utf-8'))

print(f"Save Project Filter to {filter_file_path}")

print(f"Open Project File From {project_path}")

xml.etree.ElementTree.register_namespace('', "http://schemas.microsoft.com/developer/msbuild/2003")

project_tree = ElementTree()
project_tree.parse(project_path)


project_root = project_tree.getroot()


for project_item_group in project_root.findall("{http://schemas.microsoft.com/developer/msbuild/2003}ItemGroup"):
    if len(project_item_group.attrib) == 0:
        project_item_group.clear()
        for project_add_file in file_list:
            print(f"Add File {project_add_file} In Project File")
            project_file_element = Element("ClCompile")
            project_file_element.set("Include", project_add_file)
            project_item_group.append(project_file_element)


with open(project_path, "wb") as file:
    project_tree.write(file, encoding='utf-8', xml_declaration=True)

print(f"Save Project File To {project_path}")