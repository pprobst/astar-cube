#include "libs.hpp"

/**
 * PQueue
 *
 * C++ already offers the priority_queue class, but it returns the maximum element first.
 * As we need to get the minimum element first, we're making some changes to the priority_queue.
 */

template<typename T, typename priority_t>
struct PQueue {
    typedef pair<priority_t, T> qelement;

    priority_queue<qelement, vector<qelement>, greater<qelement>> elements;

    inline void add(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    inline bool empty() const {
        return elements.empty();
    }

    T get() {
        T elem = elements.top().second;
        elements.pop();
        return elem;
    }
};
