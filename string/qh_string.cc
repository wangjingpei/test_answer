#include "qh_string.h"

#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
    {
		data_=new char[1];
		data_[0]='\0';
		len_=0;
	
    }

	//通用构造函数
    string::string( const char* s )
    {
	if (!s)
	{
		len_ = 0;
		data_ = new char[1];
		*data_ = '\0';
	}
	else
	{
		len_ = strlen(s);
		data_ = new char[len_ + 1];
		strcpy(data_,s);
	}
    }

    string::string( const char* s, size_t len )
    {
	if( NULL == s )
      {
       len_ = 0;
       data_ = new char [1];
       *data_ = '\0';
      }
    else
     {
      len_ = (strlen(s) < len) ? strlen(s) : len;
      data_ = new char [len_ + 1];
      strncpy( data_, s, len_ );
      *(data_ + len_) = '\0';
     }
    }

	//拷贝构造函数
    string::string( const string& rhs )
    {
	len_ = rhs.size();
	data_ = new char[len_ + 1];
	strcpy(data_, rhs.c_str());
    }

    string& string::operator=( const string& rhs )
    {
	if (this == &rhs)	
	return *this;
	delete []data_;
	len_ = rhs.len_;
	data_ = new char[len_ + 1];
	strcpy(data_, rhs.c_str());
    return *this;
    }

    string::~string()
    {
		if (data_ != NULL)
			delete[] data_;
		len_= 0;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return c_str();
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        return (index>len_) ? NULL : data_+index;
    }
}
