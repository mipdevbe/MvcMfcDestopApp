#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

#include <iostream>
#include <streambuf>
#include <string>

// Custom stream buffer that sends output to AfxOutputDebugString
class DebugStreamBuf : public std::streambuf {
protected:
    // Called when buffer is full or on explicit flush
    int overflow(int c = EOF) override {
        if (c != EOF) {
            char ch = static_cast<char>(c);
            buffer_.push_back(ch);
            if (ch == '\n') {
                flushBuffer();
            }
        }
        return c;
    }

    // Called when std::ostream is flushed
    int sync() override {
        flushBuffer();
        return 0;
    }

private:
    std::string buffer_;

    void flushBuffer() {
        if (!buffer_.empty()) {
            // Send to Visual Studio Output window
            AfxOutputDebugString(CString(buffer_.c_str()));
            buffer_.clear();
        }
    }
};

// RAII helper to redirect std::cout
class CoutRedirector {
public:
    CoutRedirector() : oldBuf_(std::cout.rdbuf(&debugBuf_)) {}
    ~CoutRedirector() { std::cout.rdbuf(oldBuf_); }

private:
    DebugStreamBuf debugBuf_;
    std::streambuf* oldBuf_;
};

class Employee {
private:
    string name{};
    int age{};
public:
    Employee(const string name, int age) : name{ name }, age{ age } {
        cout << "Constructor Employee: " << name << endl;
    }

    Employee(const Employee& employee) : name{ employee.name }, age{ employee.age } {
        cout << "Copy constructor Employee: " << name << endl;
    }

    virtual ~Employee() {
        cout << "Destructor Employee: " << name << endl;
    }

    const string& getName() const { return name; }
};

class Employees {
public:

    using EmployeePtr = shared_ptr<Employee>;

    Employees() {
        cout << "Constructor Employees" << endl;
    }

    virtual ~Employees() {
        cout << "Destructor Employees" << endl;
    }

    void Add(const string name, int age) {
        cout << "Employees: Add reference" << endl;
        employees.push_back(make_shared<Employee>(name, age));
    }

    void Add(const EmployeePtr& employee) {
        cout << "Employees: Add shared_ptr" << endl;
        employees.push_back(employee);
    }

    EmployeePtr getAt(int index) {
        cout << "Employees: getAt(" << index << ")" << endl;
        return employees[index];;
    }

    size_t getCount() const {
        cout << "Employees: getCount()" << endl;
        return employees.size();
	}

private:
    vector<EmployeePtr> employees{};
};

class Trial2
{
public:
	Trial2();
	virtual ~Trial2();


	void Run();
};

