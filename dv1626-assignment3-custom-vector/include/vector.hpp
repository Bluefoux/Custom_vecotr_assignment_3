#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T> class Vector{
    private:
        T* m_elements = nullptr;
        const int m_addcap = 10;
        int m_size=0;
        const int m_begin_capacity = 10;
        int m_capacity = m_begin_capacity;
        void larger_vector();
    public:
        Vector() {m_elements = new T[m_capacity];}
        ~Vector()
        {
            if (m_elements != nullptr)
            {
                delete[] m_elements;
            }
        }
        //copy construktor
        Vector(const Vector<T>& cp_Vector){
            m_size = cp_Vector.m_size;
            m_capacity = cp_Vector.m_capacity;
            m_elements = new T[cp_Vector.m_capacity];
            for (int i = 0; i < m_size; i++){
                m_elements[i] = cp_Vector.m_elements[i];
            }
        }

        //copy assignment
        Vector& operator=(const Vector& cp_assignment){
            if (this != &cp_assignment)
            {
                delete[] m_elements;
                m_capacity = cp_assignment.m_capacity;
                m_size = cp_assignment.m_size;
                m_elements = new T[m_capacity];
                for (int i = 0; i < m_size; i++)
                {
                    m_elements[i] = cp_assignment[i];
                }
            }
            return *this;
        }

        //Move construktor
        Vector(Vector&& mv_Vector) noexcept
            : m_elements(nullptr), m_size(0), m_capacity(0)
        {
            m_size = mv_Vector.m_size;
            m_capacity = mv_Vector.m_capacity;
            m_elements = mv_Vector.m_elements;
            mv_Vector.m_elements = nullptr;
            mv_Vector.m_capacity = 0;
            mv_Vector.m_size = 0;
        }

        //Move assignment
        Vector& operator=(Vector&& mv_assignment) noexcept
        {
            if (this != &mv_assignment)
            {
                delete[] m_elements;
                m_size = mv_assignment.m_size;
                m_capacity = mv_assignment.m_capacity;
                m_elements = mv_assignment.m_elements;
                mv_assignment.m_elements = nullptr;
                mv_assignment.m_capacity = 0;
                mv_assignment.m_size = 0;
            }
            return *this;
        }
        const T* data() const;
        void push_back(const T& name);
        void insert(int nmr, const T& obj);
        void clear();
        void erase(int nmbr);
        void pop_back();
        int size() const;
        int capacity() const;
        bool empty() const;
        T& operator[](int number ) const;
        T& front() const;
        T& at(int number) const;
        T& back() const;
};
#endif //VECTOR_HPP


//funktions
template <typename T>
void Vector<T>::push_back(const T& name)
{
    if (Vector::m_size == Vector::m_capacity)
    {
        larger_vector();
    }
    Vector::m_elements[Vector::m_size] = name;
    Vector::m_size++;
}
template <typename T>
int Vector<T>::size() const {return Vector::m_size;}

template <typename T>
int Vector<T>::capacity() const {return Vector::m_capacity;}

template <typename T>
bool Vector<T>::empty() const {return (Vector::m_size == 0);}

template <typename T>
void Vector<T>::clear() {Vector::m_size = 0;}

template <typename T>
void Vector<T>::pop_back() {
    if (Vector::m_size > 0) {Vector::m_size = (Vector::m_size-1);}
}

template <typename T>
T& Vector<T>::front() const 
{
    if (Vector::m_size > 0){
        return Vector::m_elements[0];
    }
    throw ("Vector is empty");
}

template <typename T>
T& Vector<T>::at(int number ) const {
    if (number < Vector::m_size && number >= 0) 
    {
        return Vector::m_elements[number];
    }
    throw ("number out of range");
}

template <typename T>
T& Vector<T>::back() const 
{
    if (Vector::m_size > 0)
    {
        return Vector::m_elements[Vector::m_size-1];
    }
    throw ("Vector is empty");
}

template <typename T>
void Vector<T>::erase(int nmbr) 
{
    if (nmbr >= 0 && nmbr < Vector::m_size)
    {
        for (int i=nmbr; i < Vector::m_size-1; i++)
        {
        Vector::m_elements[i] = Vector::m_elements[i+1];
        }
        Vector::m_size--;
    }
}

template <typename T>
const T* Vector<T>::data() const {return Vector::m_elements;}

template <typename T>
void Vector<T>::insert(int nmr, const T& obj)
{
    if (nmr >= 0 && nmr <= Vector::m_size)
    {
        if (Vector::m_size == Vector::m_capacity)
        {
            larger_vector();
        }
        
        for (int i = Vector::m_size-1; nmr <= i; i--)
        {
            Vector::m_elements[i+1] = Vector::m_elements[i];
        }
        Vector::m_elements[nmr] = obj;
        Vector::m_size++;
    }    
}

template <typename T>
T& Vector<T>::operator[](int number) const {
    if (number < Vector::m_size && number >= 0) 
    {
        return Vector::m_elements[number];
    }
    throw ("Number out of range");
}

template <typename T>
void Vector<T>::larger_vector()
{
    if (Vector::m_capacity == 0)
    {
        Vector::m_capacity = Vector::m_begin_capacity;
    }
    T* m_new_array = new T[int (Vector::m_capacity * Vector::m_addcap)];
    for (int i = 0; i < Vector::m_size; i++)
    {
        m_new_array[i] = Vector::m_elements[i];
    }
    delete[] Vector::m_elements;
    Vector::m_elements = nullptr;
    Vector::m_elements = m_new_array;
    Vector::m_capacity = int(Vector::m_capacity * Vector::m_addcap);
}