*This project has been created as part of the 42 curriculum by ymazzett, mabdur-r.*

## Description

**cub3D** is a Wolfenstein 3D-inspired first-person maze explorer written in C with the MiniLibX graphics library. The program parses a `.cub` scene file (textures, floor/ceiling colors, and a 2D map) and renders a real-time 3D view using **DDA ray-casting**.

## Build

The Makefile auto-detects the OS. From the project root:

| Target | What it does |
|--------|--------------|
| `make` | Build `cub3D` (auto OS detect) |
| `make re` | `fclean` + rebuild |
| `make clean` | Remove object files in `obj/` |
| `make fclean` | `clean` + remove the `cub3D` binary |

Compilation uses `-Wall -Wextra -Werror -g` and all source files follow the 42 **norminette** standard.

## Run

Always launch from the project root so relative texture paths inside `.cub` files resolve correctly:

```bash
./cub3D maps/subject.cub
./cub3D maps/simple.cub
./cub3D maps/explore_Maze.cub
./cub3D maps/explore_large_hall.cub
./cub3D maps/xtreme_case0.cub
```

Any map in `maps/` whose name starts with `explore_` is a valid runnable scene. Maps whose name starts with `invalid_` are used to exercise the parser error path (see below).

### Controls

| Key | Action |
|-----|--------|
| W / S | Move forward / backward |
| A / D | Strafe left / right |
| ← / → | Rotate view left / right |
| ESC | Quit |
| Window X button | Quit |

### Parser error testing

Invalid scene files must print `Error` followed by a message on stderr and exit non-zero without opening a window:

```bash
./cub3D maps/invalid_hole.cub          # map not closed
./cub3D maps/invalid_spawn.cub         # duplicated player spawn
./cub3D maps/invalid_missing_no.cub    # missing NO texture identifier
./cub3D maps/invalid_duplicate_no.cub  # duplicated NO identifier
./cub3D maps/invalid_bad_color.cub     # F/C color out of range
./cub3D maps/invalid_map_gap.cub       # empty line inside the map
./cub3D maps/invalid_open_side.cub     # map not enclosed by walls
./cub3D not_a_cub.txt                  # wrong extension
```

### Memory checking

The bundled MiniLibX allocates its display handle in `mlx_init`; the cleanup path calls `mlx_destroy_display` and then `free`s the handle from `destroy_display` in `includes/key_handling.h`, so a clean exit reports zero definitely-lost bytes:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/subject.cub
```

Any residual "still reachable" bytes come from libX11/libXext internal caches and are outside the program's ownership.

## `.cub` file format

A minimal scene contains four texture paths, two colors, and the 2D map:

```
NO textures/wall_n.xpm
SO textures/wall_s.xpm
WE textures/wall_w.xpm
EA textures/wall_e.xpm
F 220,100,0
C 225,30,0

1111111
1000001
100N001
1000001
1111111
```

- `NO / SO / WE / EA` — texture displayed when the player is facing that direction.
- `F R,G,B` and `C R,G,B` — floor and ceiling colors (each channel 0-255).
- The map uses `1` for walls, `0` for empty space, and exactly one of `N/S/E/W` for the player spawn (letter also encodes initial facing).
- The map **must be closed** by walls on all sides; any breach causes a parser error.

## Project structure

```
cub3d-main/
├── Makefile
├── README.md
├── cub3D                         # produced binary (after `make`)
├── includes/                     # public headers
│   ├── cub3d.h                   # main game struct, constants, prototypes
│   ├── key_handling.h            # per-OS key codes + destroy_display wrapper
│   ├── maps.h                    # t_map definition
│   ├── parser.h                  # parser prototypes / helpers
│   ├── player.h                  # t_player definition
│   └── raycasting.h              # t_ray + raycasting prototypes
├── sources/
│   ├── main.c                    # entry point
│   ├── parser/                   # .cub scene parser
│   │   ├── parser.c              # top-level parse driver
│   │   ├── parser_attrs.c        # NO/SO/WE/EA/F/C attributes
│   │   ├── parser_elements.c     # tokenizing / dispatch
│   │   ├── parser_error.c        # error reporting + exit
│   │   ├── parser_map.c          # 2D grid extraction
│   │   ├── parser_utils.c        # helpers
│   │   ├── parser_flood.c        # helpers
│   │   └── parser_validate.c     # closed-map + spawn validation
│   ├── player_controls/
│   │   ├── player_init.c         # spawn position + initial dir/plane
│   │   ├── movements.c           # WASD, collision (is_wall)
│   │   └── angles.c              # arrow-key rotation matrix
│   ├── raycast/
│   │   ├── raycast.c             # main per-column loop
│   │   ├── ray_dda.c             # DDA stepping, side detection
│   │   └── raycast_utils.c       # line bounds, wall_x, tex_x, draw_column
│   ├── render/
│   │   └── render.c              # background + frame + game loop
│   ├── mlx_utils/
│   │   ├── init_mlx.c            # window + framebuffer creation
│   │   ├── textures.c            # XPM loading
│   │   ├── hooks.c               # key / close hooks
│   │   └── cleanup.c             # free_game, texture/window destroy
│   ├── utils/
│   │   └── color.c               # rgb_to_int, put_pixel, get_tex_color
│   └── libft/                    # bundled libft + get_next_line
├── maps/                         # sample .cub scenes (explore_*, invalid_*, subject.cub, ...)
├── textures/                     # wall_n/s/e/w.xpm and other XPM assets
├── mlx/                          # bundled MiniLibX (built by Makefile)
└── obj/                          # object files (created by make)
```

## Resources

- [Ray-casting tutorial (Lodev)](https://lodev.org/cgtutor/raycasting.html)
- Wolfenstein 3D: http://users.atw.hu/wolf3d/

### AI usage

AI was used to understand the ray-casting engine, MLX rendering pipeline, player controls, and project documentation, based on the cub3D subject requirements.
