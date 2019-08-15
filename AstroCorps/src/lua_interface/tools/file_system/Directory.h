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

	/* =========================================================== */
	/* ================= Private Helper Functions ================ */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// This will load all of the files of the current directory
	/// into the m_files path vector. NOTE: this only loads files
	/// not additional directories
	////////////////////////////////////////////////////////////
	void load_files();

	////////////////////////////////////////////////////////////
	/// This will check to see if a directory is open. If no 
	/// directory is currently open, then this will print out
	/// an error containing the function who called it for 
	/// debugging purposes. Returns m_open
	/// Params:
	/// caller - The name (as string) of the function calling 
	///	this method
	////////////////////////////////////////////////////////////
	bool assert_open(const std::string& caller);
public:
	/* =========================================================== */
	/* ============== Constructors and Destructors =============== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// This will make a new Directory object that has no 
	/// associated directory (in filesystem). To associate a 
	/// directory with this object use open_dir(filepath)
	////////////////////////////////////////////////////////////
	Directory();

	////////////////////////////////////////////////////////////
	/// See documentation for default constructor. NOTE: this
	/// constructor also will attempt to open a directory with
	/// the path passed in.
	/// Params:
	/// dir_path - The path of the directory you want to open
	////////////////////////////////////////////////////////////
	Directory(const std::string& dir_path);


	/* =========================================================== */
	/* ======================== Functions ======================== */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Will attempt to open a directory. If a directory is 
	/// successfully opened then all information about the 
	/// prevoius directory will be flushed out. If the dir 
	/// can't be found this method will return false and will
	/// print and print a warning to the console
	/// Params:
	/// dir_path - The path of the directory you want to open
	////////////////////////////////////////////////////////////
	bool open_dir(const std::string& dir_path);


	/* =========================================================== */
	/* ========================= Getters ========================= */
	/* =========================================================== */
	////////////////////////////////////////////////////////////
	/// Will return the number of files that are contained
	/// within the current directory. It is intended for 
	/// iterating over the files in the associated directory
	/// NOTE: this doesn't include additional directories, just 
	/// files.
	////////////////////////////////////////////////////////////
	unsigned int number_of_files();

	////////////////////////////////////////////////////////////
	/// Gets the name of the file contained at the index (file
	/// param). Indexing starts a 0. If you try to access an 
	/// invalid index it will print an error and return an empty
	/// string.
	/// Params:
	/// file - the index of the file you want
	////////////////////////////////////////////////////////////
	std::string get_filename(unsigned int file);

	////////////////////////////////////////////////////////////
	/// Returns true if and only if there is a valid associated
	/// directory in this object
	////////////////////////////////////////////////////////////
	bool is_open();
};

#endif