#pragma once
#include <list>
#include <type_traits>

typedef unsigned int Hash;

template<class T, int SIZE>
class HashMap
{
public:

	HashMap()
	{
		// assume SIZE is a power of two
		mMask = SIZE - 1;
	}

	void InsertNoCheck(T& data)
	{
		int index = Translate(data->mHash);
		mBuckets[index].push_back(data);
	}

	T Find(Hash hash)
	{
		int index = Translate(hash);
		std::list<T>& bucket = mBuckets[index];

		for (auto& value : bucket)
		{
			if (value->mHash == hash)
			{
				return value;
			}
		}

		return nullptr;
	}

	const T Find(Hash hash) const
	{
		int index = Translate(hash);
		const std::list<T>& bucket = mBuckets[index];

		for (auto& value : bucket)
		{
			if (value->mHash == hash)
			{
				return value;
			}
		}

		return nullptr;
	}

	void Delete(T data)
	{
		Hash hash = data->mHash;
		int index = Translate(hash);
		std::list<T>& bucket = mBuckets[index];
		typename std::list<T>::iterator it = bucket.begin();

		for (auto& value : bucket)
		{
			if (value->mHash == hash)
			{
				if (std::_Is_pointer<T>())
				{
					// Checking if T is a pointer before deleting the value - To Prevent Errors
					delete data; 
				}
				bucket.erase(it);
				return;
			}
			++it;
		}
	}

	void ClearData()
	{
		for (std::list<T>& bucket : mBuckets)
		{
			// Deleting all the values and clearing the buckets
			for (auto& value : bucket)
			{
				delete value;
			}

			bucket.clear();
		}
	}

private:

	int Translate(Hash hash) const
	{
		return (hash & mMask);
	}

private:

	Hash mMask;

	// you should use your own linked list class for full marks
	std::list<T> mBuckets[SIZE];
};