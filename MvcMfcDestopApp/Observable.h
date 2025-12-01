#pragma once
#include <vector>
#include <algorithm>

#include "INotifyPropertyChanged.h"

class Observable {
public:
    void Subscribe(std::shared_ptr<INotifyPropertyChanged> listener) {
        // Ensure the listener is not already subscribed
        if (std::find(listeners.begin(), listeners.end(), listener) == listeners.end()) {
            listeners.push_back(listener);
        }
    }

    void Unsubscribe(const std::shared_ptr<INotifyPropertyChanged>& listener) {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }

protected:
    void NotifyPropertyChanged(const std::string& propertyName, const std::shared_ptr<INotifyPropertyChanged>& excludeListener = nullptr) {
        PropertyChangedEventArgs args(propertyName);
        for (const auto& listener : listeners) {
            if (listener != excludeListener) { // Optionally exclude the notifying listener
                listener->PropertyChanged(args);
            }
        }
    }

private:
    std::vector<std::shared_ptr<INotifyPropertyChanged>> listeners; // Use shared pointers
};
