#ifndef _LYS_MESSAGE_MANAGER_HPP
#define _LYS_MESSAGE_MANAGER_HPP 1

#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>
#include <mutex>
#include <any>

#include "Lys/LysConfig.hpp"

namespace lys
{

namespace msg
{

class LYS_API BaseMessageHandler
{
public:
    BaseMessageHandler() : m_Active(false) {}
    virtual ~BaseMessageHandler(){}
    void mt_On_Receive(const std::any& msg)
    {
        if (m_Active == true)
        {
            mt_Call(msg);
        }
    }

    void mt_Set_Activation(bool active)
    {
        m_Active = active;
    }

protected:
    virtual void mt_Call(const std::any& msg) = 0;
    bool m_Active;
};

template<class C, class MsgType>
class MessageHandler : public BaseMessageHandler
{
public:
    MessageHandler(void (C::*pmt_Callback)(const MsgType&), C* object) : m_Callback(std::bind(pmt_Callback, object, std::placeholders::_1))
    {}

    void mt_Call(const std::any& msg)
    {
        m_Callback(std::any_cast<const MsgType&>(msg));
    }

private:
    std::function<void(const MsgType&)> m_Callback;
};

}

class LYS_API MessageManager
{
public:
    MessageManager() :  m_Reciever(), m_Mutex(), m_Recursive_Handling_Count(0) {}
    ~MessageManager() {}

    template<class MsgType, class C>
    void mt_Add_Receiver(void (C::*pmt_CallBack)(const MsgType&), C* receive, bool active)
    {
        mt_Lock("mt_Add_Receiver");
        auto& l_List = m_Reciever[typeid(MsgType).hash_code()];
        auto l_it = std::find_if(l_List.begin(), l_List.end(), [&](const std::pair<void*, std::unique_ptr<msg::BaseMessageHandler>>& p){return p.first == receive;});

        if (l_it == l_List.end())
        {
            l_it = l_List.insert(l_it, std::make_pair(receive, nullptr));
        }

        l_it->second.reset(new msg::MessageHandler<C, MsgType>(pmt_CallBack, receive));
        l_it->second->mt_Set_Activation(active);
        mt_Unlock("mt_Add_Receiver");
    }

    template<class MsgType, class C>
    void mt_Remove_Receiver(C* receiver)
    {
        mt_Lock("mt_Remove_Receiver");
        auto& l_List = m_Reciever[typeid(MsgType).hash_code()];
        l_List.erase(std::remove_if(l_List.begin(),
                                    l_List.end(),
                                    [&](const std::pair<void*, std::unique_ptr<msg::BaseMessageHandler>>& p)
                                    {return p.first == receiver;}),
                     l_List.end());
        mt_Unlock("mt_Remove_Receiver");
    }

    template <class MsgType>
    void mt_Send_Message(const MsgType& m)
    {
        std::string l_Str;

        mt_Lock("mt_Send_Message");

        auto& l_Observer = m_Reciever[typeid(MsgType).hash_code()];

        for (auto& l_Handle : l_Observer)
        {
            l_Handle.second->mt_On_Receive(m);
        }

        mt_Unlock("mt_Send_Message");
    }

    template<class MsgType, class C>
    void mt_Set_Activation(C* object, bool active)
    {
        mt_Lock("mt_Set_Activation");
        auto l_List_It = m_Reciever.find(typeid(MsgType).hash_code());

        if (l_List_It != m_Reciever.end())
        {
            auto l_Object_It = std::find_if(l_List_It->second.begin(), l_List_It->second.end(), [&](const std::pair<void*, std::unique_ptr<msg::BaseMessageHandler>>& p){return p.first == object;});

            if (    (l_Object_It != l_List_It->second.end())
                &&  (l_Object_It->second != nullptr))
            {
                l_Object_It->second->mt_Set_Activation(active);
            }
        }

        mt_Unlock("mt_Set_Activation");
    }

protected:
    std::unordered_map<std::size_t, std::vector<std::pair<void*, std::unique_ptr<msg::BaseMessageHandler>>>> m_Reciever;
    std::mutex m_Mutex;
    int m_Recursive_Handling_Count;

    void mt_Lock(const char* requester)
    {
        (void)(requester);
        if (m_Recursive_Handling_Count == 0)
        {
            m_Mutex.lock();
        }
        m_Recursive_Handling_Count++;
    }

    void mt_Unlock(const char* requester)
    {
        (void)(requester);
        m_Recursive_Handling_Count--;

        if (m_Recursive_Handling_Count == 0)
        {
            m_Mutex.unlock();
        }
    }
};

}

#endif // _LYS_MESSAGE_MANAGER_HPP

