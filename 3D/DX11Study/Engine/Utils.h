#pragma once

class FUtils
{
public:
	static bool StartsWith(const std::string& InStr, const std::string& InComp);
	static bool StartsWith(const std::wstring& InStr, const std::wstring& InComp);

	static std::wstring ToWString(const string& InValue);
	static string ToString(const std::wstring& InValue);
};

