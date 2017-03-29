#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

namespace qh
{
	template<typename T>
	class vector {
	public:
		//ctor
		vector():data_(NULL), size_(0), capacity_(0) {}

		explicit vector(size_t n, const T &value = T() )
		{
			data_ = new T[n];
			for (size_t i = 0; i < n; ++i)
			{
				data_[i] = value;
			}
			size_ = n;
			capacity_ = n;
		}
		
		vector<T> &operator=(const vector<T> &rhs)
		{
			if (data_ == rhs.data_ && size_ == rhs.size_ && capacity_ == rhs.capacity_)
			{
				return *this;
			}
			else
			{
				delete [] data_;
				data_ = new T[rhs.capacity_];
				assert(data_ != NULL);
				for ( size_t i = 0; i < size_ ; ++i)
				{
					data_[i] = rhs.data_[i];
				}
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				return *this;
			}
		}
		
		//dtor
		~vector()
		{
			if (data_)
			{
				delete [] data_;
				data_ = NULL;
			}
		}

		//get
		size_t size() const
		{
			return size_;
		}

		size_t capacity() const
		{
			return capacity_;
		}

		T *data() const
		{
			return data_;
		}

		//set & get
		T &operator[](size_t index);

		//set
		void push_back(const T& element);
		void pop_back();
		void resize(size_t n);
		void reserve();
		void clear();
		bool empty();

	private:
		T *data_;
		size_t size_;
		size_t capacity_;
	};
}

#endif


