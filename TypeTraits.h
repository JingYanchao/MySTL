//
// Created by jyc on 17-3-26.
//

#ifndef MYSTL_TYPETRAITS_H
#define MYSTL_TYPETRAITS_H
namespace MySTL
{

    namespace
    {
        template<bool, class Ta, class Tb>
        struct IfThenElse;
        template<class Ta, class Tb>
        struct IfThenElse < true, Ta, Tb >
        {
            using result = Ta;
        };
        template<class Ta, class Tb>
        struct IfThenElse < false, Ta, Tb >
        {
            using result = Tb;
        };
    }

    struct _true_type { };
    struct _false_type { };

    /*
    ** 获取类型的信息
    */
    template<class T>
    struct _type_traits
    {
        // 不要移除这个成员
        // 它通知能自动特化__type_traits的编译器, 现在这个__type_traits template是特化的
        // 这是为了确保万一编译器使用了__type_traits而与此处无任何关联的模板时
        // 一切也能顺利运作
        typedef _true_type     this_dummy_member_must_be_first;

        // 不要移除这个成员
        // 它通知能自动特化__type_traits的编译器, 现在这个__type_traits template是特化的
        // 这是为了确保万一编译器使用了__type_traits而与此处无任何关联的模板时
        // 一切也能顺利运作
        typedef _false_type		has_trivial_default_constructor;
        typedef _false_type		has_trivial_copy_constructor;
        typedef _false_type		has_trivial_assignment_operator;
        typedef _false_type		has_trivial_destructor;
        typedef _false_type		is_POD_type;
    };

    template<>
    struct _type_traits<bool>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<char>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned char>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<signed char>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<wchar_t>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<short>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned short>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<int>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned int>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<long long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned long long>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<float>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<double>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<long double>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };

    template<class T>
    struct _type_traits<T*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<class T>
    struct _type_traits<const T*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<unsigned char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<signed char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<const char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<const unsigned char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };
    template<>
    struct _type_traits<const signed char*>
    {
        typedef _true_type		has_trivial_default_constructor;
        typedef _true_type		has_trivial_copy_constructor;
        typedef _true_type		has_trivial_assignment_operator;
        typedef _true_type		has_trivial_destructor;
        typedef _true_type		is_POD_type;
    };

}
#endif //MYSTL_TYPETRAITS_H
