#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_
#include<iostream>
#include<assert.h>
#define DEFAULT_LEN 4


namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
			: data_(NULL), size_(0), capacity_(0)
        {
        }

        explicit vector( size_t n, const T& value = T())
        {
            data_ = new T[n];
			size_ = n;
            for (size_t i = 0; i < n; i++)
            {
                data_[0] = value;
            }
			capacity_ = n;
        }

        vector<T>& operator=(const vector<T>& rhs)
        {

			int len = rhs.capacity();
			data_ = new T[len]();
			for (size_t i = 0; i < rhs.size(); i++)
				data_[i] = rhs.data_[i];
			capacity_ = rhs.capacity();
			size_ = rhs.size();
        }
		
        //dtor
        ~vector()
        {
            if (data_!=NULL)
            {
                delete [] data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }

        // set & get
		T& operator[](size_t index){
			assert(index < size());
			return data_[index];
		}
		size_t  capacity() const
		{
			return capacity_;
		}
		void empty()
		{
			return size()== 0;
		}
        // set
        void push_back(const T& element);
        void pop_back();
        size_t resize(size_t newsize,const T &x);
 
        size_t reserve(size_t size);
        void clear();
        


    private:
        T*      data_;
        size_t  size_;
		size_t capacity_;
    };
	template<class T>
	void vector<T>::push_back(const T&element)
	{
		int newlen = 0;
		if (size() == capacity_)
		{
			if (size() == 0)
			{
				newlen = DEFAULT_LEN;
			}
			else
				newlen= size_ * 2;
			reserve(newlen);
			capacity_ = newlen;
			
		}
		data_[size_] = element;
		size_++;
			
	}
	template<class T>
	void vector<T>::pop_back()
	{
		size_--;
	}
	template<class T>
	size_t vector<T>::resize(size_t newsize, const T &x)
	{
		if (newsize < size())
		{
			size_ = newsize;

		}
		else
			for (size_t i = size(); i < newsize; i++)
				push_back(x);
		return newsize;

	}

	template<class T>
	size_t vector<T>::reserve(size_t n)
	{
		if (capacity() < n)
		{
			T *tmp = new T[n]();
			for (size_t i=0; i < size_; i++)
				tmp[i] = data_[i];
			T *temp = data_;
			data_ = tmp;
			tmp = temp;
			delete tmp;
			capacity_ = n;
		}
		return n;
	}
 	template<class T>
	void  vector<T>::clear()
	{
		if (data_ != NULL)
			delete []  data_;
		size_ = 0;
		capacity_ = 0;
	}
}

#endif


