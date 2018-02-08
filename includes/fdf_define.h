/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 09:23:07 by mbaron            #+#    #+#             */
/*   Updated: 2018/02/08 08:34:56 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DEFINE_H
# define FDF_DEFINE_H
# define FDF_WIN_W 1500
# define FDF_WIN_H 800
# define FDF_MARGE 10
# define FDF_CL_W 400
# define FDF_CL_X FDF_MARGE
# define FDF_CL_Y FDF_MARGE
# define FDF_MAP_W FDF_WIN_W - FDF_CL_W - 3 * FDF_MARGE
# define FDF_MAP_H FDF_WIN_H - 2 * FDF_MARGE
# define FDF_MAP_X FDF_CL_W + 2 * FDF_MARGE
# define FDF_MAP_Y FDF_MARGE
# define FDF_CL_MARGE 2
# define FDF_CL_H 25
# define FDF_CL_C_H FDF_CL_H - 2 * FDF_CL_MARGE
# define FDF_CL_C_W FDF_CL_C_H
# define FDF_CL_P_X FDF_MARGE + 2 * FDF_CL_MARGE
# define FDF_CL_C2_X FDF_MARGE + FDF_CL_W - FDF_CL_C_W - FDF_CL_MARGE
# define FDF_CL_C1_X FDF_CL_C2_X - FDF_CL_MARGE - FDF_CL_C_W
# define FDF_CL_V_X FDF_CL_C1_X - FDF_CL_MARGE - 2 * FDF_CL_C_W
# define FDF_CL_C_DEC 5
# define FDF_WIN_BG_COLOR 0x000000
# define FDF_MAP_BG_COLOR 0x202020
# define FDF_MAP_BD_COLOR 0x202020
# define FDF_CL_BG_COLOR 0x202020
# define FDF_CL_BD_COLOR 0x303030
# define FDF_CL_BTN1_COLOR 0x404040
# define FDF_CL_BTN2_COLOR 0x505050
# define FDF_CL_TXT1_COLOR 0xA0A0A0
# define FDF_CL_TXT2_COLOR 0xC0C0C0
# define FDF_PM_NB_W 5
# define FDF_PM_NB_C 6
# define FDF_PM_NB_P 4
# define FDF_PM_TITLE_W "WORLD"
# define FDF_PM_TITLE_C "CAMERA"
# define FDF_PM_TITLE_P "PROJECTION"
# define FDF_PM_W_0 "Center X (%)"
# define FDF_PM_W_1 "Center Y (%)"
# define FDF_PM_W_2 "Center Z (%)"
# define FDF_PM_W_3 "Zoom (%)"
# define FDF_PM_W_4 "Rotation (deg)"
# define FDF_PM_C_0 "X Position (%)"
# define FDF_PM_C_1 "X Position (%)"
# define FDF_PM_C_2 "X Position (%)"
# define FDF_PM_C_3 "Rotation on X axis (deg)"
# define FDF_PM_C_4 "Rotation on Y axis (deg)"
# define FDF_PM_C_5 "Rotation on Z axis (deg)"
# define FDF_PM_P_0 "Parall/Iso/Conic (1/2/3)"
# define FDF_PM_P_1 "Color Gradient (0/1)"
# define FDF_PM_P_2 "Floor's color"
# define FDF_PM_P_3 "Ceil's color"
# define FDF_W_X 50
# define FDF_W_Y 50
# define FDF_W_Z 50
# define FDF_W_ZOOM 100
# define FDF_W_ROT 0
# define FDF_C_X 50
# define FDF_C_Y -50
# define FDF_C_Z 200
# define FDF_C_RX 0
# define FDF_C_RY 0
# define FDF_C_RZ 0
# define FDF_P_VAL 1
# define FDF_P_COL 1
# define FDF_P_COLF 0x000000
# define FDF_P_COLC 0xFFFFFF
# define FDF_MIN_W_X 0
# define FDF_MAX_W_X 100
# define FDF_MIN_W_Y 0
# define FDF_MAX_W_Y 100
# define FDF_MIN_W_Z 0
# define FDF_MAX_W_Z 100
# define FDF_MIN_W_ZOOM 0
# define FDF_MAX_W_ZOOM 100
# define FDF_MIN_W_ROT 0
# define FDF_MAX_W_ROT 360
# define FDF_MIN_C_X -100
# define FDF_MAX_C_X 100
# define FDF_MIN_C_Y -100
# define FDF_MAX_C_Y 100
# define FDF_MIN_C_Z -100
# define FDF_MAX_C_Z 100
# define FDF_MIN_C_RX 0
# define FDF_MAX_C_RX 360
# define FDF_MIN_C_RY 0
# define FDF_MAX_C_RY 360
# define FDF_MIN_C_RZ 0
# define FDF_MAX_C_RZ 360
# define FDF_MIN_P_VAL 1
# define FDF_MAX_P_VAL 4
# define FDF_MIN_P_COL 0
# define FDF_MAX_P_COL 2
# define FDF_MIN_P_COLF 0
# define FDF_MAX_P_COLF 0xFFFFFF
# define FDF_MIN_P_COLC 0
# define FDF_MAX_P_COLC 0xFFFFFF
# define FDF_KUP_W_X KEY_RIGHT
# define FDF_KDN_W_X KEY_LEFT
# define FDF_KUP_W_Y KEY_UP
# define FDF_KDN_W_Y KEY_DOWN
# define FDF_KUP_W_Z KEY_PAGE_UP
# define FDF_KDN_W_Z KEY_PAGE_DOWN
# define FDF_KUP_W_ZOOM KEY_PAD_ADD
# define FDF_KDN_W_ZOOM KEY_PAD_SUB
# define FDF_KUP_W_ROT KEY_SHIFT_RIGHT
# define FDF_KDN_W_ROT KEY_SHIFT_LEFT
# define FDF_KUP_C_X KEY_PAD_3
# define FDF_KDN_C_X KEY_PAD_1
# define FDF_KUP_C_Y KEY_PAD_5
# define FDF_KDN_C_Y KEY_PAD_2
# define FDF_KUP_C_Z KEY_PAD_9
# define FDF_KDN_C_Z KEY_PAD_6
# define FDF_KUP_C_RX KEY_9
# define FDF_KDN_C_RX KEY_0
# define FDF_KUP_C_RY KEY_OPEN_BRACE
# define FDF_KDN_C_RY KEY_CLOSE_BRACE
# define FDF_KUP_C_RZ KEY_O
# define FDF_KDN_C_RZ KEY_P
# define FDF_KUP_P_VAL KEY_1
# define FDF_KDN_P_VAL KEY_2
# define FDF_KUP_P_COL KEY_3
# define FDF_KDN_P_COL KEY_4
# define FDF_KUP_P_COLF KEY_C
# define FDF_KDN_P_COLF KEY_V
# define FDF_KUP_P_COLC KEY_F
# define FDF_KDN_P_COLC KEY_G
#endif
