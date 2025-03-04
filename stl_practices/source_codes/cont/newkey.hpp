#ifndef NEW_KEY_HPP
#define NEW_KEY_HPP

namespace MyLib
{
    template <typename Cont>
    inline bool replace_key(Cont &c,
                            const typename Cont::key_type &old_key,
                            const typename Cont::key_type &new_key)
    {
        typename Cont::iterator pos;
        pos = c.find(old_key);
        if (pos != c.end())
        {
            c.insert(typename Cont::value_type(new_key, pos->second));
            c.erase(pos);
            return true;
        }
        else
        {
            return false;
        }
    }
} // namespace MyLib

#endif