#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "../Model/IModel.h"

class IView 
{
public:
	IView() {} // Default constructor
    virtual ~IView() {} // Virtual destructor for proper cleanup

    virtual void CreateView() = 0; // Pure virtual method
    virtual void LoadView() = 0; // Pure virtual method
    virtual void UpdateView(const std::vector<std::unique_ptr<IModel>>& data) = 0;
    virtual void CloseView() = 0; // Pure virtual method
};