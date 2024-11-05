#include<dl/studentdao>
#include<string.h>
#include<forward_list>
using namespace inventory;
using namespace datalayer;
using namespace std;
void addStudent()
{
string name, course;
STUDENT std;
STUDENTDAO stdDAO;
cin.ignore(1000,'\n');
cout<<"enter name: ";
getline(cin,name);
cout<<"enter course: ";
getline(cin,course);
std.setName(name);
std.setCourse(course);
try
{
stdDAO.add(&std);
cout<<"student added successfully with code:"<<std.getCode()<<endl<<endl;
}
catch(DAOEXCEPTION daoexception)
{
cout<<daoexception.what()<<"\n";
}
}
void displayStudents()
{
STUDENTDAO stdDAO;
abc::ISTUDENT *std;
try
{
forward_list<abc::ISTUDENT*> *list;
list=stdDAO.getAll();
forward_list<abc::ISTUDENT*>::iterator i;
for(i=list->begin();i!=list->end();i++)
{
std=*i;
cout<<"Code: "<<std->getCode()<<" \tName: "<<std->getName()<<"\tCourse: "<<std->getCourse()<<endl;
}
}
catch(DAOEXCEPTION daoexception)
{
cout<<daoexception.what()<<endl;
}
}

void count()
{
STUDENTDAO std;
int records=std.getCount();
cout<<"Number of students: "<<records<<endl;
}
void getBycode()
{
STUDENTDAO stddao;
abc::ISTUDENT *std;
int code;
cout<<"enter code to search:";
cin>>code;
try
{
std=stddao.getByCode(code);
cout<<"Code: "<<std->getCode()<<" \tName: "<<std->getName()<<"\tCourse: "<<std->getCourse()<<endl;
}
catch(DAOEXCEPTION daoexception)
{
cout<<daoexception.what()<<endl;
}
}

void getByname()
{
 STUDENTDAO stddao;
abc::ISTUDENT *std;
string name;
cout<<"enter name to search: ";
cin.ignore(1000,'\n');
getline(cin,name);
try
{
std=stddao.getByName(name);
cout<<"Code: "<<std->getCode()<<" \tName: "<<std->getName()<<"\tCourse: "<<std->getCourse()<<endl;
}
catch(DAOEXCEPTION daoexception)
{
cout<<daoexception.what()<<endl;
}
}

void getBycourse()
{
STUDENTDAO stddao;
abc::ISTUDENT *std;
string course;
cin.ignore(1000,'\n');
cout<<"enter course to search:";
getline(cin,course);
try
{
std=stddao.getByCourse(course);
cout<<"Code: "<<std->getCode()<<" \tName: "<<std->getName()<<"\tCourse: "<<std->getCourse()<<endl;
}
catch(DAOEXCEPTION daoexception)
{
cout<<daoexception.what()<<endl;
}
}
void update()
{
int code;
string name, course;
cout<<"enter code:";
cin>>code;
cin.ignore(1000,'\n');
cout<<"enter name:";
getline(cin,name);
cout<<"enter course:";
getline(cin,course);
STUDENT std;
STUDENTDAO stddao;
std.setCode(code);
std.setName(name);
std.setCourse(course);
try
{
stddao.update(&std);
cout<<"student updated.\n";
cout<<std.getName();
}
catch(DAOEXCEPTION daoexception)
{
cout<<daoexception.what();
}
}
void remove()
{
int code;
cout<<"enter code:";
cin>>code;
STUDENTDAO std;
try
{
std.remove(code);
cout<<"student removed.\n";
}
catch(DAOEXCEPTION daoexception)
{
cout<<daoexception.what();
}
}


int main()
{
while(1)
{
int ch;
cout<<"1. Add student.\n";
cout<<"2. Display students.\n";
cout<<"3. Count students.\n";
cout<<"4. get by code.\n";
cout<<"5. get by name.\n";
cout<<"6. get by course.\n";
cout<<"7. update.\n";
cout<<"8. remove.\n";
cout<<"9. exit.\n";
cout<<"enter your choice:";
cin>>ch;
if(ch==1) addStudent();
else if(ch==2) displayStudents();
else if(ch==3) count();
else if(ch==4) getBycode();
else if(ch==5) getByname();
else if(ch==6) getBycourse();
else if(ch==7) update();
else if(ch==8) remove();
else break;
}
return 0;
}