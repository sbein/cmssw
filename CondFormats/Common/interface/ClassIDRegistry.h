#ifndef CondFormatCommon_ClassIDRegistry_H
#define CondFormatCommon_ClassIDRegistry_H
#include <typeinfo>
#include<vector>
#include<string>

namespace cond {

  namespace idCategories {
    std::string const dictIDCategory("LCGDictID");
    std::string const pythonIDCategory("CondPythonID");
  }

  class ClassIDRegistry;

    class ClassInfo {
    public:
      inline ClassInfo(const std::type_info& t) : tinfo(t) {}
      inline ClassInfo(const std::type_info& t, int);
      inline const std::type_info& type() const { return tinfo;}
      std::string pluginName(std::string const & prefix) const;
      virtual std::string resource() const=0;
    private:
      ClassIDRegistry * registry;
      const char * registerMe(const std::type_info& t);
      const std::type_info& tinfo;
    };
 

  class ClassIDRegistry {
  public:
    typedef ClassInfo Elem;
    std::vector<std::string> sids;
    std::vector<const char*> csids;
    ClassIDRegistry(std::string const & pfix);
    
   const char * registerMe(const std::type_info& t);
    
  private:
    std::string prefix;
    
  };

  template<typename T>
  struct ClassID : public  ClassInfo {
    ClassID(std::string const & res ) : ClassInfo(typeid(T)), m_res(res) {}
    ClassID(int i) : ClassInfo(typeid(T),i) {}
    virtual std::string resource() const { return m_res;}
  private:
    std::string m_res;
  };
  
    
}

// magic: works only if a file local registry exists in the file
#define ELEM_CONSTR(xx_)						\
  cond::ClassInfo::ClassInfo(const std::type_info& t,int) : tinfo(t) {registry = &xx_;registerMe(t);} 


#include "FWCore/PluginManager/interface/PluginFactory.h"
namespace cond{
  typedef edmplugin::PluginFactory<ClassInfo*() > ClassInfoFactory;
}

#endif
