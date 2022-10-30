#include <Panels/Markdown.h>
#include <sstream>
#include <iostream>

MarkdownViewer::MarkdownViewer(std::string* string)
	: m_String(string)
{
	Parse();
}

void MarkdownViewer::Draw(bool* isOpen)
{
	Parse(); // temp
}

void MarkdownViewer::Parse()
{
	std::stringstream sstream(*m_String);
	std::string line;

	while (std::getline(sstream, line))
	{
		switch (line[0])
		{
		case '#':
		{
			// Header
			unsigned int headerLevel = line.find_last_of('#') + 1;
			std::string text = line.substr(headerLevel);

			MarkdownType type;
			type.ID = MarkdownID::Header;
			type.Data = headerLevel;
			type.Text = text;

			m_ParsedText.push_back(type);

			break;
		}
		}
	}
}