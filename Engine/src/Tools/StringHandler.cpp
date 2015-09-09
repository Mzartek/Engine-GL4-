#include <Engine/Tools/StringHandler.hpp>

std::string Engine::Tools::getDir(const char *filePath)
{
	size_t size, i;
	std::string path;

	for (size = i = 0; filePath[i] != '\0'; i++)
		if (filePath[i] == '/' || filePath[i] == '\\')
			size = i + 1;

	path.insert(0, filePath, 0, size);

	return path;
}

char* Engine::Tools::readText(const char *filePath)
{
	std::ifstream file(filePath, std::ifstream::in | std::ifstream::binary);
	char *content;
	size_t size;

	if (!file.is_open())
	{
		std::exception(std::string("Error while opening file: " + std::string(filePath)).c_str());
	}
	// Lenght of the file
	file.seekg(0, std::ifstream::end);
	size = static_cast<size_t>(file.tellg());
	file.seekg(0, std::ifstream::beg);

	// Add content
	content = new char[size + 1];
	file.read(content, size);
	content[size] = '\0';

	file.close();

	return content;
}