#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "..\View\IView.h"
#include "..\Model\IModel.h"

class EmployeeView : public IView
{
public:

	using UpdateCallback = std::function<void(const std::vector<std::unique_ptr<IModel>>&)>;

	EmployeeView() {}
	virtual ~EmployeeView() {}

	void CreateView() override {}
	void LoadView() override {}

	// Setter to provide callback directly to the view
	void setUpdateCallback(const UpdateCallback& cb) { _callback = cb; }

	// Implement interface: will prefer the stored callback; if not set, will use the passed one
	void UpdateView(const std::vector<std::unique_ptr<IModel>>& data) override
	{
		if (_callback) {
			_callback(data);
		}
	}

	void CloseView() override {}

private:
	UpdateCallback _callback;
};