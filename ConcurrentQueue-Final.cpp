#include <cmath>
#include <functional>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>

template<typename T, uint64_t SIZE = 4096, uint64_t MAX_SPIN_ON_BUSY = 40000000>
class ConcurrentQueue {
private:
    static constexpr unsigned Log2(unsigned n, unsigned p = 0) {
        return (n <= 1) ? p : Log2(n / 2, p + 1);
    }

    static constexpr uint64_t closestExponentOf2(uint64_t x) {
        return (1UL << ((uint64_t)(Log2(SIZE - 1)) + 1));
    }

    static constexpr uint64_t mRingModMask = closestExponentOf2(SIZE) - 1;
    static constexpr uint64_t mSize = closestExponentOf2(SIZE);

    static const T mEmpty;

    T mMem[mSize];
    std::mutex mLock;
    uint64_t mReadPtr = 0;
    uint64_t mWritePtr = 0;

public:


    const T &  pop() {

        if (!peek()) {
            return mEmpty;
        }

        std::lock_guard<std::mutex> lock(mLock);

        //Assuming only one consumer
        //This check is useless as it has been already checked before acquiring muxtex 
        if (!peek()) {
            return mEmpty;
        }

 /*Should be :T ret = mMem[mReadPtr & mRingModMask]; To avoid undefined behavoir 
 
 -I believe this was the bug in the code, after correcting it. I ran the test below for several minutes and it was running normal
 -To find this bug, I tried to fill the  queue with  integers and it was running normal 
 -Then I tried with int* and it gave segmentation fault
 -I deduced that the error comes when trying to use pointers and allocate memory
 
Ex:  If T = object*  , then we will have ret type  : object*   ; which is a pointer and then we return this pointer that we will be 
able to derefrence to run the task
  
 */
        T& ret = mMem[mReadPtr & mRingModMask];

        mReadPtr++;
        return ret;
    }

    //Name is misleading and needs to be changed
    //Suggestions : checkNotEmpty
    bool peek() const {
        return (mWritePtr != mReadPtr);
    }

    //Move to private , no need for this function to be public
    uint64_t getCount() const {
        return mWritePtr > mReadPtr ? mWritePtr - mReadPtr : mReadPtr - mWritePtr;
    }

    //Same here , Move to private , no need for this function to be public
    // Should be declared const as it is not allowed to modify any of the class parameters
    bool busyWaitForPush() {
        uint64_t start = 0;
        while (getCount() == mSize) {
            if (start++ > MAX_SPIN_ON_BUSY) {
                return false;
            }
        }
        return true;
    }

    void push(const T& pItem) {
        if (!busyWaitForPush()) {
            throw std::runtime_error("Concurrent queue full cannot write to it!");
        }

        std::lock_guard<std::mutex> lock(mLock);
        mMem[mWritePtr & mRingModMask] = pItem;
        mWritePtr++;
    }

    void push(T&& pItem) {
        if (!busyWaitForPush()) {
            throw std::runtime_error("Concurrent queue full cannot write to it!");
        }

        std::lock_guard<std::mutex> lock(mLock);
        mMem[mWritePtr & mRingModMask] = std::move(pItem);
        mWritePtr++;
    }
};

template<typename T, uint64_t SIZE, uint64_t MAX_SPIN_ON_BUSY>
const T ConcurrentQueue<T, SIZE, MAX_SPIN_ON_BUSY>::mEmpty = T{ };

int main(int, char**) {
    using Functor = std::function<void()>;

    ConcurrentQueue<Functor*> queue;

    std::thread consumer([&] {
        while (true) {
            if (queue.peek()) {
                auto task = queue.pop();
                (*task)();
                delete task;
            }
        }
        });

    std::thread producer([&] {
        uint64_t counter = 0;
        while (true) {
            auto taskId = counter++;
            auto newTask = new Functor([=] {
                std::cout << "Running task " << taskId << std::endl << std::flush;
                });
            queue.push(newTask);
        }
        });

    consumer.join();
    producer.join();
    return 0;
}
