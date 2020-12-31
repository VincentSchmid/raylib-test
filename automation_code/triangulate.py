import bpy
import glob
from pathlib import Path
from subprocess import call


import_mesh_folder = "/Users/vincentschmid/Documents/coding/games/testGame/assets/3DNaturePack/Models"
export_mesh_folder = "/Users/vincentschmid/Documents/coding/games/raylib-game/assets/3DNaturePack/Models"


def get_all_objects_in_scene():
    return [obj for obj in bpy.data.objects]


def get_new_objects_in_scene(old_objects):
    current_objects = get_all_objects_in_scene()
    new_objects = []
    for obj in current_objects:
        if obj not in old_objects:
            new_objects.append(obj)

    return new_objects


def clearScene():
    bpy.ops.wm.read_homefile(use_empty=True)


def obj_import_mesh(filepath):
    objs = get_all_objects_in_scene()
    bpy.ops.import_scene.obj(
        filepath=str(Path(filepath).resolve())
    )
    return get_new_objects_in_scene(objs)


def obj_export_scene(filepath):
    bpy.ops.export_scene.obj(
        filepath=str(Path(filepath).resolve()),
        use_triangles=True,
        use_materials=True
    )


for file in glob.glob(import_mesh_folder + "/*.obj"):
    export_file = Path(export_mesh_folder).joinpath(Path(file).name)
    obj = obj_import_mesh(file)[0]
    obj_export_scene(export_file)
    clearScene()
