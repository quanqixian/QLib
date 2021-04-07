#ifndef QSTRING_H
#define QSTRING_H

#include "Object.h"
#include "Exception.h"
#include <cstdlib>
#include <cstring>

namespace QLib
{

class QString : public Object
{
protected:
    char * m_str;
    int m_length;
    void init(const char * s);
    static int * make_pmt(const char * p);
    static int kmp(const char * s, const char * p);
public:
    QString();
    QString(char c);
    QString(const char * s);
    QString(const QString & s);
    ~QString();
    int length() const;
    const char *str() const;

    /* 操作符重载相关函数 */
    bool operator == (const QString & s) const;
    bool operator == (const char  * s) const;
    bool operator != (const QString & s) const;
    bool operator != (const char  * s) const;
    bool operator > (const QString & s) const;
    bool operator > (const char  * s) const;
    bool operator < (const QString & s) const;
    bool operator < (const char  * s) const;
    bool operator >= (const QString & s) const;
    bool operator >= (const char  * s) const;
    bool operator <= (const QString & s) const;
    bool operator <= (const char  * s) const;

    QString operator + (const QString & s) const;
    QString operator + (const char * s) const;
    QString & operator += (const QString & s);
    QString & operator += (const char * s);

    QString operator -(const QString & s) const;
    QString operator -(const char * s) const;
    QString & operator -= (const QString & s);
    QString & operator -= (const char * s);

    QString & operator = (const QString & s);
    QString & operator = (const char * s);
    QString & operator = (char c);

    char & operator[](int i);
    char & operator[](int i) const;

    bool startWith(const char * s) const;
    bool startWith(const QString & s) const;
    bool endOf(const char * s) const;
    bool endOf(const QString & s) const;
    bool equal(const char * l, const char * r, int len) const;

    QString & insert(int i, const char * s);
    QString & insert(int i, const QString & s);
    QString & trim();

    int indexOf(const char * s) const;
    int indexOf(const QString & s) const;

    /* 删除指定下标指定长度的字符串 */
    QString & remove(int i, int len);
    /* 在字符串中将指定的子串删除 */
    QString & remove(const char * s);
    QString & remove(const QString & s);
    /* 字符串的子串替换 */
    QString & replace(const char * t, const char * s);
    QString & replace(const QString & t, const char * s);
    QString & replace(const char * t, const QString & s);
    QString & replace(const QString & t, const QString & s);

    QString sub(int i, int len) const;
};

void QString::init(const char * s)
{
    m_str = strdup(s);
    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to craete QString object...");
    }
}

QString::QString()
{
    init("");
}

QString::QString(const char * s)
{
    init(s ? s : "");
}

QString::QString(const QString & s)
{
    init(s.m_str);
}

