import bpy
import glob
from pathlib import Path
from subprocess import call

"""
Script to triangulate meshes using Blender
to run: have Blender in path variables
replaces the paths in the variable below
and run Blender --background --python traingulate.py

trangulation happens during the export step with:
use_triangles=True
"""

import_mesh_folder = "/Users/vincentschmid/Documents/coding/games/testGame/assets/3DNaturePack/Models"
export_mesh_folder = "/Users/vincentschmid/Documents/coding/games/raylib-game/assets/3DNaturePack/Models"


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


for file in glob.glob(import_mesh_folder + "/*.obj"):
    export_file = Path(export_mesh_folder).joinpath(Path(file).name)
    obj_import_mesh(file)
    obj_export_scene(export_file)
    clearScene()
