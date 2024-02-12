#include "SingleResponsibility.h"
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <fstream>

/* ----------- Single Responsibility Principle ----------- */
/* 
	The idea behind the SRP is that every class, module, or function in a program should have one responsibility/purpose in a program. 
	As a commonly used definition, "every class should have only one reason to change".

	In the example below, we've created a Journal class for saving daily thoughts and ideas. We then decide that we would like to save
	our Journal entries to an external .txt file. Our first inclination may be to create a save() function in the Journal class. However, 
	is the saving of data to a .txt file the responsibility of a Journal? No, the Journal class should only contain functions and variables
	that directly relate to the Journal itself. Instead we should be creating a new class that handles anything to do with file persistence 
	(ie, save/load/print). 
*/

struct Journal
{
	std::string title;
	std::vector<std::string> entries;

	Journal(const std::string &title) : title(title) {}

	void add_entry(const std::string& entry)
	{
		static int count = 1;
		entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);

	}

	/*
		The save function below is the wrong approach. We know that if we're going to save, we'll likely want to load, and let's say we move from files to databases, we're now going to expand this even further.
		So, this whole realm of "data persistence" should not be the responsibility of the Journal class. Instead we add in a new class called PersistenceManager, shown below.
	*/

	//void save(const std::string& filename)
	//{
	//	std::ofstream ofs(filename); 
	//	for (auto& e : entries) 
	//	{
	//		ofs << e << std::endl; 
	//	}
	//}
};

struct PersistenceManager
{
	static void save(const Journal& journal, const std::string& filename)
	{
		std::ofstream ofs(filename);
		for (auto& entry : journal.entries)
		{
			//ofs << entry << std::endl;
			std::cout << entry << std::endl; 


		}
	}
};


void SingleResponsibility::run() {
	std::cout << "1. SINGLE RESPONSIBILITY" << std::endl; 
	Journal journal{ "My Diary Title" };
	journal.add_entry("My first entry.. ");
	journal.add_entry("My second entry... ");
	// Instead of doing journal.save("Storage/Matt's diary.txt") we now do the following: 
	PersistenceManager persistenceManager;
	persistenceManager.save(journal, "Storage/Matt's diary.txt");
}
