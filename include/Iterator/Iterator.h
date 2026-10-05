
template<typename T>
class Iterator 
{
    public:
        virtual ~Iterator() {}
        virtual const T* first() const = 0;
        virtual const T* next() = 0;
        virtual const T* current() const = 0;
};