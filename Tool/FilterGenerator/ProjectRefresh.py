# 솔루션 경로 상 프로젝트 수집 및 필터 제네레이팅
# ProjectRefresh [ProjectDir] [srcDir]

import os
import xml.dom.minidom
from xml.etree.ElementTree import Element, SubElement, ElementTree

# project_root_dir, src_root = input().split()

project_root_dir = r"F:\Workspace\KGEngine\Project"
src_root = r"F:\Workspace\KGEngine\Source"
project_list = []
extension = ".vcxproj"

os.chdir(os.path.dirname(os.path.abspath(__file__)))


def do_generate_filter(project_name):
    command = f"GenerateFilter.py {project_name} {project_root_dir} {src_root}"
    print( f"do command {command}")
    os.system(command)


for (root, directories, files) in os.walk(project_root_dir):
    for file in files:
        name, ext = os.path.splitext(file)
        if ext == extension:
            do_generate_filter(name)

