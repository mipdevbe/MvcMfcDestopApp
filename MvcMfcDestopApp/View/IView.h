#pragma once

class IView {
public:
	IView() {} // Default constructor
    virtual ~IView() {} // Virtual destructor for proper cleanup

    virtual void Create() = 0; // Pure virtual method
    virtual void Load() = 0;   // Pure virtual method
    virtual bool Update() = 0; // Pure virtual method

    virtual bool Close() = 0;   // Pure virtual method
    virtual bool IsClosed() const = 0; // Pure virtual accessor
};