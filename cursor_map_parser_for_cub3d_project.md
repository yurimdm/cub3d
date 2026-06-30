# Map parser for cub3d project
_Exported on 6/10/2026 at 20:48:24 GMT+4 from Cursor (3.2.16)_

---

**User**

@cub3d.pdf i am doing cub3d with my partner. my part for now i want to create a map parser that will pass the right map to the programme. refer the subject file to create the file. program must take as a first argument a scene description file with the .cub
extension.so i need to create the code file for this only. 

---

**Cursor**

Let me read the relevant portions of the cub3d.pdf subject to understand the parsing requirements.

I have enough understanding of the subject now. Let me check a few more sections of the PDF to make sure I cover all parsing requirements correctly.

I have a clear picture now. Let me set up a plan and start building the parser module.

First, I'll extend `cub3d.h` with the fields the parser needs to populate (textures, colors, player spawn) and declare the public parse entry point.

Now I'll create the parser module. I'm splitting it across several files so each stays within the 42 norm (≤5 functions per file, ≤25 lines per function).

Now I'll wire it into `main.c` and the `Makefile`. The subject mandates one argument with `.cub` extension, so I'll enforce that here.

Now let me update the Makefile to include the parser sources.

Let me first check for any lint issues, then verify the parser compiles standalone (without MLX) by building a quick test.

The `mlx` folder is empty so the full Makefile build won't work yet. Let me compile just the parser + libft + main as a quick standalone sanity check, with a sample valid map and a few invalid ones.

Clean compile, no warnings. Let me write a tiny test driver to make sure parsing actually works on real `.cub` files.

Now let me run several scenarios — a valid map, the subject's example, and a few invalid ones — to verify correctness.

Found a bug — the map lines are not getting their trailing `\n` stripped because `parse_elements` only strips up to the map's start. Let me fix this with a single strip pass right after reading.

That bumps `parser.c` to 6 functions, breaking the 42 norm. Let me inline that strip pass directly into `parse_scene`.

The shell output seems truncated. Let me re-run the remaining error cases.

The error message for missing elements is misleading — I should detect "looks like a map line but elements not set" first.

All six maps behave correctly. Now the CLI-level cases (wrong extension, no args, missing file).

All paths report `Error\n` followed by an explicit message and exit non-zero — exactly what the subject requires. Let me also check a couple of trickier maps that often catch parsers off guard.

Everything passes. Let me do a final compile of all parser objects one more time to make sure nothing broke after the small fixes.

Done. Here's what I built and how it works.

## What was created

A self-contained map parser module under `parser/`, split across files to respect the 42 norm (≤5 functions per file, ≤25 lines per function, ≤80 columns):

- `parser/parser.h` — internal API for the parser module
- `parser/parser.c` — `parse_scene` entry point, `.cub` extension check, file → `char **` lines via `get_next_line`
- `parser/parser_utils.c` — line helpers: `init_map_defaults`, `append_line`, `strip_newline`, `is_blank_line`, `skip_spaces`
- `parser/parser_elements.c` — top-level loop, `is_map_line`, identifier matching, dispatcher, "all elements set" check
- `parser/parser_attrs.c` — `parse_texture` (path) and `parse_color` (`R,G,B` with strict bounds 0–255)
- `parser/parser_map.c` — extracts map lines, right-pads them to a uniform width, builds `char **grid`
- `parser/parser_validate.c` — validates allowed characters, exactly one `N/S/E/W` spawn, and that every walkable cell (`0`, `N/S/E/W`) is bordered only by `1` or other walkable cells (no spaces, no out-of-bounds) → that proves the map is closed by walls

## Files modified to wire it in

- `cub3d.h` — added the data fields the parser populates on `t_map`:

```51:74:cub3d.h
typedef struct s_map
{
	int		fd;
	char	*file_path;
	int		width;
	int		height;
	char	**grid;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	int		floor_set;
	int		ceiling_set;
	int		player_count;
	char	player_dir;
	int		player_x;
	int		player_y;
	t_bool	(*file_to_grid)(struct s_map * m);
	t_bool	(*is_wall)(struct s_map * m, float x, float y);
	t_bool	(*load_map)(struct s_map * m, const char *fp);
}			t_map;
```

- `main.c` — now requires exactly one `.cub` arg and calls `parse_scene` before the game loop.
- `Makefile` — added the 6 parser sources and the `obj/parser` and `obj/player_controls` subdirs.

## Subject rules enforced

- First arg must end in `.cub`, otherwise `Error\n` + message.
- All 6 elements (`NO`, `SO`, `WE`, `EA`, `F`, `C`) must be present, each only once. Order is free; any number of blank lines between them is allowed.
- Map must be the **last** thing in the file. A blank line in the middle of map lines, or any non-blank content after, is rejected.
- Allowed map characters: `0 1 N S E W` and space/tab. Spaces are preserved (lines are right-padded to a common width so the grid is rectangular).
- Exactly one player spawn (`N`/`S`/`E`/`W`); position and orientation are saved in `map.player_x`, `map.player_y`, `map.player_dir`.
- Map must be closed by walls (any `0`/spawn touching a space or the outer edge → error).
- RGB components must be plain integers in `[0,255]`; format must be `R,G,B` exactly, no junk after.
- On any failure: prints `Error\n` then an explicit message to stderr and exits with `EXIT_FAILURE`.

## Verified behavior

I built the parser standalone (without MLX) against your `libft` and ran it on:

| Input | Result |
|---|---|
| simple valid map (5×6, subject example) | parsed, player `N` at (4,3) |
| subject's larger jagged map | parsed, 33×14 with spaces preserved |
| jagged map with leading-space rows | parsed, 13×7, player `E` at (2,4) |
| map with a hole on the side | `Error / Map is not closed by walls` |
| map with two spawns | `Error / Map must contain exactly one player spawn (N/S/E/W)` |
| map with no spawn | same error |
| missing `C` element | `Error / Missing scene elements before map` |
| `F 220,100,300` | `Error / Color value out of range [0,255]` |
| duplicate `NO` | `Error / Duplicate texture definition` |
| blank line splitting the map | `Error / Empty line inside map or extra content after map` |
| wrong extension (`.txt`) | `Error / File must have .cub extension` |
| missing file | `Error / Cannot open scene file` |
| empty file | `Error / Missing scene elements` |

All parser sources compile clean with `-Wall -Wextra -Werror`.

## Where your partner picks up

After `parse_scene(&game, argv[1])` returns, `game.map` has everything they need to start raycasting:

- `grid` (rectangular `char **`, width × height), `width`, `height`
- `no_texture`, `so_texture`, `we_texture`, `ea_texture` (paths to load via mlx)
- `floor_color[3]`, `ceiling_color[3]`
- `player_x`, `player_y`, `player_dir` — to feed into `init_player(...)`

Note: I left the existing `t_bool (*load_map)`, `(*file_to_grid)`, `(*is_wall)` function pointers in `t_map` untouched — your partner can hook those up later. The full project still won't *link* until the `mlx` folder has the actual minilibX (your `mlx/` is currently empty), but that's unrelated to parsing.

