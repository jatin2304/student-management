#include<iostream>
#include<dl/studentdao>
#include<dl/istudentdao>
#include<string.h>
#include<fstream>
using namespace std;
using namespace inventory;
using namespace datalayer;

void STUDENTDAO::add(abc::ISTUDENT *std) throw(DAOEXCEPTION)
{
string vname=std->getName();
string vcourse=std->getCourse();
string name=trim(vname);
string course=trim(vcourse);
if(vname.length()==0) throw DAOEXCEPTION(string("Name cannot be empty."));
if(vname.length()>50) throw  DAOEXCEPTION(string("length of Name cannot exceed 50."));
HEADER header;
_STUDENT _std;
fstream datafile(FileName,ios::in |ios::out | ios::binary);
if(datafile.fail()) //file does not exists
{
ofstream dfile(FileName,ios::app|ios::binary);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dfile.write((char*)&header, sizeof(HEADER));
_std.code=header.lastGeneratedCode; //1
strcpy(_std.name,name.c_str());
strcpy(_std.course, course.c_str());
dfile.seekp(0,ios::end);
dfile.write((char*)&_std, sizeof(_STUDENT));
dfile.close();
std->setCode(1);
return;
}
datafile.seekg(0,ios::beg);
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail())  //empty file
{
datafile.clear();
datafile.seekp(0,ios::beg);
datafile.seekg(0,ios::beg);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
datafile.write((char*)&header,sizeof(HEADER));
_std.code=header.lastGeneratedCode; //1
strcpy(_std.name,name.c_str());
strcpy(_std.course, course.c_str());
datafile.seekp(0,ios::end);
datafile.write((char*)&_std, sizeof(_STUDENT));
std->setCode(1);
return;
}
while(true)
{
datafile.read((char*)&_std,sizeof(_STUDENT));
if(datafile.fail()) break;
if(compareStringIncase(_std.name,name.c_str())==0) 
{
datafile.close();
throw DAOEXCEPTION(name+string("already exists."));
}
}
datafile.clear();
header.lastGeneratedCode++;
header.numberOfRecords++;
_std.code=header.lastGeneratedCode;
strcpy(_std.name,name.c_str());
strcpy(_std.course, course.c_str());
datafile.seekp(0,ios::end);
datafile.write((char*)&_std,sizeof(_STUDENT));
datafile.seekp(0,ios::beg);
datafile.write((char*)&header,sizeof(HEADER));
datafile.close();
std->setCode(header.lastGeneratedCode);
}

void STUDENTDAO::update(abc::ISTUDENT *std) throw(DAOEXCEPTION)
{
int code=std->getCode();
if(code<=0)
{
throw DAOEXCEPTION(string("provide valid code.\n"));
}
HEADER header;
fstream datafile(FileName, ios::in | ios::out | ios::binary);
if(datafile.fail()) throw DAOEXCEPTION(string("unable to update as no student added.\n"));
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
throw DAOEXCEPTION(string("unable to update as no student added.\n"));
}
if(header.numberOfRecords==0)
{
datafile.close();
throw DAOEXCEPTION(string("unable to update as no student added.\n"));
}
if(header.lastGeneratedCode<code)
{
datafile.close();
throw DAOEXCEPTION(string("invalid code, unable to update.\n"));
}
_STUDENT _std;
string vname=std->getName(); 
string vcourse=std->getCourse();
code=std->getCode();
string name=trim(vname);
string course=trim(vcourse);
int pos;
int found=0;
while(true)
{
pos=datafile.tellg();
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(_std.code==code)
{
found=1;
break;
}
}
if(found==0)
{
datafile.close();
throw DAOEXCEPTION(string("invalid code, unable to update.\n"));
}
datafile.clear();
datafile.seekg(sizeof(HEADER),ios::beg);
//datafile.read((char*)&header,sizeof(HEADER));
while(true)
{
datafile.read((char*)&_std,sizeof(_STUDENT));
if(datafile.fail()) break;
if(compareStringIncase(_std.name,name.c_str())==0 && _std.code!=code)
{
datafile.close();
throw DAOEXCEPTION(string("unable to update as student already exists.\n"));
}
}
datafile.clear();
_std.code=code;
strcpy(_std.name,name.c_str());
strcpy(_std.course,course.c_str());
datafile.seekp(pos,ios::beg);
datafile.write((char*)&_std,sizeof(_STUDENT));
if(datafile.fail()) 
{
datafile.close();
throw DAOEXCEPTION(string("unable to update student1.\n"));
}
datafile.close();
}


void STUDENTDAO::remove(int code) throw(DAOEXCEPTION)
{
HEADER header;
ifstream datafile(FileName, ios::in | ios::binary);
if(datafile.fail()) throw DAOEXCEPTION(string("unable to remove.\n"));
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail())
{
datafile.close();
throw DAOEXCEPTION(string("unable to remove.\n"));
}
if(header.numberOfRecords==0)
{
datafile.close();
throw DAOEXCEPTION(string("unable to remove.\n"));
}
ofstream tmp("temp.dat",ios::out |ios::binary);
_STUDENT _std;
header.numberOfRecords--;
datafile.seekg(sizeof(HEADER), ios::beg);
tmp.seekp(0, ios::beg);
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(_std.code!=code) tmp.write((char*)&_std, sizeof(_STUDENT));
}
datafile.close();
tmp.close();
ofstream dfile(FileName, ios::out|ios::binary);
ifstream tfile("temp.dat",ios::in | ios::binary);
dfile.write((char*)&header, sizeof(HEADER));
while(true)
{
tfile.read((char*)&_std, sizeof(_STUDENT));
if(tfile.fail()) break;
dfile.write((char*)&_std,sizeof(_STUDENT));
if(dfile.fail())
{
dfile.close();
throw DAOEXCEPTION(string("unable to remove.\n"));
}
}
dfile.close();
tfile.close();
}

