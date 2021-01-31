from sys import argv

import bpy
import glob
from pathlib import Path
from subprocess import call

"""
Script to triangulate meshes using Blender
to run: have Blender in path variables
replaces the paths in the variable below
and run Blender --background --python traingulate.py -- -it <import type> -et <export type> t (to tringulate) -if <folder of source meshes> -ef <export folder>
"""

# PARSING FUNCTIONS

def parse_argv(args):
    commands = {}
    for i, arg in enumerate(args):
        if "-" in arg:
            commands[arg[1:]] = args[i+1]

    return commands


def check_commands(commands, required_commands):
    for required_comm in required_commands:
        if not required_comm in commands.keys():
            return required_comm

    return None


# BLENDER FUNCTIONS

def clearScene():
    bpy.ops.wm.read_homefile(use_empty=True)


def triangulate_object(obj):
    me = obj.data
    bm = bmesh.new()
    bm.from_mesh(me)

    bmesh.ops.triangulate(bm, faces=bm.faces[:], quad_method=0, ngon_method=0)

    bm.to_mesh(me)
    bm.free()


def obj_import_mesh(filepath):
    bpy.ops.import_scene.obj(
        filepath=str(Path(filepath).resolve())
    )


def fbx_import_mesh(filepath):
    bpy.ops.import_scene.fbx(
        filepath=str(Path(filepath).resolve()),
        axis_forward="-Z",
        axis_up="Y",
    )


def obj_export_scene(filepath, traingulate):
    bpy.ops.export_scene.obj(
        filepath=str(Path(filepath).resolve()) + ".obj",
        use_triangles=traingulate,
        use_materials=True,
        axis_forward="-Z",
        axis_up="Y",
    )


def glb_export_scene(filepath, triangulate):
    if triangulate:
        for obj in bpy.data.objects:
            triangulate(obj)

    bpy.ops.export_scene.gltf(export_format='GLB', 
        export_texture_dir='', export_colors=True, 
        export_selected=False, export_yup=False, 
        filepath=str(Path(filepath).resolve())
    )


def run(import_type, import_function, export_function, import_folder, eport_folder, triangulate):
    for file in glob.glob(import_mesh_folder + f"/*.{import_type}"):
        export_file = Path(export_mesh_folder).joinpath(Path(file).stem)
        import_function(file)
        export_function(export_file, triangulate)
        clearScene()


commands = parse_argv(argv)
missing_comm = check_commands(commands, ["it", "et", "if", "ef"])

if not missing_comm is None:
    print(f"+{missing_comm} flag is missing" )

else:
    traingulate = "t" in commands.keys()

    import_type = commands["it"]
    import_function = obj_import_mesh if import_type == "obj" else fbx_import_mesh

    export_type = commands["et"]
    if export_type == "obj":
        export_function = obj_export_scene
    if export_type in ["glb", "gltf"] :
        export_function = glb_export_scene


    import_mesh_folder = str(Path(commands["if"]).resolve()) # "/Users/vincentschmid/Documents/coding/games/testGame/assets/3DNaturePack/Models"
    export_mesh_folder = str(Path(commands["ef"]).resolve()) # "/Users/vincentschmid/Documents/coding/games/raylib-game/assets/3DNaturePack/Models"
    
    run(import_type, import_function, export_function, import_mesh_folder, export_mesh_folder, traingulate)
