/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:37:04 by mcoskune          #+#    #+#             */
/*   Updated: 2025/04/11 12:52:57 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clear_mlx(t_rayt *lux)
{
	if (!lux)
		return;
		
	if (lux->win_ptr)
	{
		mlx_destroy_window(lux->mlx_ptr, lux->win_ptr);
		lux->win_ptr = NULL;
	}
	
	if (lux->image.img)
	{
		mlx_destroy_image(lux->mlx_ptr, lux->image.img);
		lux->image.img = NULL;
	}
	
	if (lux->mlx_ptr)
	{
		mlx_destroy_display(lux->mlx_ptr);
		free(lux->mlx_ptr);
		lux->mlx_ptr = NULL;
	}
	
	lux->image.addr = NULL;
}

/**
 * Frees a camera and all of its associated matrices.
 * 
 * @param camera Pointer to the camera to free
 */
static void	free_camera(t_camera *camera)
{
	if (!camera)
		return;
		
	// if (camera->origin)
	// 	free_matrix(camera->origin);
		
	// if (camera->v_orient)
	// 	free_matrix(camera->v_orient);
		
	free(camera);
}

/**
 * Frees a point light and all of its associated matrices.
 * 
 * @param light Pointer to the point light to free
 */
static void	free_point_light(t_light *light)
{
	if (!light)
		return;
		
	// if (light->origin)
	// 	free_matrix(light->origin);
		
	free(light);
}


void	exit_cleanup(char *msg, t_rayt *lux, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 2);
		
	if (!lux)
		exit(exit_code);
		
	// Clean up resources in a structured way
	if (lux->mlx_ptr || lux->win_ptr)
		clear_mlx(lux);
		
	if (lux->p_light)
		free_point_light(lux->p_light);
		
	if (lux->a_light)
		free(lux->a_light);
		
	if (lux->camera)
		free_camera(lux->camera);
		
	// if (lux->objects)
	// 	free_objects(lux->objects);
		
	exit(exit_code);
}

int	handle_keys(int keysys, t_rayt *lux)
{
	if (keysys == XK_Escape)
		mlx_loop_end(lux->mlx_ptr);
	else if (keysys == XK_r)
	{
		free(lux->image.img);
		lux->image.img = NULL;
	}
	return (0);
}

int	handle_x_button(t_rayt *lux)
{
	mlx_loop_end(lux->mlx_ptr);
	return (0);
}
