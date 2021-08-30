#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct		s_param
{
	int width;
	int	height;
}					t_param;

char		*get_header(t_param param);

char			*ft_convert_base(char *nbr, char *base_from, char *base_to);

int			ft_len(char *str);
