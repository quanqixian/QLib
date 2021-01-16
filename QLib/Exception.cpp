#include "Exception.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

namespace QLib
{

void Exception::init(const char * message, const char * file, int line)
{
    m_message = (message ? strdup(message) : NULL);
    if(file != NULL)
    {
        char s1[16] = {0};

        snprintf(s1, sizeof(s1), "%d", line);
        m_location = static_cast<char *>(malloc(strlen(file) + strlen(s1)+2));
        if(m_location != NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, s1);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char * message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char * file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char * message, const char * file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception & Exception::operator = (const Exception & e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);
        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }
    return *this;
}

const char * Exception::message() const
{
    return m_message;
}

const char * Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}
