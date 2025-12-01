#pragma once
#include <string>

class PropertyChangedEventArgs {
public:
    explicit PropertyChangedEventArgs(const std::string& propertyName)
        : propertyName(propertyName) {
    }

    const std::string& getPropertyName() const { return propertyName; }

private:
    std::string propertyName;
};