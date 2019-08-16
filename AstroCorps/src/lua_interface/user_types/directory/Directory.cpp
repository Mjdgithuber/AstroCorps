#include <filesystem>

#include "Core.h"
#include "Directory.h"

/* New Directory with no association with a directory
   in filesystem */
Directory::Directory()
	: m_open(false), m_dir() {}

/* New Directory with an attempt to associate with a 
   directory in the filesystem */
Directory::Directory(const std::string& dir_path)
	: Directory() {
	// attempt to open dir
	open_dir(dir_path);
}

/* Through each file their path's in the m_files
   vector for latter use */
void Directory::load_files() {
	/* iterate over each file in directory. NOTE:
	   this is not recursive */
	for (auto& p : std::filesystem::directory_iterator(m_dir)) {
		if (!p.is_directory()) {
			m_files.push_back(p.path());
		}
	}
}

/* Prints error if there is no open directory */
bool Directory::assert_open(const std::string& caller) {
	// print error if needed
	if (!m_open)
		LOG_ERROR("Tried to call '{0}' with no open directory", caller);

	return m_open;
}

/* Attempts to open a new directory in your 
   filesystem */
bool Directory::open_dir(const std::string& dir_path) {
	// wrap string into path
	std::filesystem::path dir(dir_path);

	// check if path exists & is a directory
	if (std::filesystem::exists(dir)) {
		if (std::filesystem::is_directory(dir)) {
			// clear prev dir and load new one
			m_files.clear();
			m_dir = dir;
			load_files();
			return (m_open = true);
		}
	}
	LOG_WARN("Failed to open '{0}' directory", dir_path);
	return false;
}

/* Gets the number of file (not including directories)
   in the current directory */
unsigned int Directory::number_of_files() {
	// ensure that a directory is open
	if (!assert_open("number_of_files()"))
		return 0;

	return m_files.size();
}

/* Gets the filename (not path) of the path at the 
   passed in index. */
std::string Directory::get_filename(unsigned int file) {
	if (!assert_open("get_filename(unsigned int file)"))
		return "";

	// make sure file is in bounds
	if (file >= m_files.size()) {
		LOG_ERROR("Get filename at index '{0}' from directory '{1}' is out of bounds",
			file, m_dir.string());
		return "";
	}
	
	return m_files[file].filename().string();
}

/* Returns m_open :) I love comments */
bool Directory::is_open() {
	return m_open;
}