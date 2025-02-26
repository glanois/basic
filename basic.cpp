#include <fstream>
#include <cstdio>
#include <cstring>
#include <set>
#include <unistd.h>
#include <sys/dir.h>

#include "basic.h"

extern "C" FILE *yyin;

using std::map;
using std::string;
using std::pair;

Basic *Basic::b;

// add a program line at index, overwriting if it exists
void Basic::add(int index, const Program *program){
	// see if index already exists, if so delete it
	remove(index);
	
	lines.insert(pair<int, const Program *>(index, program));
}

// remove an existing line from the program
void Basic::remove(int index){
	map<int, const Program*>::iterator it = lines.find(index);
	if( it != lines.end() ){
		const Program *old = it->second;
		delete old;
		lines.erase(it);
	}	
}

// print out the program lines
void Basic::list(std::ostream &out){
	for( map<int, const Program *>::iterator it = lines.begin(); it!= lines.end(); ++it ){
		out << it->first << " ";
		it->second->list(out);
		out << std::endl;
	}
}

// run the program
void Basic::execute(){
	data.clear();	// clear any existing stored data
	for( map<int, const Program *>::iterator it = lines.begin(); it!= lines.end(); ++it ){
		it->second->preExecute();
	}
	
	counter = lines.begin();
   int c = 0;
	while( counter != lines.end() )
   {
      // Don't have to check the return value here:
      // Statements that terminate the program (STOP, END)
      // do so by callind endProgram(), which sets counter 
      // to lines.end() directly.
		counter->second->execute(true);
   }
}

// access the singleton instance, creating it if necessary
Basic *Basic::instance(){
	if( b == NULL )
		b = new Basic();
	return b;
}

// assign a value to a variable
void Basic::assign(string var, double value){
	// delete value if var already exists
	map<string, double>::iterator it = vars.find(var);
	if( it != vars.end() ){
		vars.erase(it);
	}
	
	vars.insert(pair<string, double>(var, value));
}

// return variable value
double Basic::resolve(string var){
   double result = 0.0;
	map<string, double>::iterator it = vars.find(var);
	if( it == vars.end() )
   {
      printf("ERROR: variable %s not found.\n", var.c_str());
   }
   else
   {
		result = it->second;
	}
   return result;
}

// save active program to disk
void Basic::saveProgram(){
	std::ofstream out;
	out.open(name + ".bas");
	list(out);
}

// delete saved program from disk
void Basic::unsaveProgram(){
	::remove((name + ".bas").c_str());
}

// start a new program
void Basic::newProgram(){
	erase();
	renameProgram();
}

// rename the current program
void Basic::renameProgram(){
	std::cout << "Enter a program name: ";
	std::cin >> name;
	std::cin.ignore();	// consume the newline character
}

// list saved programs
void Basic::catalogPrograms(){
	char cwd[FILENAME_MAX];
	getcwd(cwd, FILENAME_MAX);

    DIR* dirp = opendir(cwd);
    struct dirent * dp;
    std::set<std::string> set;	// store in a set to get alphabetical ordering
    while ((dp = readdir(dirp)) != NULL) {
    	char *sub = strstr(dp->d_name, ".bas");
        if( strstr(dp->d_name, ".bas") ){
        	sub[0] = 0;		// end name before .bas
        	set.insert(dp->d_name);
        }
    }
    closedir(dirp);
    // print them out
    for( std::set<std::string>::iterator it = set.begin(); it != set.end(); ++it ){
    	std::cout << *it << std::endl;
    }
}

// load program from disk
void Basic::oldProgram(){
	erase();
	std::cout << "Enter program to read: ";
	std::cin >> name;
	yyin = fopen((name + ".bas").c_str(), "r");
	if( !yyin ){
		std::cout << "ERROR: could not read file: " << name << ".bas\n";
		yyin = stdin;
	}
}

// clear stored program lines
void Basic::erase(){
	for( map<int, const Program *>::iterator it = lines.begin(); it!= lines.end(); ++it ){
		delete it->second;
	}
	lines.clear();
}

// jump to program line
void Basic::gotoLine(int line){
	counter = lines.find(line);
}

// go to next program line
void Basic::nextLine(){
   if (counter != lines.end())
   {
      ++counter;
   }
}

// go to program line
void Basic::gotoProgram(const Program *program){
	for( map<int, const Program *>::iterator it = lines.begin(); it!= lines.end(); ++it ){
		if( it->second == program )
			counter = it;
	}
}

// end program execution
void Basic::endProgram(){
	counter = lines.end();
}

// assign next data value to var
void Basic::read(std::string var){
	assign(var, data.front());
	data.pop_front();
}

// push more values onto data vector
void Basic::pushData(std::vector<double> vals){
	for( std::vector<double>::iterator it = vals.begin(); it != vals.end(); ++it ){
		data.push_back(*it);
	}
}

// push a FOR loop onto the stack
void Basic::pushFor(const For *forLoop){
	forLoops.push(forLoop);
}

// pop last FOR off the stack
const For* Basic::popFor(){
	const For *loop = forLoops.top();
	forLoops.pop();
	return loop;
}
