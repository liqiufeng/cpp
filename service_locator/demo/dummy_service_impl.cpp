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

#include "dummy_service_impl.h"
#include "log_service.h"
#include "service_locator.h"
#include <iostream>

DummyServiceImpl::DummyServiceImpl() {
    std::cout << __FUNCTION__ << std::endl;
}

DummyServiceImpl::~DummyServiceImpl() {
    std::cout << __FUNCTION__ << std::endl;
}

void DummyServiceImpl::foo() {
    auto logService = service_locator_get_service(ILogService);
    logService->log("foo");
}

void DummyServiceImpl::bar() {
    auto logService = service_locator_get_service(ILogService);
    logService->log("bar");
}
