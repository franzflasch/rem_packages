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

global_config.set_c_flag("-Os -g -fno-common -ffunction-sections -fdata-sections -MD -mthumb -mcpu=cortex-m0")
global_config.set_link_flag("--static -Wl,--gc-sections -mthumb -mcpu=cortex-m0 -mabi=aapcs -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group")
