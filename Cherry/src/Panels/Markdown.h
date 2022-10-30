#pragma once

#include <string>
#include <vector>

enum class MarkdownID
{
	Text,           // Data field unused
	Header,         // Length of the element
	Bold,           // Length of the element
	Italic,         // Length of the element
	Blockquote,     // Data field unused
	OrderedList,    // Index of the list
	UnorderedList,  // Index of the list
	Code,           // Length of the element
	HorizontalRule, // Data field unused
	Link            // Link path
};

struct MarkdownType
{
	MarkdownID ID;     // ID of the type
	unsigned int Data; // Data linked with the type (length, header level...)
	std::string Text;
};

class MarkdownViewer
{
public:
	MarkdownViewer(std::string* string);

	void Draw(bool* isOpen);

	void SetString(std::string* string) { m_String = string; }

private:
	void Parse();

	std::string* m_String;
	std::vector<MarkdownType> m_ParsedText;
	float m_Timer;
};