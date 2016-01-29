class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        stkin.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        if (stkout.empty()) {
            while(!stkin.empty()) {
                int tmp = stkin.top();
                stkin.pop();
                stkout.push(tmp);
            }
        }
        stkout.pop();
        
    }

    // Get the front element.
    int peek(void) {
        if (stkout.empty()) {
            while(!stkin.empty()) {
                int tmp = stkin.top();
                stkin.pop();
                stkout.push(tmp);
            }
        }
        return stkout.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return (stkin.empty() && stkout.empty());
    }
private:
    stack<int> stkin;
    stack<int> stkout;
};