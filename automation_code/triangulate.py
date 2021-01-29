from sys import argv
import bpy
import glob
from pathlib import Path
from subprocess import call

"""
Script to triangulate meshes using Blender
to run: have Blender in path variables
replaces the paths in the variable below
and run Blender --background --python traingulate.py <folder of source meshes> <export folder>

trangulation happens during the export step with:
use_triangles=True
"""

import_mesh_folder = str(Path(argv[-2]).resolve()) # "/Users/vincentschmid/Documents/coding/games/testGame/assets/3DNaturePack/Models"
export_mesh_folder = str(Path(argv[-1]).resolve()) # "/Users/vincentschmid/Documents/coding/games/raylib-game/assets/3DNaturePack/Models"

print(import_mesh_folder)
print(export_mesh_folder)

def clearScene():
    bpy.ops.wm.read_homefile(use_empty=True)


def obj_import_mesh(filepath):
    bpy.ops.import_scene.obj(
        filepath=str(Path(filepath).resolve())
    )


def obj_export_scene(filepath):
    bpy.ops.export_scene.obj(
        filepath=str(Path(filepath).resolve()),
        use_triangles=True,
        use_materials=True
    )


def glb_export_scene(filepath):
    bpy.ops.export_scene.gltf(export_format='GLB', 
        export_texture_dir='', export_colors=True, 
        export_selected=False, export_yup=False, 
        filepath=str(Path(filepath).resolve()))


for file in glob.glob(import_mesh_folder + "/*.obj"):
    export_file = Path(export_mesh_folder).joinpath(Path(file).stem)
    obj_import_mesh(file)
    glb_export_scene(export_file)
    clearScene()
