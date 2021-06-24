#include <iostream>
#include <string>
#include <sstream>

template<class type>
struct element                          
{
	type el;                          
	element<type>* Next = nullptr;              
};

template<class type>
class Stack                            
{
	element<type>* First;                 
public:
	Stack() : First(nullptr) {};   
	~Stack();
	template <typename type>friend std::ostream& operator<<(std::ostream& stream, const Stack<type>& mylist);
	template <typename type>friend std::istream& operator>>(std::istream& stream, Stack& list);
	void push(type input);
	const type pop();
	void print();
};

template<class type>
Stack<type>::~Stack()
{
	if (First != nullptr) {
		element<type>* temp = First;
		element<type>* temp1 = temp->Next;
		while (temp1 != nullptr) {
			delete temp;
			temp = temp1;
			temp1 = temp->Next;
		}
		delete temp;
	}
}

template<class type>
void Stack<type>::push(type input)
{
	element<type>* temp = new element<type>;  
	temp->el = input;                         

	if (First != nullptr)                   
	{
		temp->Next = First;                
		First = temp;                    
	}
	else 
	{
		temp->Next = nullptr;               
		First = temp;              
	}
}

template<class type>
const type Stack<type>::pop()
{
	if (First) {
		element<type>* temp = First->Next;
		type buf = First->el;
		delete First;
		First = temp;
		return buf;
	}
	return 0;
}

template<class type>
std::ostream& operator<<(std::ostream& stream, const Stack<type>& my_stack) {

	size_t counter = 0;
	if (my_stack.First != nullptr) {
		element<type>* temp = my_stack.First;
		while (temp != nullptr)
		{
			stream << temp->el << std::endl;
			temp = temp->Next;
			++counter;
		}
	}
	stream << "in stack " << counter << " elements" << std::endl;
	return stream;

}


template<class type>
const type mpow(const type& a, const type& b) {
	type buf = a;
	for (size_t i = 1; i < b; i++)
		buf *= a;
	return buf;
}

template<class type>
std::istream& operator>>(std::istream& stream, Stack<type>& my_stack) {
	std::string input;
	type buf;
	stream >> buf;
	my_stack.push(buf);
	std::getline(std::cin, input);

	std::stringstream ss;
	ss << input;
	while (!ss.eof())
	{
		ss >> buf;
		ss.ignore(1);
		my_stack.push(buf);
	}

	return stream;
}

template<class type>
void Calculate(Stack<type>& stack, char op) {
	type a, b;
	a = stack.pop();
	b = stack.pop();
	if (op == '+')
		stack.push(a + b);
	else if (op == '-')
		stack.push(a - b);
	else if (op == '*')
		stack.push(a * b);
	else if (op == '/')
		stack.push(a / b);
	else if (op == '^')
		stack.push(mpow(a, b));

}


template<class type>
void Calculate(Stack<type>& stack) {
	std::string input;
	std::getline(std::cin, input);
	std::stringstream ss;
	ss << input;
	std::string buf;
	while (!ss.eof())
	{
		ss >> buf;
		if (buf == "+" || buf == "-" || buf == "*" || buf == "/" || buf == "^")
			Calculate(stack, buf[0]);
		else
			stack.push(stoi(buf));
		ss.ignore(1);
	}
}


int main() {
	Stack<int> stack;
	Calculate(stack);
	std::cout << stack << std::endl;

	return 0;
}