forward_list<abc::ISTUDENT *> * STUDENTDAO::getAll() throw(DAOEXCEPTION)
{
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) throw DAOEXCEPTION(string("No students are added...\n"));
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
throw DAOEXCEPTION(string("No students are added...\n"));
}
if(header.numberOfRecords==0) 
{
datafile.close();
throw DAOEXCEPTION(string("No students are added...\n"));
}
_STUDENT _std;
abc::ISTUDENT *std;
forward_list<abc::ISTUDENT *> *list;
list=new forward_list<abc::ISTUDENT *>;
forward_list<abc::ISTUDENT*> ::iterator i=list->before_begin();
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
std=new STUDENT;
std->setCode(_std.code);
std->setName(string(_std.name));
std->setCourse(string(_std.course));
i=list->insert_after(i,std);
}
datafile.close();
return list;
}

abc::ISTUDENT* STUDENTDAO::getByCode(int code) throw(DAOEXCEPTION)
{
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) throw DAOEXCEPTION(string("Invalid code"));
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
throw DAOEXCEPTION(string("Invalid code"));
}
if(header.numberOfRecords==0) 
{
datafile.close();
throw DAOEXCEPTION(string("Invalid code"));
}
_STUDENT _std;
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(code==_std.code)
{
abc::ISTUDENT *std;
std=new STUDENT;
std->setCode(_std.code);
std->setName(string(_std.name));
std->setCourse(string(_std.course));
datafile.close();
return std;
}
}
datafile.close();
throw DAOEXCEPTION(string("Invalid code"));
}

abc::ISTUDENT* STUDENTDAO::getByName(string name) throw(DAOEXCEPTION)
{
string vname=trim(name);
//if(vname.length()==0) throw DAOEXCEPTION(string("Name cannot be empty."));
//if(vname.length()>50) throw  DAOEXCEPTION(string("length of Name cannot exceed 50."));
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) throw DAOEXCEPTION(string("Invalid name."));
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
throw DAOEXCEPTION(string("Invalid name."));
}
if(header.numberOfRecords==0) 
{
datafile.close();
throw DAOEXCEPTION(string("Invalid name."));
}
_STUDENT _std;
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(compareStringIncase(_std.name,name.c_str())==0)
{
abc::ISTUDENT *std;
std=new STUDENT;
std->setCode(_std.code);
std->setName(string(_std.name));
std->setCourse(string(_std.course));
datafile.close();
return std;
}
}
datafile.close();
throw DAOEXCEPTION(string("Invalid name"));
}

abc::ISTUDENT* STUDENTDAO::getByCourse(string course) throw(DAOEXCEPTION)
{
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) throw DAOEXCEPTION(string("Invalid course."));
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
throw DAOEXCEPTION(string("Invalid course."));
}
if(header.numberOfRecords==0) 
{
datafile.close();
throw DAOEXCEPTION(string("Invalid course."));
}
_STUDENT _std;
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(course==_std.course)
{
abc::ISTUDENT *std;
std=new STUDENT;
std->setCode(_std.code);
std->setName(string(_std.name));
std->setCourse(string(_std.course));
datafile.close();
return std;
}
}
datafile.close();
throw DAOEXCEPTION(string("Invalid course"));
}

int STUDENTDAO::getCount() throw(DAOEXCEPTION)
{
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) return 0;
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
return 0;
}
datafile.close();
return header.numberOfRecords;
}

int STUDENTDAO::codeExists(int code) throw(DAOEXCEPTION)
{
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) return 0;
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
return 0;
}
if(header.numberOfRecords==0) 
{
datafile.close();
return 0;
}
_STUDENT _std;
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(code==_std.code) 
{
datafile.close();
return 1;
}
}
datafile.close();
return 0;
}

int STUDENTDAO::nameExists(string name) throw(DAOEXCEPTION)
{
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) return 0;
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
return 0;
}
if(header.numberOfRecords==0) 
{
datafile.close();
return 0;
}
_STUDENT _std;
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(compareStringIncase(_std.name,name.c_str())!=0)
{
datafile.close();
 return 1;
}
}
datafile.close();
return 0;
}

int STUDENTDAO::courseExists(string course) throw(DAOEXCEPTION)
{
HEADER header;
fstream datafile(FileName,ios::in | ios::binary);
if(datafile.fail()) return 0;
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail()) 
{
datafile.close();
return 0;
}
if(header.numberOfRecords==0) 
{
datafile.close();
return 0;
}
_STUDENT _std;
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
if(compareStringIncase(_std.course,course.c_str())!=0) {
datafile.close();
return 1;
}
}
datafile.close();
return 0;
}
