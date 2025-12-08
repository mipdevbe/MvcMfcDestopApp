#pragma once
#include <iostream>
#include <vector>
#include "../Controller/IControler.h"
#include "../Controller/CompanyController.h"
#include "../Controller/EmployeeController.h"
#include "../Controller/LeaveController.h"

#include <typeindex>

using namespace std;

class Controllers
{
public:
	Controllers() { cout << "Controllers instance created" << endl; }

	virtual ~Controllers() {
		cout << "Controllers instance destroyed" << endl;
	}

	void Initialize()
	{
        Controller<CompanyController>()->Initialize();
        Controller<EmployeeController>()->Initialize();
        Controller<LeaveController>()->Initialize();
	}

    template <typename C>
    const std::shared_ptr<IController> Controller() const {

        CheckIsViewType(C);

        std::type_index typeIndex(typeid(C));
        auto it = controllers.find(typeIndex);
        if (it != controllers.end() && it->second.has_value())
            return it->second;

        auto newInstance = std::make_shared<C>();
        controllers.push_back(newInstance);
        return newInstance;
    }

private:
	std::vector<std::shared_ptr<IController>> controllers;
};