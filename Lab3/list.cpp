#include <iostream>
#include <string>
#include <sstream>


struct list                             //Структура, являющаяся звеном списка
{
	std::string str;                             //Значение x будет передаваться в список
	list *Next = nullptr;
	list *Prev = nullptr;                 //Указатели на адреса следующего и предыдущего элементов списка
};

class List                              //Создаем тип данных Список
{
	list *Head, *Tail;                 //Указатели на адреса начала списка и его конца
	void add(std::string input);
public:
	List() :Head(NULL), Tail(NULL) {};    //Инициализируем адреса как пустыe
	friend std::ostream& operator<<(std::ostream& stream, const List& mylist);
	friend std::istream& operator>>(std::istream& stream, List& list);
	void show();
};

void List::show()
{
	list *temp = Head;                       //Временно указываем на адрес первого элемента
	while (temp != NULL)              //Пока не встретим пустое значение
	{
		if (temp->str.size() % 2 != 0) {
			temp->str.erase(temp->str.begin());
			temp->str.erase(temp->str.end() - 1);
			std::cout << temp->str << " ";        //Выводим каждое считанное значение на экран

		}
		temp = temp->Next;             //Смена адреса на адрес следующего элемента
	}
}


void List::add(std::string input)
{
	list* temp = new list;               //Выделение памяти под новый элемент структуры
	temp->Next = NULL;                   //Указываем, что изначально по следующему адресу пусто
	temp->str = input;                         //Записываем значение в структуру

	if (Head != NULL)                    //Если список не пуст
	{
		temp->Prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
		Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
		Tail = temp;                     //Меняем адрес хвоста
	}
	else //Если список пустой
	{
		temp->Prev = NULL;               //Предыдущий элемент указывает в пустоту
		Head = Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
	}
}

std::ostream& operator<<(std::ostream& stream, const List& mylist) {

	if (mylist.Head != NULL) {
		list* temp = mylist.Head;
		while (temp != nullptr)
		{
			stream << temp->str << " ";
			temp = temp->Next;
		}
	}
	return stream;

}

std::istream& operator>>(std::istream& stream, List& list) {
	std::string input;
	std::getline(std::cin, input);

		std::stringstream ss;
		ss << input;
		std::string buf;
		while (!ss.eof())
		{
			ss >> buf;
			ss.ignore(1);
			list.add(buf);
		}
	
	return stream;
}

class list_with_char {
	std::string* str;
	size_t size;
public:
	list_with_char() { str = NULL; size = 0; };
	~list_with_char() { delete[] str; }
	friend std::ostream& operator<<(std::ostream& stream, const list_with_char& list);
	friend std::istream& operator>>(std::istream& stream, list_with_char& list);
	void show();
	void resize(size_t new_size);
};


std::ostream& operator<<(std::ostream& stream, const list_with_char& list)
{
	if (list.str != NULL) {
		for (size_t i = 0; i < list.size; ++i) {
			stream << list.str[i] << " ";
		}
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, list_with_char& list)
{
	std::string input;
	std::getline(std::cin, input);
	std::string buf;

	std::stringstream ss;
	ss << input;

	ss >> list.size;


	list.str = new std::string[list.size];
	for (size_t i = 0; i < list.size; ++i) {
		if (!ss.eof())
		{
			ss >> buf;
			ss.ignore(1);
			list.str[i] = buf;
		}
		else
			break;
	}
	return stream;
}
void list_with_char::show()
{
	if (str != NULL) {
		for (size_t i = 0; i < size; ++i) {
			if (str[i].size() % 2 != 0) {
				str[i].erase(str[i].begin());
				str[i].erase(str[i].end() - 1);
				std::cout << str[i] << " ";
			}
		}
	}
}

void list_with_char::resize(size_t new_size)
{
	std::string* newstr = new std::string[new_size];
	if (size < new_size) {
		for (size_t i = 0; i < size; i++)
		{
			newstr[i] = str[i];
		}
	}
	else {
		for (size_t i = 0; i < new_size; i++)
		{
			newstr[i] = str[i];
		}
	}
	delete[] str;
	str = newstr;
	size = new_size;
}


int main()
{
#if 0
	List mylist;
	std::cin >> mylist;
	std::cout << std::endl;
	std::cout << mylist << std::endl;
	mylist.show();
	std::cout << std::endl;
	std::cout << "That`s all, children" << std::endl;
#endif
	//list_with_char mylist;
	//std::cin >> mylist;
	//std::cout << std::endl;
	//std::cout << mylist << std::endl;
	//mylist.show();
	//size_t newsize;
	//std::cout << std::endl;
	//std::cin >> newsize;
	//mylist.resize(newsize);
	//std::cout << mylist << std::endl;
	std::string buf = "fjeifjeijfie";
	std::cout << *buf.begin();
	std::cout << *(buf.end() - 1);
	return 0;
}

