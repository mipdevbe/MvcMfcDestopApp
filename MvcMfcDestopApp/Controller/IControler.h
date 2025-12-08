#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "..\View\IView.h"
#include "..\Model\IModel.h"

class IController
{
public:
    IController()
    {
    }

    virtual ~IController()
    {
    }

    template <typename T>
    void CheckIsViewType(T type) {
        //static_assert(std::is_base_of<IView, T>::value, "T must be derived from IView.");
    }

    template <typename T>
    void CheckIsModelType(T type) {
        //static_assert(std::is_base_of<IModel, T>::value, "T must be derived from IModel.");
    }

    template <typename T>
    void registerView(std::shared_ptr<IView>&& view = nullptr) 
    {
        //CheckIsViewType(T);

        std::type_index typeViewIndex(typeid(T));
        auto it = views.find(typeViewIndex);
        if (it == views.end())
            views[typeViewIndex] = view;
    }

    template <typename T>
    const std::shared_ptr<IView> View() {

        //CheckIsViewType(T);

        std::type_index typeIndex(typeid(T));
        auto it = views.find(typeIndex);
        if (it != views.end() && it->second != nullptr)
            return it->second;

        auto newInstance = std::make_shared<T>(this);
        views[typeIndex] = newInstance;
        return newInstance;
    }

    template <typename T>
    void registerModel() {

       // CheckIsModelType(T);

        std::type_index typeModelIndex(typeid(T));
        auto it = models.find(typeModelIndex);
        if (it == models.end())
            models[typeModelIndex] = nullptr;
    }

    // async ??
    virtual bool Initialize() = 0;
    virtual bool Load() = 0;
	virtual bool Update() = 0;
	virtual bool Close() = 0;

protected:



    template <typename T>
    const std::shared_ptr<IModel> Model() const {

        //CheckIsModelType(M);

        std::type_index typeIndex(typeid(T));
        auto it = views.find(typeIndex);
        if (it != views.end() && it->second.has_value())
            return it->second;

        auto newInstance = std::make_shared<T>(this);
        views[typeIndex] = newInstance;
        return newInstance;
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<IView>> views;
    std::unordered_map<std::type_index, std::shared_ptr<IModel>> models;
};


