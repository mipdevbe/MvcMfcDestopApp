#pragma once
#include <string>
#include "../Model/IModel.h"

class LeaveModel : public IModel
{
public:

	LeaveModel(int id, const std::string& type, int duration);
	virtual ~LeaveModel();
	int getId() const;

	const std::string& getType() const;
	int getDuration() const;

private:
	int id;
	std::string type;
	int duration;
};