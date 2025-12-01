#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <iostream>
#include <any>
#include "IView.h"
#include "Observable.h"

class Controller : public Observable, public INotifyPropertyChanged
{
public:
    Controller() = default;

    template <typename T>
    bool RegisterView() {

        static_assert(std::is_base_of<IView, T>::value, "T must be derived from IView.");

        std::type_index typeIndex(typeid(T));
        auto it = views.find(typeIndex);
        if (it == views.end()) {
            views[typeIndex] = nullptr;
            return true;
        }

        return false;
    }

    template <typename T>
    bool UnregisterView() {
        static_assert(std::is_base_of<IView, T>::value, "T must be derived from IView.");

        std::type_index typeIndex(typeid(T));
        if (views.erase(typeIndex) > 0) 
            return true;
      
        return false; 
    }

    template <typename T>
    const std::shared_ptr<IView> View() const 
    {
        static_assert(std::is_base_of<IView, T>::value, "T must be derived from IView.");

        std::type_index typeIndex(typeid(T));
        auto it = views.find(typeIndex);
        if (it != views.end() && it->second.has_value()) 
            return it->second;

        auto newInstance = std::make_shared<T>(this);
        views[typeIndex] = newInstance;
        return newInstance;
    }

    bool Load() {
        return true;
    }

    bool Update() {
        return true;
    }

    bool Close() {
        return true;
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<IView>> views;
};
