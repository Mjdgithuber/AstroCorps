#include <filesystem>

#include "Core.h"
#include "Directory.h"

Directory::Directory()
	: m_open(false), m_dir() {}

Directory::Directory(const std::string& dir_path)
	: Directory() {
	// attempt to open dir
	open_dir(dir_path);
}

void Directory::load_files() {
	for (auto& p : std::filesystem::directory_iterator(m_dir)) {
		if (!p.is_directory()) {
			m_files.push_back(p.path());
		}
	}
}

bool Directory::open_dir(const std::string& dir_path) {
	// wrap string into path
	std::filesystem::path dir(dir_path);

	// check if path exists & is a directory
	if (std::filesystem::exists(dir)) {
		if (std::filesystem::is_directory(dir)) {
			m_files.clear();
			m_dir = dir;
			load_files();
			return (m_open = true);
		}
	}
	LOG_WARN("Failed to open '{0}' directory", dir_path);
	return false;
}

unsigned int Directory::number_of_files() {
	if (!assert_open("number_of_files()"))
		return 0;

	return m_files.size();
}

std::string Directory::get_filename(unsigned int file) {
	if (!assert_open("get_filename(unsigned int file)"))
		return "";

	return m_files[file].filename().string();
}

bool Directory::assert_open(const std::string& caller) {
	if (!m_open)
		LOG_ERROR("Tried to call '{0}' with no open directory", caller);

	return m_open;
}

bool Directory::is_open() {
	return m_open;
}