/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:11:37 by abrun             #+#    #+#             */
/*   Updated: 2021/03/24 11:44:39 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game.h"

int			ft_put_pui_save(int nbr, int base_len)
{
	int			res;
	int			puissance;

	puissance = 0;
	res = base_len;
	while (nbr >= res)
	{
		puissance++;
		res *= base_len;
	}
	return (puissance + 1);
}

void		put_zero(char *s)
{
	int		i;
	int		len;
	char	tmp;

	len = ft_len(s);
	i = 0;
	s[len] = '0';
	while (len > 0)
	{
		tmp = s[len];
		s[len] = s[len - 1];
		s[len - 1] = tmp;
		len--;
	}
}

char		*putnbr_base(int nbr, char *base, int size)
{
	char		*res;
	int			base_len;
	int			len;
	char		n[size + 1];
	int			i;

	i = 0;
	base_len = ft_len(base);
	len = ft_put_pui_save(nbr, 10);
	while (i < len)
	{
 		n[i] = nbr / pow(10, len - i - 1) + '0';
		nbr = (nbr %  (int)pow(10, len - i - 1));
		i++;
	}
	n[i] = 0;
	res = ft_convert_base(n, "0123456789", "0123456789abcdef");
	i = ft_len(res);
	if (i % 2 != 0)
	{
		put_zero(res);
		i++;
	}
	while (i < size)
	{
		res[i] = '0';
		i++;
	}
	res[i] = 0;
	return (res);
}

void		put_conv_in(char *conv, char *header, int con_len, int j)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (i < con_len)
	{
		if (conv[i] == '0' && conv[i + 1] == '0')
			i = con_len;
		else
		{
			len++;
			i += 2;
		}
	}
	len = len * 2 - 1;
	i = j;
	while (len > 0)
	{
		header[j++] = conv[len - 1];
		header[j++] = conv[len];
		len -= 2;
	}
	while (j < i + con_len)
		header[j++] = '0';
}

void		fill_len_fic(char *header, t_param param)
{
	int		len;
	char	*conv;
	int		i;
	int		c;

	c = get_c(param.width);
	i = 2;
	len = 54 + (param.width * 3 + c) * param.height;
	printf("len : %d\n", len);
	conv = putnbr_base(len, "0123456789", 8);
	put_conv_in(conv, header, 8, 2);
	header[10] = 0;
}

void		fill_chp_res(char *header)
{
	int		i;

	i = 10;
	while (i < 18)
	{
		header[i] = '0';
		i++;
	}
	header[i] = 0;
}

void		fill_offset(char *header)
{
	int		i;

	i = 18;
	header[i++] = 3 + '0';
	header[i++] = 6 + '0';
	while (i < 26)
	{
		header[i] = '0';
		i++;
	}
	header[i] = 0;
}

void		fill_len_img(char *header)
{
	int		i;

	i = 26;
	header[i++] = 2 + '0';
	header[i++] = 8 + '0';
	while (i < 34)
	{
		header[i] = '0';
		i++;
	}
	header[i]= 0;
}

void		fill_wid_hei(char *header, t_param param)
{
	char	*conv;

	conv = putnbr_base(param.width, "0123456789", 8);
	put_conv_in(conv, header, 8, 34);
	conv = putnbr_base(param.height, "0123456789", 8);
	put_conv_in(conv, header, 8, 42);
}

void		fill_n_plan(char *header)
{
	int		i;

	i = 50;
	header[i++] = '0';
	header[i++] = '1';
	header[i++] = '0';
	header[i++] = '0';
	header[i] = 0;
}

void		fill_bit_per_pix(char *header)
{
	int		i;

	i = 54;
	header[i++] = '1';
	header[i++] = '8';
	header[i++] = '0';
	header[i++] = '0';
	header[i] = 0;
}

void		fill_comp(char *header)
{
	int		i;

	i = 58;
	while (i < 66)
		header[i++] = '0';
	header[i] = 0;
}

void		fill_n_oct(char *header, t_param param)
{
/*	int		len;
	char	*conv;

	len = param.width * param.height * 3;
	conv = putnbr_base(len, "0123456789", 8);
	put_conv_in(conv, header, 8, 66);
	header[74] = 0;*/
	int		i;
	(void)param;
	i = 66;
	while (i < 74)
		header[i++] = '0'; 
}

int			convert_hexa(char *header, int i)
{
	int		a;
	int		b;
	int		res;

	if (header[i] >= 96)
		a = header[i] - 87;
	else
		a = header[i] - 48;
	if (header[i + 1] >= 96)
		b = header[i + 1] - 87;
	else
		b = header[i + 1] - 48;
	res = a * 16 + b;
	return (res);
}

void		get_resu(char *header, char *res)
{
	int		i;
	int		j;

	i = 2;
	j = 2;
	res[0] = 'B';
	res[1] = 'M';
	while (header[i])
	{
		res[j] = convert_hexa(header, i);
		i += 2;
		j++;
	}
}

int			get_save_len(t_param param)
{
	int		len;

	len = 54 + param.height * ((param.width * 3) + get_c(param.width));
	return (len);
}

void		get_header(t_param *param)
{
	char	*header;
	int		i;

	if (!(header = malloc(110)))
		param->save = NULL;
	if (!(param->save = malloc(get_save_len(*param))))
		param->save = NULL;
	header[0] = 'B';
	header[1] = 'M';
	fill_len_fic(header, *param);
	fill_chp_res(header);
	fill_offset(header);
	fill_len_img(header);
	fill_wid_hei(header, *param);
	fill_n_plan(header);
	fill_bit_per_pix(header);
	fill_comp(header);
	fill_n_oct(header, *param);
	i = 74;
	while (i < 106)
		header[i++] = '0';
	header[i] = 0;
	get_resu(header, param->save);
	free(header);
}
