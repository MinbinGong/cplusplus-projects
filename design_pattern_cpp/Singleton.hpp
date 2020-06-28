template <typename T>
class Singleton
{
private:
    Singleton(void);
    virtual ~Singleton(void);
    Singleton(const Singleton &);
    Singleton &operator=(const Singleton &);

private:
    static T *m_pInstance;

public:
    template <typename... Args>
    static T *Instance(Args... args)
    {
        if (m_pInstance == nullptr)
        {
            m_pInstance = new T(std::forward<Args>(args)...); //perfect forwarding
        }

        return m_pInstance;
    }

    static T* GetInstance()
    {
        if (m_pInstance == nullptr)
        {
            throw std::logic_error("The instance is not init, please initialize the instance first.");
        }
        return m_pInstance;
    }

    static void DestroyInstance()
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
};

template<class T> T* Singleton<T>::m_pInstance = nullptr;