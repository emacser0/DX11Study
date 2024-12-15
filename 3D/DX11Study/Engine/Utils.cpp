#include "pch.h"
#include "Utils.h"

bool FUtils::StartsWith(const std::string& InStr, const std::string& InComp)
{
	std::wstring::size_type Index = InStr.find(InComp);
	if (Index != std::wstring::npos && Index == 0)
		return true;

	return false;
}

bool FUtils::StartsWith(const std::wstring& InStr, const std::wstring& InComp)
{
	std::wstring::size_type Index = InStr.find(InComp);
	if (Index != std::wstring::npos && Index == 0)
		return true;

	return false;
}

std::wstring FUtils::ToWString(const std::string& InValue)
{
	return std::wstring(InValue.begin(), InValue.end());
}

std::string FUtils::ToString(const std::wstring& InValue)
{
	return string(InValue.begin(), InValue.end());
}
