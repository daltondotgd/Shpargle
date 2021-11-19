import unreal

def convert_all_meshes_to_static(save_every=3000):
    editor_filter_lib = unreal.EditorFilterLibrary()
    editor_level_lib = unreal.EditorLevelLibrary()

    actors = editor_level_lib.get_all_level_actors()
    static_mesh_actors = editor_filter_lib.by_class(actors, unreal.StaticMeshActor)

    with unreal.ScopedSlowTask(len(static_mesh_actors), "Setting mobility to Static") as slow_task:
        slow_task.make_dialog(True)
        i = 0
        num_processed_actors = 0
        for actor in static_mesh_actors:
            if slow_task.should_cancel():
                break

            num_processed_actors += 1
            slow_task.enter_progress_frame(1, "Setting mobility to Static " + "(" + str(num_processed_actors) + "/" + str(len(static_mesh_actors)) + ")")

            i += 1
            static_mesh_components = actor.get_components_by_class(unreal.StaticMeshComponent)

            with unreal.ScopedSlowTask(len(static_mesh_components), "Processing " + actor.get_name()) as process_components_task:
                process_components_task.make_dialog(True)
                num_processed_components = 0
                for component in static_mesh_components:
                    process_components_task.enter_progress_frame(1, "Processing " + actor.get_name() + " -> " + component.get_name() + "(" + str(num_processed_components) + "/" + str(len(static_mesh_components)) + ")")
                    component.set_editor_property("mobility", unreal.ComponentMobility.STATIC)
                    num_processed_components += 1

            if i > save_every:
                unreal.EditorLoadingAndSavingUtils.save_dirty_packages(True, True)
                i = 0

    unreal.EditorLoadingAndSavingUtils.save_dirty_packages(True, True)