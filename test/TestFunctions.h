/**
 * @brief Test_Sınıfı
 * 
 */
class Test
{
public:
    /**
     * @brief Construct a new Test object
     * 
     */
    Test();

    /**
     * @brief Toplama Test Methodu
     * 
     * @tparam T 
     * @param a 
     * @param b 
     * @return T 
     */
    template <typename T>
    static T sumup(T a, T b)
    {
        T temp = a + b;
        return temp;
    }

    /**
     * @brief Çıkarma Test Methodu
     * 
     * @tparam T 
     * @param a 
     * @param b 
     * @return T 
     */
    template <typename T>
    static T subup(T a, T b)
    {
        T temp = a - b;
        return temp;
    }

    /**
     * @brief Bölme Test Methodu
     * 
     * @tparam T 
     * @param a 
     * @param b 
     * @return T 
     */
    template <typename T>
    static T divideup(T a, T b)
    {
        T temp = a / b;
        return temp;
    }
    
    /**
     * @brief Modunu Alma Test Methodu
     * 
     * @tparam T 
     * @param a 
     * @param b 
     * @return T 
     */
    template <typename T>
    static T modup(T a, T b)
    {
        T temp = a % b;
        return temp;
    }

private:
    /**
     * @brief Sınıf parametresi deneme amaçlı
     * 
     */
    int m_x;
};