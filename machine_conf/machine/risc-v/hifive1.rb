=begin
    
    Copyright (C) 2018 Franz Flasch <franz.flasch@gmx.at>

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

require_relative './risc-v'

global_config.set_compile_flag("-O3 -g -fno-builtin-printf -fdata-sections -ffunction-sections -march=rv32imac -mabi=ilp32 -mcmodel=medany")
global_config.set_link_flag("-Wl,--gc-sections")
