/*
Copyright (C) 2024 by Xuefeng Li <liqiufeng@gmail.com>

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

#include "log_service_impl.h"

#include <iostream>

LogServiceImpl::LogServiceImpl() {
    std::cout << __FUNCTION__ << std::endl;
}

LogServiceImpl::~LogServiceImpl() {
    std::cout << __FUNCTION__ << std::endl;
}

void LogServiceImpl::log(const std::string_view message, const std::source_location location) {
    std::clog << location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';
}
