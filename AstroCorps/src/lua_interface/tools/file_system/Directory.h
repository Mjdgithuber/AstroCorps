#ifndef __DIRECTORY__H__
#define __DIRECTORY__H__

#include <string>
#include <filesystem>
#include <vector>

class Directory {
private:
	// directory
	bool m_open;
	std::filesystem::path m_dir;

	// files in directory
	std::vector<std::filesystem::path> m_files;

	void load_files();
	bool assert_open(const std::string& caller);
public:
	Directory();
	Directory(const std::string& dir_path);

	bool open_dir(const std::string& dir_path);

	unsigned int number_of_files();

	std::string get_filename(unsigned int file);

	bool is_open();
};

#endif