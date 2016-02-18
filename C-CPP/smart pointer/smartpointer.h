template <class T>
class smartpointer
{
private:
	T *_ptr;
public:
	smartpointer(T *p) : _ptr(p)  //构造函数
	{
	}
	T& operator *()        //重载*操作符
	{
		return *_ptr;
	}
	T* operator ->()       //重载->操作符
	{
		return _ptr;
	}
	~smartpointer()        //析构函数
	{
		delete _ptr;
	}
};