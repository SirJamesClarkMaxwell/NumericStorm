
#pragma once
#include <string>
namespace NumericStorm 
{
namespace Fitting 
{
class SimplexCreatorSettigns 
{
public:
	SimplexCreatorSettigns(std::string name)
		:m_name(name){};
private:
	std::string m_name;
};
}

}