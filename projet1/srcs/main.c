/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2018/12/22 03:06:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"
#include "../includes/libft.h"

int		main(void)
{
	t_input	in;
	int		status;
	t_ptr	ptr;
	Uint32	*pixels;

	status = EXIT_FAILURE;
	if (ft_sdl_init(&ptr, SCR_WIDTH, SCR_HEIGHT, "42"))
		goto Quit;
	if (!(pixels = (Uint32 *)malloc(sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT)))
	{
		perror("Error Malloc pixels");
	}
	memset(pixels, 0, sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_update_event(&in);
		ft_draw(pixels);
		ft_update_renderer(ptr, pixels);
	}
	status = EXIT_SUCCESS;
Quit:
	ft_sdl_quit(&ptr);
	return (status);
}
