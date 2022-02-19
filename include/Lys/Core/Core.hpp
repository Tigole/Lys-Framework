#ifndef _LYS_CORE_HPP
#define _LYS_CORE_HPP 1

#define LYS_CLASS_NO_COPY(class_type) private: class_type& operator=(const class_type&) = delete; class_type(const class_type&) = delete;

#define LYS_DECL_IMPL_PART_SINGLETON(class_type) LYS_CLASS_NO_COPY(class_type) private: class_type(); public: static class_type& smt_Get() {static class_type ls_Singleton; return ls_Singleton;}


#include <cassert>
#define LYS_ASSERT(expr) assert((expr))

#endif // _LYS_CORE_HPP
