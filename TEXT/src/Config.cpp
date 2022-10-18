#include <Config.h>
#include <fstream>

void Config::Init()
{
	std::ifstream file;
	file.open(m_FilePath);
	m_JSON = nlohmann::json::parse(file);
	file.close();
}

void Config::SetConfigFile(const std::string& path)
{
	m_FilePath = path;
	Init();
}

nlohmann::json& Config::Get()
{
	return m_JSON;
}

void Config::Write()
{
	std::ofstream file(m_FilePath);
	file << std::setw(4) << m_JSON;
	file.close();
}