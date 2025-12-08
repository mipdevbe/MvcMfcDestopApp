#pragma once
#include <vector>
#include <functional>
#include "../Model/IModel.h"

class IView 
{
public:
	IView() {} // Default constructor
    virtual ~IView() {} // Virtual destructor for proper cleanup

    virtual void CreateView() = 0; // Pure virtual method
    virtual void LoadView() = 0; // Pure virtual method
    virtual void CloseView() = 0; // Pure virtual method
};