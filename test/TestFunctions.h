class Test
{
public:
    Test();
    template <typename T>
    static T sumup(T a, T b)
    {
        T temp = a + b;
        return temp;
    }
    template <typename T>
    static T subup(T a, T b)
    {
        T temp = a - b;
        return temp;
    }

    template <typename T>
    static T divideup(T a, T b)
    {
        T temp = a / b;
        return temp;
    }
    
    template <typename T>
    static T modup(T a, T b)
    {
        T temp = a % b;
        return temp;
    }

private:
    int m_x;
};