#pragma once
#include <string>
#include "../Model/IModel.h"

class LeaveModel : public IModel
{
public:

	LeaveModel(int id, const std::string& type, int duration) : id(id), type(type), duration(duration) 
	{
	}	

	virtual ~LeaveModel() {}
	int getId() const { return id; }

	const std::string& getType() const { return type; }
	int getDuration() const { return duration; }

private:
	int id;
	std::string type;
	int duration;
};