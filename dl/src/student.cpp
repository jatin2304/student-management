#include<iostream>
#include<dl/istudent>
#include<dl/student>
using namespace inventory;
using namespace datalayer;
STUDENT::STUDENT()
{
this->code=0;
this->name="";
this->course="";
}
STUDENT::STUDENT(int code,string name,string course)
{
this->code=code;
this->name=name;
this->course=course;
}
STUDENT::STUDENT(STUDENT & other)
{
this->code=other.code;
this->name=other.name;
this->course=other.course;
}
STUDENT::~STUDENT()
{
}
void STUDENT::setCode(int code)
{
this->code=code;
}
int STUDENT::getCode() const
{
return this->code;
}
void STUDENT::setName(string name)
{
this->name=name;
}
string STUDENT::getName() const
{
return this->name;
}
void STUDENT::setCourse(string course)
{
this->course = course;
}
string STUDENT::getCourse() const
{
return this->course;
}