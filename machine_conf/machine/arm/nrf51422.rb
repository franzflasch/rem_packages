=begin
    
    Copyright (C) 2017 Franz Flasch <franz.flasch@gmx.at>

    This file is part of REM - Rake for EMbedded Systems and Microcontrollers.

    REM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    REM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with REM.  If not, see <http://www.gnu.org/licenses/>.
=end

require_relative './arm'

global_config.set_compile_flag("-MP -MD -std=c99 -mcpu=cortex-m0 -mthumb -mabi=aapcs -Wall -Werror -Os -g3 -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums")
global_config.set_link_flag("-mthumb -mabi=aapcs -mcpu=cortex-m0 -Wl,--gc-sections -lc -lnosys -lm")
