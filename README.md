1. File Parsing (.cub Parser)
- Parses arguments (extension = .cub)
- Parses config lines (NO, SO, EA, WE, F, C)
- Parses map block (1/0/N/S/E/W/space)
- Ensures map is enclosed by walls and spaces are accounted for
- Handles whitespace and empty lines
- Fails gracefully with errors on misconfig

2. Game State Initialization
- Depends on: File Parsing
- Loads textures from valid paths
- Stores map in 2D structure (maybe a string with segmenter symbols)
- Validates & places player with correct orientation
- Converts F/C colors to RGB
 Prepares image buffers (mlx_xpm_file_to_image)

3. Raycasting Engine
- Depends on: Game State Initialization
- Uses math to cast rays
- Detects walls + which face is hit (N/S/E/W)
- Calculates distance to wall
- Projects vertical wall slice
- Picks correct texture for hit face

4. Rendering & Drawing
- Depends on: Raycasting Engine
- Draws wall slices with texture mapping
- Draws floor/ceiling colors
- Updates image buffer
- Handles minimize, focus change, expose
- Uses minilibx image functions (mlx_put_image_to_window)

5. Input Handling
- Depends on: Game State Init & Drawing
- W/A/S/D = position movement (collision detection)
- Left/Right = rotate direction vector
- ESC key = exit cleanly
- Clicking X = exit cleanly
- Optional: mouse rotation (bonus)

6. Program Lifecycle & Cleanup
- Depends on: All other modules
- Frees all heap memory
- Closes file descriptors
- Destroys MLX images and window
- Exits gracefully on all paths
 on all paths
