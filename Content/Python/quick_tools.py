import unreal

def populate_the_level(num_actor = 10000, mesh = '/Engine/BasicShapes/Cube.Cube', radius = 128000):
    desired_world_box_extent = unreal.Vector(radius, radius, radius)
    
    for i in range(0, num_actor):
        spawn_location = unreal.Vector().random_point_in_box_extents(desired_world_box_extent)
        spawn_rotation = unreal.MathLibrary.random_rotator(True)
        spawned_actor = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.StaticMeshActor.static_class(), spawn_location, spawn_rotation)
        static_mesh = unreal.EditorAssetLibrary.load_asset(mesh)
        spawned_actor.static_mesh_component.set_editor_property('static_mesh', static_mesh)

def pack_all(cell_size = 6400.0):
    world = unreal.UnrealEditorSubsystem().get_editor_world()
    actors = unreal.GameplayStatics.get_all_actors_of_class(world, unreal.StaticMeshActor.static_class())
    
    level_bounds = unreal.GameplayStatics.get_actor_array_bounds(actors, False)
    bounds_min = level_bounds.origin - level_bounds.box_extent
    bounds_max = level_bounds.origin + level_bounds.box_extent

    cells = {}
    cells['empty_cell'] = []

    for actor in actors:
        actor_location = actor.get_actor_location()
        x = int(actor_location.x / cell_size)
        y = int(actor_location.y / cell_size)
        z = int(actor_location.z / cell_size)
        cell_name = x + '_' + y + '_' + z

        if cell_name in cells:
            cells[cell_name].append(actor)
        else:
            cells[cell_name] = [ actor ]

    level_name = world.get_name()

    for cell_name in cells:
        packed_level_name = cell_name + "_Packed"
        actors_to_pack = cells[cell_name]

        unreal.WorldUtils.convert_actors_to_packed_level_instance(actors_to_pack, '/Game/Packed/' + str(level_name) + '/' + packed_level_name)

def unpack_all():
    level_instance = unreal.GameplayStatics.get_all_actors_of_class(unreal.EditorLevelLibrary.get_editor_world(), unreal.LevelInstance.static_class())
    return unreal.WorldUtils.break_level_instance(level_instance[0], 1)

def repack_all():
    unpack_all()
    pack_all()