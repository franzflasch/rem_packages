=begin
    
    Copyright (C) 2015 Franz Flasch <franz.flasch@gmx.at>

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

global_config.set_compiler_prefix("avr-")
global_config.set_c_compiler("gcc")
global_config.set_cpp_compiler("g++")
global_config.set_obj_cp("objcopy")
global_config.set_c_flag("-Wall -Werror")
global_config.set_objcopy_flag("-R .eeprom -R .fuse -R .lock -R .signature")

# This is needed for AVR due to some changes in GCC >=12
global_config.set_c_flag("--param=min-pagesize=0")
global_config.set_cpp_flag("--param=min-pagesize=0")

require "#{global_config.get_rakefile_dir()}/scripts/build_functions/gcc/default.rb"
