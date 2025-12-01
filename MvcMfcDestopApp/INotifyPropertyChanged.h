#pragma once
#include "PropertyChangedEventArgs.h"

class INotifyPropertyChanged {
public:
    virtual void PropertyChanged(const PropertyChangedEventArgs& args) = 0;
    virtual ~INotifyPropertyChanged() = default;
};