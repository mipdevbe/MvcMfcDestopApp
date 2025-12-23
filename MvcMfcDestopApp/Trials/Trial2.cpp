#include <afx.h>
#include "Trial2.h"

Trial2::Trial2()
{
}

Trial2::~Trial2()
{
}


void Trial2::Run()
{
    // Redirect std::cout to AfxOutputDebugString
    CoutRedirector redirect;

    Employees employees;
    employees.Add("Bob", 25);
    auto employee2 = make_shared<Employee>("James", 30);
    employees.Add(employee2); // ref count not increased...

    auto emp1 = employees.getAt(0);
    employee2 = employees.getAt(1);
    std::cout << "employee: " << emp1->getName() << " use_count: " << emp1.use_count() << "\n";
    std::cout << "employee: " << employee2->getName() << " use_count: " << employee2.use_count() << "\n";

}