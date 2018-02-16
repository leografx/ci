#include <iostream>
#include <string>
#include <fstream>
 
 using namespace std;

enum comm { CONTROLLER, MODEL, LIBRARY, CLI }; 

void generate(int command, string name );
void makeController( string name );
void makeModel( string name );
string capitalize(string);
void processCommand(const char**);
void writeFile(string filename, string data);
void makeLibrary(string name);
void makeCLI(string name);



int main(int argc, const char ** argv){

    processCommand(argv);
    return 0;

}

void processCommand(const char** argv){

    if( strcmp(argv[1],"g")  == 0 ) {
        if ( strcmp(argv[2],"controller")==0 ){
            string name = (string) argv[3];
            generate(CONTROLLER, name);
        }
        
        if ( strcmp(argv[2],"model")==0 ){
            string name = (string) argv[3];
            generate(MODEL, name);
        }
                
        if ( strcmp(argv[2],"library")==0 ){
            string name = (string) argv[3];
            generate(LIBRARY, name);
        }

        if ( strcmp(argv[2],"cli")==0 ){
            string name = (string) argv[3];
            generate(CLI, name);
        }
    }

}



void generate(int command, string name ){
    
    switch( command ) {
        case 0 : {  makeController( name ); break; }
        case 1 : {  makeModel( name ); break; }
        case 2 : {  makeLibrary( name ); break; }
        case 3 : {  makeCLI( name ); break; }
        default  : break;
    }
}

void makeController( string name ){
    string data;
    data += "<?php\n";
    data += "defined('BASEPATH') OR exit('No direct script access allowed');\n";
    data += "\nclass "+capitalize(name)+" extends CI_Controller {\n";
    data += "\tpublic function index()\n";
    data += "\t{\n";
	data += "\t\t$this->load->view('"+name+"');\n";
	data += "\t}\n";
    data += "}\n";

    name +=".php";
    string path = "./application/controllers/" + capitalize(name);
    writeFile(path, data);
}

void makeModel( string name ){
    string data;
    data += "<?php\n";
    data += "defined('BASEPATH') OR exit('No direct script access allowed');\n";
    data += "\nclass "+capitalize(name)+"_model extends CI_Model {\n";
    data += "\n}\n";

    name +="_model.php";
    string path = "./application/models/" + capitalize(name);
    writeFile(path, data);
}

void makeLibrary(string name){
    string data;
    data += "<?php defined('BASEPATH') OR exit('No direct script access allowed');\n";
    data += "\n class "+capitalize(name)+" {\n";
    data +="\n \t public function __construct($params)\n";
    data += " \t {\n";
    data += "\t\t // Do something with $params\n";
    data += "\t } \n";
    data += "}\n";
    
    name +=".php";
    string path = "./application/libraries/" + capitalize(name);
    writeFile(path, data);
}

void makeCLI(string name){
    string data;
    data += "<?php \n";
    data += "class" +capitalize(name)+"extends CI_Controller { \n";
    data += "\n \t public function message($to = 'World') \n";
    data += "\t { \n";
    data += "\t \t echo \"Hello {$to}!\".PHP_EOL;";
    data += "\n\t } \n";
    data += "} \n";
    
    name +="_command.php";
    string path = "./application/controllers/" + capitalize(name);
    writeFile(path, data);
}

string capitalize(string value){
    int size = value.length();
    for (int i = 0; i < size; i++){
        value[i]  = tolower(value[i]);
    }
    
    value[0] = toupper(value[0]);
    return value;
}

void writeFile(string filename, string data){
    fstream fs;
    fs.open(filename,fstream::out);
    fs << data;
    fs.close();
}