import unreal

def populate(num_actors = 1000, mesh = '/Engine/BasicShapes/Cube.Cube', radius = 12800):
    desired_world_box_extent = unreal.Vector(radius, radius, radius)
    
    with unreal.ScopedSlowTask(num_actors, 'Populating worlds with actors') as populate_task:
        populate_task.make_dialog(True)
        for i in range(0, num_actors):
            populate_task.enter_progress_frame(1, 'Populating world with actors: ' + str(i) + '/' + str(num_actors))
            spawn_location = unreal.Vector().random_point_in_box_extents(half_size=desired_world_box_extent)
            spawn_rotation = unreal.MathLibrary.random_rotator(True)
            spawned_actor = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.StaticMeshActor.static_class(), spawn_location, spawn_rotation)
            static_mesh = unreal.EditorAssetLibrary.load_asset(mesh)
            spawned_actor.static_mesh_component.set_editor_property('static_mesh', static_mesh)

def pack_all(cell_size = 6400.0):
    world = unreal.UnrealEditorSubsystem().get_editor_world()
    static_mesh_actors = unreal.GameplayStatics.get_all_actors_of_class(world, unreal.StaticMeshActor.static_class())

    def build_existing_levels_dict():
        result = {}
        existing_level_actors = unreal.GameplayStatics.get_all_actors_of_class(unreal.EditorLevelLibrary.get_editor_world(), unreal.LevelInstance.static_class())
        for level in existing_level_actors:
            result[level.get_actor_label()] = level

        return result

    existing_level_instances = build_existing_levels_dict()    
    
    level_bounds = unreal.GameplayStatics.get_actor_array_bounds(static_mesh_actors, False)
    level_size = level_bounds[1].multiply_float(2.0)
    cell_count = int(level_size.x / cell_size) * int(level_size.y / cell_size) * int(level_size.z / cell_size)

    cells = {}
    cells['empty_cell'] = []

    with unreal.ScopedSlowTask(cell_count, 'Processing cells') as process_cells_task:
        progress = 0
        process_cells_task.make_dialog(True)
        for actor in static_mesh_actors:
            if process_cells_task.should_cancel():
                return

            actor_location = actor.get_actor_location()
            x = int(actor_location.x / cell_size)
            y = int(actor_location.y / cell_size)
            z = int(actor_location.z / cell_size)
            cell_name = str(x) + '_' + str(y) + '_' + str(z)

            process_cells_task.enter_progress_frame(1, 'Processing cells: ' + str(progress) + '/' + str(cell_count) + ' (' + str(cell_name) + ')')

            if cell_name in cells:
                cells[cell_name].append(actor)
            else:
                cells[cell_name] = [ actor ]

            progress += 1

        level_name = world.get_name()

    cell_count = len(cells)
    with unreal.ScopedSlowTask(cell_count, 'Converting cells') as convert_cells_to_packed_task:
        progress = 0
        convert_cells_to_packed_task.make_dialog(True)
        for cell_name in cells:
            if process_cells_task.should_cancel():
                return

            packed_level_name = cell_name + '_Packed'
            actors_to_pack = cells[cell_name]
            
            if len(cells[cell_name]) == 0:
                progress += 1
                continue

            convert_cells_to_packed_task.enter_progress_frame(1, 'Converting cells: ' + str(progress) + '/' + str(cell_count) + ' (' + str(cell_name) + ')')
            new_instance_path = '/Game/Packed/' + str(level_name) + '/' + packed_level_name
            if cell_name in existing_level_instances:
                level_instance_actor = existing_level_instances[cell_name]
                result = unreal.WorldUtils.move_actors_to_level(level_instance_actor, actors_to_pack)
            else:
                level_instance_actor = unreal.WorldUtils.convert_actors_to_packed_level_instance(actors_to_pack, new_instance_path)
                if unreal.SystemLibrary.is_valid(level_instance_actor):
                    level_instance_actor.set_actor_label(cell_name, True)

            progress += 1
        
    unreal.EditorLoadingAndSavingUtils.save_dirty_packages(True, True)

def break_all():
    level_instances = unreal.GameplayStatics.get_all_actors_of_class(unreal.EditorLevelLibrary.get_editor_world(), unreal.LevelInstance.static_class())
    progress = 0
    num_instances = len(level_instances)
    with unreal.ScopedSlowTask(num_instances, 'Breaking cells') as break_all_task:
        break_all_task.make_dialog(True)
        level_name = unreal.UnrealEditorSubsystem().get_editor_world().get_name()
        # actors_to_delete = []
        assets_to_delete = []
        for level_instance in level_instances:
            break_all_task.enter_progress_frame(1, 'Breaking cells: ' + str(progress) + '/' + str(num_instances))
            instance_name = level_instance.get_actor_label()
            packed_levels_root_directory = unreal.Paths.normalize_directory_name('/Game/Packed')
            packed_levels_current_directory = unreal.Paths.normalize_directory_name(packed_levels_root_directory + '/' + str(level_name))
            
            if len(unreal.WorldUtils.break_level_instance(level_instance, 1)) != 0:
                unreal.EditorLevelLibrary.destroy_actor(level_instance)
                # actors_to_delete.append(level_instance)
                assets_to_delete.append(packed_levels_current_directory + '/' + str(instance_name) + '_Packed')

            progress += 1

        # unreal.WorldUtils.delete_actors(actors_to_delete)

        # packages_to_cleanup = []
        # for path in assets_to_delete:
        #     unreal.AssetUtils.delete_asset(path)
        #     packages_to_cleanup.append(unreal.load_package(path + '.' + str(level_name))) # wrong path
        # unreal.AssetUtils.cleanup_after_delete(packages_to_cleanup, False)

        # if not unreal.EditorAssetLibrary.does_directory_have_assets(packed_levels_current_directory):
        #     unreal.AssetUtils.delete_directory(packed_levels_current_directory)
        #     unreal.log(packed_levels_current_directory)
        #     if not unreal.EditorAssetLibrary.does_directory_have_assets(packed_levels_root_directory):
        #         unreal.AssetUtils.delete_directory(packed_levels_root_directory)
        #         unreal.log(packed_levels_root_directory)

        unreal.log("oops: " + packed_levels_root_directory + " exists? " + str(unreal.Paths.directory_exists(packed_levels_root_directory)))
        unreal.log("oops: " + packed_levels_current_directory + " exists? " + str(unreal.Paths.directory_exists(packed_levels_current_directory)))

def repack_all(cell_size = 6400.0):
    break_all()
    pack_all(cell_size)