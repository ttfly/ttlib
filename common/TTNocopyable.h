#ifndef __NOCOPYABLE_H__
#define __NOCOPYABLE_H__

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}
private:
	Noncopyable(const Noncopyable&);
	const Noncopyable& operator=(const Noncopyable&);
};
#endif