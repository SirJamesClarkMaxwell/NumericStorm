
#pragma once
#include <string>
namespace NumericStorm 
{
namespace Fitting 
{
class SimplexCreatorSettigns 
{
public:
	SimplexCreatorSettigns(std::string operationName)
		:m_name(operationName){};
private:
	std::string m_name;
};
}

}