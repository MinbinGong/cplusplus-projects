#include <iostream>
#include <map>
#include <memory>

class chat_dialog
{
private:
    
public:
    chat_dialog()
    {
        std::cout << "chat_dialog constructor.\n" << std::endl;
    }
    ~chat_dialog()
    {
        std::cout << "chat_dialog destructor.\n" << std::endl;
    }

    void activate()
    {
        std::cout << __FUNCTION__ << "[" << __LINE__ << "] start...\n" << std::endl;
    }
};

std::map<long, std::unique_ptr<chat_dialog>> m_chat_dialogs;

void on_double_click_friend_item3(long userid)
{
    auto dialog1 = std::make_unique<chat_dialog>();

    auto [iter, inserted] = m_chat_dialogs.try_emplace(userid, std::move(dialog1));
    if (inserted)
    {
        iter->second->activate();
    }
}

int main()
{
    on_double_click_friend_item3(96123413245L);

    return 0;
}