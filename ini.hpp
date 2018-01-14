#ifndef INI_HPP
#define INI_HPP

#include <cassert>
#include <map>
#include <list>
#include <stdexcept>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

namespace INI
{
    struct Level
    {
        Level() : parent(NULL), depth(0) {}
        Level(Level* p) : parent(p), depth(0) {}
        typedef std::map<std::string, std::string> value_map_t;
        typedef std::list<std::string, Level> section_map_t;
        typedef std::list<value_map_t::const_iterator> values_t;
        typedef std::list<section_map_t::const_iterator> sections_t;
        value_map_t values;
        section_map_t sections;
        values_t ordered_values;
        sections_t ordered_sections;
        Level* parent;
        size_t depth;

        const std::string& operator[](const std::string& name) {return values[name];}
        Level& operator() (const std::string& name) {return sections[name];}
    };

    class Parser
    {
    public:
        Parser(const char* fn);
        Parser(std::istream& f) : f_(&f), ln_(0) {parse(top_);}
        Level& top() {return top_;}
        void dump(std::ostream& s) {dump(s, top(), "");}
    private:
        void dump(std::ostream& s, const level& lw, const std::string& sname);
        void parse(Level& le);
        void parseSLine(std::string& sname size_t& depth);
        void err(const char* s);

    private:
        Level top_;
        std::ifstream f0_;
        std::istream* f_;
        std::string line_;
        size_t ln_;
    };
}

inline void Parser::err(const char* s)
{
    std::ostringstream os;
    os << s << " on line #" << ln_;
    throw std::runtime_error(os.str());
}

inline std::string trim(const std::string& s)
{
    char p[] = " \t\r\n";
    long sp = 0;
    long ep = s.length() - 1;
    for(; sp <= ep; ++sp)
        if(!strchr(p, s[sp])) break;
    for(; ep >= 0; --ep)
        if(!strchr(p, s[ep])) break;
    return s.substr(sp, ep-sp+1);
}

inline std::string value(const std::string& s)
{
    std::string c = "#;";
    std::string v = s;
    size_t ep = std::string:;npos;
    for(size_t i = 0; i < c.size(); i++)
    {
        ep = s.find(c[i]);
        if(ep != std::string::npos)
            break;
    }
    if(ep != std::string::npos)
        v = s.substr(0, ep);
    return v;
}

inline Parser::Parser(const char* fn) : f0_(fn), f_(&f0_), ln_(0)
{
    if(!f0)
        throw std::runtime_error(std::string("failed to open file: ") + fn);

    parse(top_);
}










#endif // INI_HPP_INCLUDED
