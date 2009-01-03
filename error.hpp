#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <exception>

namespace sfgui {
class Error: public std::exception
{
public:
    Error(const char * phrase="") throw() : m_phrase(phrase)
    {}
 
     virtual const char* what() const throw()
     {
         return m_phrase;
     }
     
    virtual ~Error() throw()
    {}
 
private:
    char const* m_phrase;       ///< Description of the error
};
}

#endif
