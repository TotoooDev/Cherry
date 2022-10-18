#include <Config.h>
#include <fstream>

void GlobalConfig::Init()
{
	std::ifstream file;
	file.open(m_FilePath);
	m_JSON = nlohmann::json::parse(file);
	file.close();
}

void GlobalConfig::SetConfigFile(const std::string& path)
{
	m_FilePath = path;
	Init();
}

nlohmann::json& GlobalConfig::Get()
{
	return m_JSON;
}

void GlobalConfig::Write()
{
	std::ofstream file(m_FilePath);
	file << std::setw(4) << m_JSON;
}