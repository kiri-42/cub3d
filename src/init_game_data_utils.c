#include "cub3d.h"

bool	is_path_line(char *str)
{
	return (!ft_strncmp(str, "NO", PREFIX_SIZE) || !ft_strncmp(str, "SO", PREFIX_SIZE) || !ft_strncmp(str, "WE", PREFIX_SIZE) || !ft_strncmp(str, "EA", PREFIX_SIZE));
}
