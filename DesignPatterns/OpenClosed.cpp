#include "OpenClosed.h"
#include <iostream>
#include <vector>
#include <string>

/* ----------- Open-Closed Principle ----------- */
/*
	The Open-Closed Principle states that your software module should be open to extension, but closed to modification. This means 
	when you need to change functionality of a software module, you can do so by extending it through inheritance/polymorphism and 
	not by changing existing functions/code. 

	In the example below, we've created a Product class with name, color, and size attributes that we need to be able to filter by 
	Color and Size. To filter our Products we create a ProductFilter class with a naive implementation function called byColor_naive().
	This naive function works, however, if we then needed to filter by size, we would have to create an almost identical function to 
	do so, and then if we needed to filter by size and color, we again would need to create a new function that does both. 

	For a better implementation we're going to use the "Specification" pattern, which is an "Enterprise" pattern. 
	We define interfaces for Specification and Filter. Specification requires an isSatisfied method that determines if some criteria is satisfied
	and Filter requires a vector of items and a Specification. With these we many kinds of filters and specifications. 
	Our implementation of Filter (BetterFilter) simply goes through each Product in its item list and checks that its Specification is satisfied. 
	Now we can create any type of Specification we want, and pass that into the filter. All items that satisfy the spec are returned. 

	In addition, we've created the "AndSpecification" which implements the Specification interface (ie, it is a specification as well). With this we can 
	take two specifications and only accept items that satisfy both. 
*/


enum class Color { RED, GREEN, BLUE };
enum class Size { SMALL, MEDIUM, LARGE };

struct Product {
	std::string name; 
	Color color; 
	Size size; 
};

// Naive Filter Implementation 
struct NaiveFilter {
	std::vector<Product*> byColor_naive(std::vector<Product*> itemsToFilter, Color color)
	{
		std::vector<Product*> result; 
		for (auto& item : itemsToFilter)
		{
			if (item->color == color) 
			{
				result.push_back(item);
			}
		}
		return result;
	}
};

// Better Filter Implementation 
template <typename T> struct Specification
{
	// Defines the interface that needs to be implemented for any kind of specification
	//Simply tries to check that some item satisfies a particular specification
	virtual bool isSatisfied(T* item) = 0; 
};

template <typename T> struct Filter
{
	// Defines the interface that needs to be implemented by any kind of filter
	virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0; 
};

struct BetterFilter : Filter<Product> {
	std::vector<Product*> filter(std::vector<Product*> items, Specification<Product> &spec) override
	{
		std::vector<Product*> result;
		for (auto& item : items) 
		{
			if (spec.isSatisfied(item)) {
				result.push_back(item); 
			}
		}
		return result; 
	}
};

struct ColorSpecification : Specification<Product> {
	Color m_color; 
	ColorSpecification(Color color) : m_color(color) {}
	bool isSatisfied(Product* item) override
	{
		return item->color == m_color;
	}
};

struct SizeSpecification : Specification<Product> {
	Size m_size; 
	SizeSpecification(Size size) : m_size(size) {}
	bool isSatisfied(Product* item) override 
	{
		return item->size == m_size;
	}
};

template <typename T> struct AndSpecification : Specification<T>
{
	Specification<T>& m_first; 
	Specification<T>& m_second; 
	AndSpecification(Specification<T>& first, Specification<T>& second) : m_first(first), m_second(second) {}
	bool isSatisfied(T* item) override
	{
		return m_first.isSatisfied(item) && m_second.isSatisfied(item); 
	}
};


void OpenClosed::run() 
{
	std::cout << "2. OPEN-CLOSED" << std::endl;
	Product apple{ "Apple", Color::GREEN, Size::SMALL }; 
	Product tree{ "Tree", Color::GREEN, Size::LARGE };
	Product house{ "House", Color::BLUE, Size::LARGE };
	std::vector<Product*> items{ &apple, &tree, &house };
	
	//NaiveFilter productFilter;
	//auto greenThings = productFilter.byColor_naive(items, Color::GREEN);
	//for (auto& item : greenThings) {
	//	std::cout << item->name << " is green" << std::endl; 
	//}

	BetterFilter betterFilter; 
	ColorSpecification greenSpec(Color::GREEN); 
	auto greenThings = betterFilter.filter(items, greenSpec); 
	for (auto& item : greenThings) 
	{
		std::cout << item->name << " is green" << std::endl; 
	}
	SizeSpecification largeSpec(Size::LARGE);
	auto largeThings = betterFilter.filter(items, largeSpec); 
	for (auto& item : largeThings) {
		std::cout << item->name << " is large" << std::endl;
	}
	AndSpecification<Product> greenAndLargeSpec(greenSpec, largeSpec);


	auto largeGreenThings = betterFilter.filter(items, greenAndLargeSpec);
	for (auto& item : largeGreenThings) {
		std::cout << item->name << " is large and green" << std::endl; 
	}



	std::cout << std::endl; 

}