forward_list<abc::ISTUDENT *> * STUDENTDAO::getAll() throw DAOEXCEPTION()
{
HEADER header;
fstream datafile(FileName, ios::in | ios::binary);
if(datafile.fail()) throw DAOEXCEPTION("No students added yet");
datafile.read((char*)&header, sizeof(HEADER));
if(datafile.fail())
{
datafile.close();
throw DAOEXCEPTION("No students added yet");
}
if(header.lastGeneratedCode==0)
{
datafile.close();
throw DAOEXCEPTION("No students added yet");
}
_STUDENT _std;
abc::ISTUDENT *istd
forward_list<abc::ISTUDENT *> *list;
list=forward_list<abc::ISTUDENT*>;
forward_list<abc::ISTUDENT *>::iterator i=list->before_begin();
while(true)
{
datafile.read((char*)&_std, sizeof(_STUDENT));
if(datafile.fail()) break;
istd=new STUDENT;
istd->setCode(_std.code);
istd->setName(string(_std.name));
istd->setCourse(string(_std.course));
i=list->insert_after(i,istd);
}
datafile.close();
return list;
}