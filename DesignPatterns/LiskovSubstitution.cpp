#include "LiskovSubstitution.h"
#include <iostream>


/* ----------- Liskov Substition Principle ----------- */
/*
	Sub-types should be immediately substituable for their base-types. Meaning that for any implementation (function) that uses
	a base class, any derived class should be able to be substituted for the base class without breaking the intended functionality
	of the function. 
	
	In the example below, we implement a Rectangle Class and then a "process" function that takes a Rectangle reference. This represents
	some kind of processing funcionality, in this cass it gets the width of the rectangle, then sets the height, then prints the expected 
	area vs the actual area. Since, area is calculated as width times height in the Rectangle class, and the process function returns the 
	set height times the "gett'ed" width, we would expect them to return the same value. 
	However, if we create a Square class that, due to the nature of squares, overrides the setter functions of the Rectangle class, to force
	the height and width to be the same value when they are set, it will break the intended functionality of Process. 

	To avoid this, we could simply not create a derived square class, and instead handle all square creation through a Factory Class
	called RectangleFactory. Here we simply have a create_rectangle method that takes a height and width, and a create_square method that
	takes a single int to be used for both height and width. 

	However, this is the equivalent of simply removing the overidden setHeight and setWidth methods in the square class. So, now we've got a 
	Square class that acts like a rectangle class. Once it's been created we can set different height's and widths without issue. 



	
*/

class Rectangle
{
protected:
	int m_width, m_height; 
public: 
	Rectangle(int width, int height) : m_width(width), m_height(height) {}
	int getWidth() const { return m_width; }
	virtual void setWidth(int width) { m_width = width; }
	int getHeight() const { return m_height;}
	virtual void setHeight(int height) { m_height = height; }
	int area() const { return m_width * m_height; }
};

class Square : public Rectangle
{
public: 
	Square(int size) : Rectangle(size, size) {}
	void setWidth(int width) override {
		this->m_width = this->m_height = width; 
	}
	void setHeight(int height) override {
		this->m_width = this->m_height = height;
	}
};

struct RectangleFactory
{
	static Rectangle create_rectangle(int w, int h)
	{
		return Rectangle(w, h); 
	}; 
	static Rectangle create_square(int size)
	{
		return Rectangle(size, size); 
	};
};


void process(Rectangle& r) 
{
	int w = r.getWidth();
	r.setHeight(10);
	std::cout << "expected area = " << (w * 10)
		<< ", got " << r.area() << std::endl; 

}

void LiskovSubstitution::run() 
{
	std::cout << "3. LISKOV SUBSTITUTION" << std::endl;
	Rectangle rectangle{ 3,4 }; 
	process(rectangle);

	Square sq{ 5 }; 
	process(sq); 

	Rectangle square = RectangleFactory::create_square(5); 
	process(square); 
	std::cout << std::endl; 
}