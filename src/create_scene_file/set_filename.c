#include <RTmlx.h>
#include <scene.h>

//	Static Function
static void	update_filename_input(const keys_t key, t_window *win);

// void draw_custom_text(mlx_t *mlx, const char *text, int x, int y, int char_width, int char_height) {
//     mlx_texture_t *font_texture = mlx_load_png("path/to/font.png");
//     if (!font_texture) {
//         printf("Failed to load font texture\n");
//         return;
//     }

//     for (size_t i = 0; text[i] != '\0'; i++) {
//         char c = text[i];
//         int char_x = (c % 16) * char_width; // Assuming 16 characters per row in the texture
//         int char_y = (c / 16) * char_height;

//         // Create an image for the character
//         mlx_image_t *char_image = mlx_new_image(mlx, char_width, char_height);
//         if (!char_image) {
//             printf("Failed to create character image\n");
//             continue;
//         }

//         // Copy the character from the font texture to the image
//         for (int py = 0; py < char_height; py++) {
//             for (int px = 0; px < char_width; px++) {
//                 uint32_t color = font_texture->pixels[(char_y + py) * font_texture->width + (char_x + px)];
//                 mlx_put_pixel(char_image, px, py, color);
//             }
//         }

//         // Display the character image
//         mlx_image_to_window(mlx, char_image, x + i * char_width, y);
//         mlx_delete_image(mlx, char_image);
//     }

//     mlx_delete_texture(font_texture);
// }

void	set_filename(const keys_t key, t_window *win, t_scene *sc)
{
	if (key == MLX_KEY_ENTER && win->file_creation == false)
	{
		win->file_creation = true;
		mlx_set_window_title(win->mlx, win->filename);
	}
	else if (key == MLX_KEY_ESCAPE)
	{
		mlx_set_window_title(win->mlx, "miniRT");
		reset_filename(win);
	}
	else if (key == MLX_KEY_ENTER && win->file_creation == true)
	{
		if (ft_strncmp(win->filename, NAME_FILE, sizeof(NAME_FILE)) != 0)
		{
			printf(">%s<\n>%s<\n", win->filename, NAME_FILE);
			create_scene_rt_file(sc, win->filename + (sizeof(NAME_FILE) - 1));
			cpy_str(win->filename + 6, "Created file: ");
			win->filename[sizeof(NAME_FILE) - 2] = ' ';
		}
		mlx_set_window_title(win->mlx, "miniRT");
		reset_filename(win);
	}
	else
		update_filename_input(key, win);
}

void	reset_filename(t_window *win)
{
	win->filename_len = cpy_str(win->filename, NAME_FILE);
	win->file_creation = false;
}

static void	update_filename_input(const keys_t key, t_window *win)
{
	if (key == MLX_KEY_BACKSPACE && win->filename_len > sizeof(NAME_FILE) - 1)
		win->filename[--win->filename_len] = '\0';
	else if (key >= MLX_KEY_SPACE && key <= MLX_KEY_GRAVE_ACCENT)
	{
		if (win->filename_len < FILE_CREATION + (sizeof(NAME_FILE) - 1))
		{
			if (key >= MLX_KEY_A && key <= MLX_KEY_Z)
				win->filename[win->filename_len++] = (char)(key + 32);
			else
				win->filename[win->filename_len++] = (char)key;
			win->filename[win->filename_len] = '\0';
		}
		else
			return (mlx_set_window_title(win->mlx, "Filename too long."));
	}
	mlx_set_window_title(win->mlx, win->filename);
}
