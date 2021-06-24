#include <iostream>
#include <string>
#include <sstream>

template<class type>
struct element                             
{
	type el;                             
	element<type>* Next = nullptr;
	element<type>* Prev = nullptr;                 
};

template<class type>
class Queue                              
{
	element<type> *First, *Last;                 
public:
	Queue() :First(nullptr), Last(nullptr) {};   
	~Queue();
	template <typename type>friend std::ostream& operator<<(std::ostream& stream, const Queue<type>& my_queue);
	template <typename type>friend std::istream& operator>>(std::istream& stream, Queue& my_queue);
	void push(type input);
	const type pop();
};

template<class type>
Queue<type>::~Queue()
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
void Queue<type>::push(type input)
{
	element<type>* temp = new element<type>;               
	temp->Prev = nullptr;                  
	temp->el = input;                       

	if (First != nullptr)                   
	{
		temp->Next = First;               
		First->Prev = temp;               
		First = temp;                     
	}
	else 
	{
		temp->Next = nullptr;               
		First = Last = temp;              
	}
}

template<class type>
const type Queue<type>::pop()
{
	if (Last) {
		element<type>* temp = Last->Prev;
		type buf = Last->el;
		delete Last;
		Last = temp;
		if (Last)
			Last->Next = nullptr;
		else {
			First = Last;
			std::cout << "Queue is empty!" << std::endl;
		}
		return buf;
	}
	return 0;
}

template<class type>
std::ostream& operator<<(std::ostream& stream, const Queue<type>& my_queue) {

	size_t counter = 0;
	if (my_queue.First != nullptr) {
		element<type>* temp = my_queue.First;
		while (temp != nullptr)
		{
			stream << temp->el << std::endl;
			temp = temp->Next;
			++counter;
		}
	}
	stream << "in queue " << counter << " elements" << std::endl;
	return stream;

}


template<class type>
std::istream& operator>>(std::istream& stream, Queue<type>& my_queue) {
	std::string input;
	std::getline(std::cin, input);

	std::stringstream ss;
	ss << input;
	type buf;
	while (!ss.eof())
	{
		ss >> buf;
		ss.ignore(1);
		my_queue.push(buf);
	}

	return stream;
}



//Cicular queue

template<class type>
class Cicular
{
	type* data;
	size_t size;
	size_t tail = 0;
	size_t head = 0;
public:
	Cicular() { size = 0; data = nullptr; }
	Cicular(size_t in_size) { size = in_size; data = new type[size]; }
	~Cicular() { size = 0; delete[] data; }
	void En(const type& input);
	void De() { if (head || tail) { data[head] = NULL; head = (head == size - 1) ? 0 : ++head; } }
	template<typename type> friend std::ostream& operator<<(std::ostream& stream, const Cicular<type>& queue);
	template<typename type> friend std::istream& operator>>(std::istream& stream, Cicular<type>& queue);
};
template<class type>
void Cicular<type>::En(const type& input)
{
	int new_tail = static_cast<int>(tail);
	new_tail -= 2;
	new_tail = (new_tail < 0) ? size + new_tail : new_tail;
	
	
	if (head != 0) {
		tail = (tail == size) ? 0 : tail;
	}
	else
		tail = (tail == size) ? static_cast<size_t>(new_tail) : tail;
	if(head != 0 && tail != 0)
		tail = (head != (tail) % (size + 1)) ? tail : static_cast<size_t>(new_tail);
	
	data[tail] = input;
	/*if (head != (tail + 1) % (size + 1))
		tail = (tail == size) ? 0 : ++tail;
	else
		--tail;*/
	tail = (tail == size) ? 0 : ++tail;
}
template<typename type>
std::ostream& operator<<(std::ostream& stream, const Cicular<type>& queue)
{
	stream << "Head: " << queue.head << std::endl;
	stream << "Tail: " << queue.tail << std::endl;
	for (size_t i = 0; i < queue.size; ++i)
	{
		//TODO èñïðàâèòü äóáëèðîâàíèå êîäà
		if (queue.head < queue.tail) {
			if ((i >= queue.head) && (i < queue.tail))
				stream << "[" << queue.data[i] << "] ";
			else
				stream << "[] ";
		}
		else
			if ((i >= queue.head) || (i < queue.tail))
				stream << "[" << queue.data[i] << "] ";
			else
				stream << "[] ";
	}
	return stream;
}

template<typename type>
std::istream& operator>>(std::istream& stream, Cicular<type>& queue)
{
	std::string input;
	std::getline(std::cin, input);
	type buf;

	std::stringstream ss;
	ss << input;

	ss >> queue.size;

	queue.data = new type[queue.size + 1];
	while (!ss.eof())
	{
		ss >> buf;
		ss.ignore(1);
		queue.En(buf);
	}
	return stream;
}






int main() {
#if 0
	Queue<int> queue;
	std::cin >> queue;
	std::cout << queue;
	std::cout << "Pop item: " << queue.pop() << std::endl;
	std::cout << queue;
	std::cout << "Pop item: " << queue.pop() << std::endl;
	std::cout << queue;
	std::cout << "Pop item: " << queue.pop() << std::endl;
	std::cout << queue;

#endif
#if 1
	Cicular<int> queue;
	std::cin >> queue;
	std::cout << queue << std::endl;
	queue.De();
	std::cout << queue << std::endl;
	queue.De();
	std::cout << queue << std::endl;
	queue.En(89);
	std::cout << queue << std::endl;
	queue.En(75);
	std::cout << queue << std::endl;
	queue.En(75);
	std::cout << queue << std::endl;
#endif
	return 0;
}

