*This project has been created as part of the 42 curriculum by ymazzett, mabdur-r.*

## Description

**cub3D** is a Wolfenstein 3D–inspired first-person maze explorer built in C with the MiniLibX graphics library. The program parses a `.cub` scene file (textures, floor/ceiling colors, and a 2D map), then renders a real-time 3D view using **ray-casting**.

## Instructions

### Dependencies (Linux)

```bash
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
```

### Build

```bash
make
```

```bash
make relinux
```

### Run

Run from the project root so texture paths resolve correctly:

```bash
./cub3D maps/simple.cub
./cub3D maps/subject.cub
```

### Controls

| Key | Action |
|-----|--------|
| W / S | Move forward / backward |
| A / D | Strafe left / right |
| ← / → | Rotate view left / right |
| ESC | Quit |
| Window X button | Quit |

### Parser error testing

Invalid maps must print `Error` followed by a message on stderr and exit non-zero:

```bash
./cub3D maps/invalid_hole.cub    # map not closed
./cub3D maps/invalid_spawn.cub   # two player spawns
./cub3D not_a_cub.txt            # wrong extension
```

## Project structure

```
cub3d/
├── parser/          # .cub file parser (map, textures, colors)
├── player_controls/ # movement and rotation
├── raycast/         # DDA ray-casting
├── render/          # frame rendering (floor, ceiling, walls)
├── mlx_utils/       # MLX init, textures, hooks, cleanup
├── maps/            # sample .cub maps
├── textures/        # wall XPM textures (N/S/W/E)
├── libft/           # custom C library + get_next_line
└── mlx/             # MiniLibX
```

## Resources

- [Cub3D subject](en.subject.pdf)
- [Ray-Casting tutorial (Lodev)](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/mlx)
- Wolfenstein 3D: http://users.atw.hu/wolf3d/

### AI usage

AI was used to implement the ray-casting engine, MLX rendering pipeline, player controls, and project documentation, based on the existing parser module and the official cub3D subject requirements.
