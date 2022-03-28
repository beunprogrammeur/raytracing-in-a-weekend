#pragma once
#include <regex>
#include <string>
std::string generate_file_path(const std::string& path, const std::string& filename_without_extension, const std::string& extension_without_dot) {
	std::string regex_string = filename_without_extension + "(\\d+)\\." + extension_without_dot;
	const std::regex file_regex(regex_string);
	
	int index = 0;

	for (const auto& file : std::filesystem::directory_iterator(path, std::filesystem::directory_options::skip_permission_denied)) {
		if (file.is_directory()) continue;
		const auto name = file.path().filename().string();

		std::smatch matches;
		if (std::regex_search(name, matches, file_regex) && matches.size() == 2) {
			auto str = matches[1].str();
			try {
				int num = std::stoi(str);
				if (num > index) index = num;
			}
			catch (std::exception ex) {}
		}
	}

	return path + "\\" + filename_without_extension + std::to_string(index + 1) + "." + extension_without_dot;
}