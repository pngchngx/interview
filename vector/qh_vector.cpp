#include <assert.h>
#include "qh_vector.h"

namespace qh
{
	// set & get
	template<typename T>
	T& vector<T>::operator[](size_t index)
	{
		assert(index < size_);
		return *(data_ + index);
	}

	// set
	template<typename T>
	void vector<T>::push_back(const T& element)
	{
		if (size_ == capacity_)
		{
			reserve();
		}
		data_[size_] = element;
		++size_;
	}

	template<typename T>
	void vector<T>::pop_back()
	{
		data[size_-1].~T();
		--size_;
	}

	template<typename T>
	void vector<T>::resize(size_t n)
	{
		T *new_data_ = new T[n];
		assert(new_data_ != NULL);
		if (n <= size_)
		{
			for (size_t i = 0; i < n; ++i)
				new_data_[i] = data_[i];
			delete[] data_;
		}
		else
		{
			for (size_t i = 0; i < size_; ++i)
				new_data_[i] = data_[i];
			delete[] data_;
		}
		size_ = n;
		capacity_ = n;
	}

	template<typename T>
	void vector<T>::reserve()
	{
		T *new_data_ = new T[2*capacity_+1];
		assert(new_data_ != NULL);
		for (size_t i = 0; i < size_; ++i)
		{
			new_data_[i] = data_[i];
		}
		delete[] data_;
		data_ = new_data_;
		capacity_ = 2*capacity_+1;
	}

	template<typename T>
	void vector<T>::clear()
	{
		size_ = 0;
	}

	template<typename T>
	bool vector<T>::empty()
	{
		return size_ == 0 ? true : false;
	}
		
}
