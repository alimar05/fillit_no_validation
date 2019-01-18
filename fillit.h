#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include <stdio.h>
# include <libft.h>
# define BUFF_SIZE 21
# define SIZE 5

typedef	struct		s_etra
{
	char			*coor;
	char			c;
	struct s_etra	*next;
}					t_etra;

void				ft_list_push_back(t_etra **begin_list, char *coor, char c);
char				smallest_square_size(int n);
int					ft_list_count(t_etra **begin_list);
char				init_map(char **map, char size_map);
void				tet_norm(t_etra **begin_list);
void				tet_place_map(char **map, t_etra *tetra, char c);
char				tet_move(char size_map, t_etra *tetra);
char				solve_map(char **map, char size_map, t_etra *tetra);

#endif
