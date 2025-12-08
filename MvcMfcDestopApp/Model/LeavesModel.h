#pragma once

#include <vector>
#include "../Model/IModel.h"
#include "../Model/LeaveModel.h"

class LeavesModel : public IModel
{
public:
	LeavesModel();
	virtual ~LeavesModel();

	void addLeave(const LeaveModel& leave);
	void removeLeave(int leaveId);
	const std::vector<LeaveModel> getAll() const;

private:
	std::vector<LeaveModel>& companies;
};