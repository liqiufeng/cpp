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

#include "service_locator.h"
#include "log_service_impl.h"
#include "dummy_service_impl.h"

int main(int argc, const char* argv[]) {
    service_locator_autowired(std::make_shared<LogServiceImpl>());
    service_locator_autowired(std::make_shared<DummyServiceImpl>());
        
    auto logService = service_locator_get_service(ILogService);
    logService->log("hello world");
        
    auto dummyService = service_locator_get_service(IDummyService);
    dummyService->foo();
    dummyService->bar();
        
    service_locator_clear();
    return 0;
}
