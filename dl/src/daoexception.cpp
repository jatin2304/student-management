#include<dl/daoexception>
using namespace inventory;
using namespace datalayer;
DAOEXCEPTION::DAOEXCEPTION()
{
this->msg="";
}
DAOEXCEPTION::DAOEXCEPTION(string msg)
{
this->msg=msg;
}
DAOEXCEPTION::DAOEXCEPTION(const DAOEXCEPTION &other)
{
this->msg=other.msg;
}
DAOEXCEPTION::~DAOEXCEPTION() throw()
{
//do nothing
}
DAOEXCEPTION & DAOEXCEPTION::operator=(const DAOEXCEPTION &other)
{
this->msg=other.msg;
return *this;
}
const char* DAOEXCEPTION::what() const throw()
{
return this->msg.c_str();
}