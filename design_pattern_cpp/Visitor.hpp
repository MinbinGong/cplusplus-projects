template<typename... Types>
struct Visitor;

template<typename T, typename... Types>
struct Visitor<T, Types...> : Vistor<Types...>
{
    using Visitor<Types...>::Visit;
    virtual void Visit(const T&) = 0;
};

template<typename T>
struct Visitor<T>
{
    virtual void Visit(const T&) = 0;
};
