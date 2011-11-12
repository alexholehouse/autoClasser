#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctype.h>

using std::cout;
using std::cerr;
using std::string;
using std::endl;
using std::ifstream;
using std::ofstream;

// global constant
const string c_CUSTOM_HEADER_FILE = "cust_header.txt";

bool file_present(string filename);
void build_headerfile(string headerfile, string classname, bool custh);
void build_classfile(string classfile, string classname, bool custh);
string convert_to_upper(string input);
void write_custom_header(ofstream &file);



// MAIN
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main ( int argc, char *argv[] )
{

  // test that we have a single argument, which should be the class name
  if (argc != 2){
    cout << "INVALID INPUT\nUsage is just the new Class name!..." << endl;
    return 1;
  }

  // get the intended classname
  string classname  = argv[1];

  // get the filenames (classname.h and classname.cpp)
  string headerfile = argv[1];
  string classfile = argv[1];
  headerfile.append(".h");
  classfile.append(".cpp");
  
  // check neither header file nor class file exist (if so abort)
  if (file_present(headerfile) || file_present(classfile)){
    cout << "File already exists - don't want to overwrite. " << endl;
    return 1;
  }
  
  cout << "Looking for " << c_CUSTOM_HEADER_FILE << endl;
  
  // if a config file with acustom header is pressent
  if (!file_present(c_CUSTOM_HEADER_FILE)){
    cout << "No default header config file (config.txt) found" << endl
	 << "Not a problem though, we'll just carry on!" << endl;
    
    build_headerfile(headerfile, classname, false);
    build_classfile(classfile, classname, false);
  }
  
  else {
    build_headerfile(headerfile, classname, true);
    build_classfile(classfile, classname, true);
  }
    
}

bool file_present(string filename){
  
  ifstream tester;

  tester.open(filename.c_str(), ifstream::in);
  tester.close();

  // i.e. if we couldnt open the file called "filename"
  if (tester.fail())
    return false;

  // if we could open it then it is present
  else
    return true;
}



// BUILD_HEADERFILE
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Build a default headerfile (using a custom intro if custh is set to true)
void build_headerfile(string headerfile, string classname, bool custh){
  
  ofstream file;

  file.open(headerfile.c_str());

  if (custh)
    write_custom_header(file);
  
  // write define guards...
  string temp = "#ifndef ";
  file << (temp.append(convert_to_upper(classname))).append("_H") << endl;
  temp = "#define ";
  file << (temp.append(convert_to_upper(classname))).append("_H") << endl << endl;

  // reminder about other includes you may want...
  file << "// include any relevant header files here..." << endl << endl;
  
  // doxygen markup
  file << "/*! \\brief <One sentence class summary>" << endl << endl;
  file << "<Longer class description>" << endl;
  file << "*/ " << endl << endl;

  // write the class structure...
  file << "//------------------------------------" << endl;
  temp = "class ";
  file << (temp.append(classname)).append(" : public <PARENT CLASS> {") << endl << endl;
  file << "public:" << endl;
  file << "// Public class methods go here" << endl << endl;
  file << "private:" << endl;
  file << "// Private class methods and class variables go here" << endl << endl;
  file << "};" << endl  << endl;
  
  // end the include guardes
  file << "#endif" << endl;
  
}



// BUILD_CLASSFILE
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void build_classfile(string classfile, string classname, bool custh){
  ofstream file;
  
  file.open(classfile.c_str());
  
  if (custh)
    write_custom_header(file);

  // standard includes - this can be edited for a specific project...
  file << "#include <iostream>" << endl;
  file << "#include <fstream>" << endl;
  file << "#include <string>" << endl;
  file << "#include <cstdlib>" << endl << endl << endl << endl;

  // default constructor override
  file << "//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  file << "//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  file << "// default constructor" << endl;
  file << classname << "::" << classname << "() {"<< endl << endl << "}" << endl;
  file << endl << endl << endl;
  file << "//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  file << "//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  file << "// another function would go here" << endl;
  file << "// <return_value> " << classname << "::<Function Name>(<parameters>){" << endl 
       << endl << "}" << endl << endl;
  file << "// END OF FILE" << endl;
}


// CONVERT_TO_UPPER
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// simple function which converts a string to all uppercase
string convert_to_upper(string input){
  
  int length = input.length();

  for (int i = 0 ; i<length ;i++){
    input[i] = toupper(input[i]);
  }

  return input;
}



// WRITE_CUSTOM_HEADER
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// writes the header contents defined in c_CUSTOM_HEADER_FILE to the top of the file 
// defined in the [file] variable. NB

void write_custom_header(ofstream &file){

  // check input file is actually an open ofstream...
  if (!file.good()){
    cerr << "ERROR - problem with file opening. Aborting..." << endl;
    exit(1);
  }
    
  // build variables
  string line;
  string header_content;
  ifstream conf(c_CUSTOM_HEADER_FILE.c_str());
  
  if (!conf){
    cerr << "ERROR: Unable to open configuration file..." << endl
	 << "Aborting!" << endl;
    exit(1);
  }
  
  // read all of the file defined by c_CUSTOM_HEADER_FILE
  while(getline(conf,line)){
      line.append("\n");
      header_content = header_content.append(line);
  }
  
  // write to your new headerfile
  file << header_content;
  
  cout << "Loaded custom header details..." << endl;
}
