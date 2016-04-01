#ifndef _INIFILEH_
#define _INIFILEH_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>

class Inifile
{
  public:
    Inifile()
    {}
    Inifile(const std::string filename) {
        read(filename.c_str());
    }
    void read(const std::string filename)  {
        boost::property_tree::ini_parser::read_ini(filename, pt);
    }
    template<typename T>
    T get(const std::string str) const {
        return pt.get<T>(str);
    }
    template<typename T>
    T get(const std::string str, T defval) const {
       T result;
       try {
          result = pt.get<T>(str);
       }
       catch (...) {
          result = defval;
       }
       return result;
    }
  private:
    boost::property_tree::ptree pt;
};

#endif
