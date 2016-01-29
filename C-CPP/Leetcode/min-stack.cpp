class MinStack {
private:
    stack<int> curstack;
    stack<int> minstack;
public:
    
    void push(int x) {
        curstack.push(x);
        if (minstack.empty() || minstack.top() >= x) {
            minstack.push(x);
        }
    }

    void pop() {
        if (!curstack.empty()) {
            int cur = curstack.top();
            curstack.pop();
            if (cur == minstack.top()) {
                minstack.pop();
            }
        }
    }

    int top() {
        return curstack.top();
    }

    int getMin() {
        if (!minstack.empty()) {
            return minstack.top();
        } else {
            return INT_MIN;
        }
    }
};