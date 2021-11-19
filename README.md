# Shpargle
Różne szpargały

Tools, workarounds, buttons, random stuff...

Also... Use with caution. Everything is considered experimental and hasn't been tested thoroughly. Some features may have been built for specific purposes and might not work for all cases.

## Features
*Thy shall seek the truth in the Source*

I mean, this list might be outdated a bit at times, but I'll try to keep it up!

### Editor Tools
* Restart Editor Button (`File > Restart Editor`)

### Editor Utility Widgets
* Toolbox (`/ShpargleEditor/EditorWidgets/Toolbox`)
  
  *Right-Click* the asset and select *Run Editor Utility Widget*

### World Utils
Functions exposed to Blueprints / Python
* Add Static Mesh Component To Actor
  ```python
  unreal.WorldUtils.add_static_mesh_component_to_actor(target_actor, name, mesh, relative_transform)
  ```
  Adds a `StaticMeshComponent` to an `Actor` on the level in such a way so that it is later editable in the editor
* Get World Partition
  ```python
  unreal.WorldUtils.get_world_partition()
  ```
  Returns `WorldPartition`
* Convert Actors To Packed Level Instance
  ```python
  unreal.WorldUtils.convert_actors_to_packed_level_instance(actors, path)
  ```
  Returns `LevelInstance`
* Move Actors To Level
  ```python
  unreal.WorldUtils.move_actors_to_level(level_instance_actor, actors_to_move)
  ```
  Returns `True` if operation was successfull, or `False` otherwise
* Break Level Instance
  ```python
  unreal.WorldUtils.break_level_instance(level_instance_actor, levels)
  ```
  Returns a list of extracted `Actor`s
* Load/Unload World Partition Cell
  ```python
  unreal.WorldUtils.load_world_partition_cell(selected_box)
  ```
  Does the same thing as corresponding context menu actions in World Partition window
* Load/Unload World Partition Cell Light
  ```python
  unreal.WorldUtils.load_world_partition_cell_light(selected_box)
  ```
  Same as above, but skips calling redraw on level viewports
* Load/Unload World Partition Cell Superlight
  ```python
  unreal.WorldUtils.load_world_partition_cell_superlight(selected_box, world_partition)
  ```
  Same as above, but requires providing `world_partition`, so a cached value can be used

### Asset Utils
Functions exposed to Blueprints / Python
* Create Blueprint
  ```python
  unreal.WorldUtils.create_blueprint(path, prent_class, istance_components)
  ```
  Returns created `Blueprint` asset
  
  Creates a Blueprint class with components from the `istance_components` list added
* Create Actor Blueprint
  ```python
  unreal.WorldUtils.create_actor_blueprint(path)
  ```
  Returns created `Blueprint` asset
  
  Creates a basic `Actor`-based Blueprint class
* Delete Asset
  ```python
  unreal.WorldUtils.delete_asset(path)
  ```
  Deletes an asset at specified `path`

### Python Scripts
#### Quick Tools
```python
import quick_tools
```

* `quick_tools.populate(num_actors = 1000, mesh = '/Engine/BasicShapes/Cube.Cube', radius = 12800)`
  
  Populates the level with randomly distributed `num_actors` instances of a `StaticMeshActor` with random transform in `radius` and the Static Mesh property set to `mesh`

* `quick_tools.pack_all(cell_size = 6400.0)`

  Packs all the loaded meshes into `PackedLevelInstances` based on their location and the grid with a cell size of `cell_size`

  This will only iterate through lonely `StaticMeshActors` and add them into appropriate `PackedLevelInstance` or create a new one if necessary

* `quick_tools.break_all()`

  This will break all level instances into the level and *delete(!)* the level assets from the project, so that later there shouldn't be any collisions with exisiting assets with the same names

* `quick_tools.repack_all(cell_size = 6400.0)`

  Calls `break_all()` and `pack_all(cell_size)` back to back.

#### World Tools
```python
import world_tools
```

* `world_tools.combine_selected_actors()`

  Combines selected meshes into a single `CombinedStaticMeshActor` with `StaticMeshComponent`s instead

* `world_tools.break_selected_actors()`

  Breaks selected `StaticMeshActor`s and drops the `StaticMeshComponent`s into the level as individual `StaticMeshActor`s 