QString::QString(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

QString::~QString()
{
    free(m_str);
}

int QString::length() const
{
    return m_length;
}

const char * QString::str() const
{
    return m_str;
}

bool QString::operator == (const QString & s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool QString::operator == (const char *s ) const
{
    return (strcmp(m_str, s) == 0);
}

bool QString::operator != (const QString & s) const
{
    return !(*this == s);
}

bool QString::operator != (const char *s) const
{
    return !(*this == s);
}

bool QString::operator > (const QString & s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool QString::operator > (const char *s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool QString::operator < (const QString & s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}

bool QString::operator < (const char * s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool QString::operator >= (const QString & s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}

bool QString::operator >= (const char * s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool QString::operator <= (const QString & s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}

bool QString::operator <= (const char * s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

QString QString::operator + (const QString & s) const
{
    return (*this + s.m_str);
}

QString QString::operator + (const char * s) const
{
    QString ret;
    int len = m_length + strlen(s ? s : "");
    char * str = reinterpret_cast<char *>(malloc(len + 1));
    if(str)
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add QString value...");
    }

    return ret;
}

QString & QString::operator += (const QString & s)
{
    return (*this = *this + s);
}

QString & QString::operator += (const char * s)
{
    return (*this = *this + s);
}

QString & QString::operator = (const QString & s)
{
    return (*this = s.m_str);
}

QString & QString::operator = (const char * s)
{
    if(m_str != s)
    {
        char * str = strdup(s ? s : "");
        if(str != nullptr)
        {
            free(m_str);
            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign a new QString value...");
        }
    }
}

QString & QString::operator = (char c)
{
     char s[] = {c,'\0'};
     return (*this = s);
}

char & QString::operator[](int i)
{
    if((i >= 0) && (i < m_length))
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter is is invalid...");
    }
}

char & QString::operator[](int i) const
{
    return (const_cast<QString & >(*this))[i];
}

bool QString::equal(const char * l, const char *r, int len) const
{
    bool ret = true;

    for(int i = 0; (i<len) && ret; i++)
    {
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

bool QString::startWith(const char * s) const
{
    bool ret = (s != nullptr);

    if(ret)
    {
        int len = strlen(s);
        ret = (len < m_length) && (equal(m_str, s, len));
    }

    return ret;
}

bool QString::startWith(const QString & s) const
{
    return startWith(s.m_str);
}

bool QString::endOf(const char * s) const
{
    bool ret = (s != nullptr);

    if(ret)
    {
        int len = strlen(s);
        char * str = m_str + (m_length - len);
        ret = (len < m_length) && (equal(str, s, len));
    }

    return ret;
}

bool QString::endOf(const QString & s) const
{
    return endOf(s.m_str);
}

QString & QString::insert(int i, const char * s)
{
    if((i >= 0) && (i <= m_length))
    {
        if((s != nullptr) && (s[0] != '\0'))
        {
            int len = strlen(s);
            char * str = reinterpret_cast<char *>(malloc(m_length + len + 1));
            if(str != nullptr)
            {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);
                str[m_length + len] = '\0';

                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign a new QString value...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }

    return *this;
}

QString & QString::insert(int i, const QString & s)
{
    return insert(i, s.m_str);
}

QString&QString::trim()
{
    int b = 0;
    int e = m_length - 1;

    while(m_str[b] == ' ') b++;
    while(m_str[e] == ' ') e--;

    if(b == 0)
    {
        m_str[e + 1] = '\0';
        m_length = e + 1;
    }
    else
    {
        for(int i = 0, j = b; j <= e; i++,j++)
        {
            m_str[i] = m_str[j];
        }
        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }

    return *this;
}

int * QString::make_pmt(const char * p)
{
    int len = strlen(p);
    int * ret = static_cast<int * >(malloc(sizeof(int) * len));
    if(ret != nullptr)
    {
        int ll = 0;             /* 前缀 后缀的交际中的最大长度(longest length) */
        ret[0] = 0;             /* 下标为1的ll值为0 */
        for(int i = 1; i < len; i++)  /* 确定剩下元素的ll值 */
        {
            while((ll > 0) && (p[i] != p[ll]))
            {
                ll = ret[ll - 1];
            }
            if(p[i] == p[ll])
            {
                ll++;
            }
            ret[i] = ll;
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create a pmt...");
    }

    return ret;
}

int QString::kmp(const char * s, const char * p)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int * pmt = make_pmt(p);
    if((pmt != nullptr) && (pl > 0) && (pl <= sl))
    {
        for(int i = 0, j = 0; i < sl; i++)
        {
            while((j > 0) && (s[i] != p[j]))/* 如果匹配不成功，移动子串，查pmt表改变j的值 */
            {
                j = pmt[j - 1];
            }
            if(s[i] == p[j])/* 单个字符匹配相等，j加一 */
            {
                j++;
            }
            if(j == pl)     /* 相等长度等于子串长度，则匹配完成 */
            {
                ret = i + 1 - pl;
                break;
            }
        }
    }

    free(pmt);
    return ret;
}

int QString::indexOf(const char * s) const
{
    return kmp(m_str, s ? s : "");
}

int QString::indexOf(const QString & s) const
{
    return kmp(m_str, s.m_str);
}

/*删除指定下标指定长度的字符串*/
QString & QString::remove(int i, int len)
{
    if((i >= 0) && (i < m_length))
    {
        int n = i;
        int m = i + len;

        while((n < m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
}

/*在字符串中将指定的子串删除*/
QString & QString::remove(const char * s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

QString & QString::remove(const QString & s)
{
    return remove(indexOf(s), s.length());
}

QString QString::operator - (const QString & s) const
{
    return QString(*this).remove(s);/* 通过拷贝构造函数构造一个新的字符串对象 */
}

QString QString::operator - (const char *s) const
{
    return QString(*this).remove(s);
}

QString & QString::operator -= (const QString & s)
{
    return remove(s);
}

QString & QString::operator -= (const char * s)
{
    return remove(s);
}

QString & QString::replace(const char * t, const char * s)
{
    int index = indexOf(t);
    if(index >= 0)
    {
        remove(t);
        insert(index, s);
    }

    return *this;
}

QString & QString::replace(const QString & t, const char * s)
{
    return replace(t.m_str, s);
}

QString & QString::replace(const char * t, const QString & s)
{
    return replace(t, s.m_str);
}

QString & QString::replace(const QString & t, const QString & s)
{
    return replace(t.m_str, s.m_str);
}

QString QString::sub(int i, int len) const
{
    QString ret;
    if((i >= 0) && (i < m_length))
    {
        if(len < 0) len = 0;
        if((i + len) > m_length)
        {
            len = m_length - i;
        }
        char *substr = reinterpret_cast<char *>(malloc(len));
        if(substr != nullptr)
        {
            strncpy(substr, m_str + i, len);
            ret = substr;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create sub QString...");
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }

    return ret;
}

}/* end of namespace */
#endif
