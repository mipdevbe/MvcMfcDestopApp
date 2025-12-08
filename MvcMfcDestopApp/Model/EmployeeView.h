#pragma once
#include <afxwin.h>
#include <memory>
#include <vector>
#include "..\View\IView.h"
#include "..\Model\IModel.h"

class EmployeeView : public IView
{
public:
		EmployeeView() : IView() {}
	virtual ~EmployeeView() {}

public:
	void CreateView() override {}
	void LoadView() override {}
	void UpdateView(const std::vector<std::shared_ptr<IModel>>& data) override {}
	void CloseView() override {}
};