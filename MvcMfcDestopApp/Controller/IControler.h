#pragma once
#include <memory>
#include <typeindex>
#include <map>
#include "..\View\IView.h"

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

    template <class T>
    void registerView(std::shared_ptr<IView>& view)
    {
        //CheckIsViewType(T);

        std::type_index typeViewIndex(typeid(T));
        auto it = views.find(typeViewIndex);
        if (it == views.end())
            views[typeViewIndex] = view;
    }

    template <class T>
    const std::shared_ptr<IView> View() const{

        //CheckIsViewType(T);
		std::shared_ptr<IView> result = nullptr;

        std::type_index typeIndex(typeid(T));
        auto it = views.find(typeIndex);
        if (it != views.end() && it->second != nullptr)
            result = it->second;

      
        return result;
    }

    // async ??
    virtual void Initialize() = 0;
    virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Close() = 0;

private:
    std::map<std::type_index, std::shared_ptr<IView>> views;
};


