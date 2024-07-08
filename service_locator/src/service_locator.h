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

#pragma once

#include <map>
#include <mutex>
#include <memory>
#include <stdexcept>
#include "service.h"

class ServiceLocator
{
public:
    static ServiceLocator& sharedInstance() {
        static ServiceLocator instance;
        return instance;
    }
    
    ServiceLocator(const ServiceLocator&) = delete;
    ServiceLocator& operator=(const ServiceLocator&) = delete;
    
    template <typename T>
    void registerService(std::shared_ptr<T> service) {
        static_assert(std::is_base_of_v<IService, T>, "T must inherit from IService");
        std::lock_guard<std::mutex> lock(mutex_);
        std::type_index index = service->getTypeIndex();
        auto it = services_.find(index);
        if (it != services_.end()) {
            throw std::runtime_error("Service already registered");
        }
        services_[index] = service;
    }
    
    template <typename T>
    std::shared_ptr<T> getService() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::type_index index(typeid(T));
        auto it = services_.find(index);
        if (it != services_.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }
    
    template <typename T>
    void unregisterService() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::type_index index(typeid(T));
        auto it = services_.find(index);
        if (it != services_.end()) {
            services_.erase(it);
        }
    }
    
    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        services_.clear();
    }
    
private:
    ServiceLocator() = default;
    
    ~ServiceLocator() {
        clear();
    }
    
private:
    mutable std::mutex mutex_;
    std::map<std::type_index, std::shared_ptr<IService>> services_;
};

#define service_locator_autowired(service) ServiceLocator::sharedInstance().registerService(service)
#define service_locator_unwired(T) ServiceLocator::sharedInstance().unregisterService<T>()
#define service_locator_get_service(T) ServiceLocator::sharedInstance().getService<T>()
#define service_locator_clear() ServiceLocator::sharedInstance().clear()
