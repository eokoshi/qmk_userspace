/*
This is the c configuration file for the keymap

Copyright 2025 Ethan N. Okoshi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

#define TAPPING_TERM 150
// #define RETRO_TAPPING
#define PERMISSIVE_HOLD

#define COMBO_TERM 30

#define MOUSEKEY_OVERLAP_RESET
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_MAX_SPEED 32
#define MOUSEKEY_WHEEL_DELAY 0

#ifdef RGB_MATRIX_ENABLE
    #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
    #define RGB_MATRIX_DEFAULT_SPD 80
    #define RGB_MATRIX_DEFAULT_HUE 200
    #define RGB_MATRIX_DEFAULT_VAL 120
    #define RGB_MATRIX_SLEEP
    #define RGB_MATRIX_HUE_STEP 4
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 8
    #define RGB_MATRIX_LED_PROCESS_LIMIT 2
    #define RGB_MATRIX_LED_FLUSH_LIMIT 8
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE
    #define ENABLE_RGB_MATRIX_RIVERFLOW
#endif
