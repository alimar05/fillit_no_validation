#include "fillit.h"

t_etra	*ft_create_elem(char *coor, char c)
{
	t_etra	*elem;

	if (!(elem = (t_etra *)malloc(sizeof(t_etra))))
		return (NULL);
	if (coor != NULL)
	{
		if (!(elem->coor = (char *)malloc(sizeof(char) * 8)))
		{
			free(elem);
			return (NULL);
		}
		ft_memcpy(elem->coor, coor, 8);
		elem->c = c;
	}
	else
		elem->coor = NULL;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back(t_etra **begin_list, char *coor, char c)
{
	t_etra	*list;

	if (begin_list && *begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem(coor, c);
	}
	else
		*begin_list = ft_create_elem(coor, c);
}

int		ft_list_count(t_etra **begin_list)
{
	int		count;
	t_etra	*tetra;

	count = 0;
	tetra = *begin_list;
	while (tetra)
	{
		count++;
		tetra = tetra->next;
	}
	return (count);
}

char	smallest_square_size(int n)
{
	char	size;

	size = 2;
	while (size * size < n)
		size++;
	return (size);
}

char	init_map(char **map, char size_map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size_map)
	{
		if (!(map[i] = (char *)malloc(sizeof(char) * (size_map + 1))))
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (0);
		}
		j = -1;
		while (++j < size_map)
			map[i][j] = '.';
		map[i][j] = '\0';
	}
	return (1);
}

static char	tet_min_x(char *coor)
{
	char	i;
	char	xmin;

	i = -1;
	xmin = coor[0];
	while (++i < 4)
		if (coor[i * 2] < xmin)
			xmin = coor[i * 2];
	return (xmin);
}

static char	tet_max_x(char *coor)
{
	char	i;
	char	xmax;

	i = -1;
	xmax = coor[0];
	while (++i < 4)
		if (coor[i * 2] > xmax)
			xmax = coor[i * 2];
	return (xmax);
}

static char	tet_min_y(char *coor)
{
	char	i;
	char	ymin;

	i = -1;
	ymin = coor[1];
	while (++i < 4)
		if (coor[i * 2 + 1] < ymin)
			ymin = coor[i * 2 + 1];
	return (ymin);
}

static char	tet_max_y(char *coor)
{
	char	i;
	char	ymax;

	i = -1;
	ymax = coor[1];
	while (++i < 4)
		if (coor[i * 2 + 1] > ymax)
			ymax = coor[i * 2 + 1];
	return (ymax);
}

void	tet_upper_left(t_etra *tetra)
{
	char	i;
	char	xmin;
	char	ymin;

	i = -1;
	xmin = tet_min_x(tetra->coor);
	ymin = tet_min_y(tetra->coor);
	while (++i < 4)
	{
		tetra->coor[i * 2] = tetra->coor[i * 2] - xmin - 1;
		tetra->coor[i * 2 + 1] = tetra->coor[i * 2 + 1] - ymin;
	}
}

void	tet_norm(t_etra **begin_list)
{
	t_etra	*tetra;

	tetra = *begin_list;
	while (tetra)
	{
		tet_upper_left(tetra);
		tetra = tetra->next;
	}
}

char	is_tet_place_map(char **map, t_etra *tetra)
{
	char	i;

	i = -1;
	while (++i < 4)
		if (map[(int)tetra->coor[i * 2 + 1]][(int)tetra->coor[i * 2]] != '.')
			return (0);
	return (1);
}

void	tet_place_map(char **map, t_etra *tetra, char c)
{
	char	i;

	i = -1;
	while (++i < 4)
		map[(int)tetra->coor[i * 2 + 1]][(int)tetra->coor[i * 2]] = c;
}

char	tet_move(char size_map, t_etra *tetra)
{
	char	i;
	char	xmin;

	i = -1;
	while (++i < 4)
		tetra->coor[i * 2] = tetra->coor[i * 2] + 1;
	if (tet_max_x(tetra->coor) >= size_map)
	{
		xmin = tet_min_x(tetra->coor);
		i = -1;
		while (++i < 4)
			tetra->coor[i * 2] = tetra->coor[i * 2] - xmin;
		i = -1;
		while (++i < 4)
			tetra->coor[i * 2 + 1] = tetra->coor[i * 2 + 1] + 1;
		if (tet_max_y(tetra->coor) >= size_map)
		{
			tet_upper_left(tetra);
			return (0);
		}
	}
	return (1);
}

char	solve_map(char **map, char size_map, t_etra *tetra)
{
	if (tetra == NULL)
		return (1);
	while (tet_move(size_map, tetra))
	{
		if (is_tet_place_map(map, tetra))
		{
			tet_place_map(map, tetra, tetra->c);
			if (solve_map(map, size_map, tetra->next))
				return (1);
			tet_place_map(map, tetra, '.');
		}
	}
	return (0);
}
