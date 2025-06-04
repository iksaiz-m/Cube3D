/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:40:13 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/06/04 20:54:32 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

//Para las rotaciones habra que crear un vector de direccion y uno de camara del que se disparen los rayos.

//  π / 2 = 90°
// isRayFacingDown  = rayAngle > 0 && rayAngle < pi [180];
// isRayFacingUp    = !isRayFacingDown;
// isRayFacingRight = rayAngle < (0.5 * pi) [90] || rayAngle > (1.5 * pi) [270];
// isRayFacingLeft  = !isRayFacingRight;



// Para determinar si un rayo toca un muro se va a tener que dividir el mapa en baldosas mas pequeñas que tenemos que definir en el .h

//Ay         = floor(player_y / TILE) * TILE;
// if (RayFacingDown)
// Ay += TILE;

// // tan(α)  = Opposite / Adjacent;
// // tan(α)  = (Ay - Py) / (Ax - Px);
// // Ax - Px = (Ay - Py) / tan(α);
// Ax         = Px + (Ay - Py) / tan(α);