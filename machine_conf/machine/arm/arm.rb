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

if(USE_CLANG == "1")
    global_config.set_compiler("clang -target arm-none-eabi")
    global_config.set_obj_cp("llvm-objcopy-14")

    # we still need some header files and libraries even when we build with clang
    # to get those library search dirs do, please change appropriately:
    # arm-none-eabi-gcc -print-search-dirs
    global_config.set_compile_flag("--sysroot=/opt/local/cross-tool-cortex-m4-gcc12/arm-none-eabi/")
    global_config.set_link_flag("-L /opt/local/cross-tool-cortex-m4-gcc12/arm-none-eabi/lib/")
    global_config.set_link_flag("-L /opt/local/cross-tool-cortex-m4-gcc12/lib/gcc/arm-none-eabi/12.2.0/")
else
    global_config.set_compiler_prefix("arm-none-eabi-")
    global_config.set_compiler("gcc")
    global_config.set_obj_cp("objcopy")
end

global_config.set_compile_flag("-Wall -Werror")


require "#{global_config.get_rakefile_dir()}/scripts/build_functions/gcc/default.rb"
