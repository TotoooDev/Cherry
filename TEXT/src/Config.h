#pragma once

#include <string>
#include <nlohmann/json.hpp>

class GlobalConfig
{
public:
	static void Init();
	static void SetConfigFile(const std::string& path);
	static nlohmann::json& Get();
	static void Write();

private:
	inline static nlohmann::json m_JSON;
	inline static std::string m_FilePath = "TOE_GlobalConfig.json";
};