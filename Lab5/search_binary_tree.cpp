#include <iostream>
#include <queue>
#include <sstream>
#include <iomanip> 
#include <string>

template<typename type>
struct element
{
	type el;
	element<type>* left = nullptr; 
	element<type>* right = nullptr;
	element<type>* parent = nullptr;
};


template<typename type>
class SearchBinaryTree
{	
	size_t t_size = 0;
	element<type>* kernel;
public:
	const element<type>* begin() const { return kernel; }
	SearchBinaryTree() :kernel(NULL){};
	~SearchBinaryTree();
	void add(type el);
	template<typename type> friend std::ostream& operator<<(std::ostream& stream, const SearchBinaryTree<type>& my_tree);
	
	template<typename type> friend std::istream& operator>>(std::istream& stream, SearchBinaryTree<type>& my_tree);

	size_t size() { return t_size; }

	bool find(type el);
	void Infix(const element<type>* p) const;
	void Postorder(const element<type>* p) const;
};


template<typename type>
SearchBinaryTree<type>::~SearchBinaryTree()
{
	std::queue<element<type>*> T; //ìíîæåñòâî âåðøèí
	T.push(kernel);
	while (!T.empty())
	{
		if (T.front()->left) { T.push(T.front()->left); }
		if (T.front()->right) { T.push(T.front()->right); }
		delete T.front();
		T.pop();
	}
}

template<typename type>
void SearchBinaryTree<type>::add(type el)
{
	if (kernel) {
		element<type>* temp = kernel;

		element<type>* new_el = new element<type>;
		new_el->el = el;

		while (temp)
		{
			if (temp->el > el) {
				if (!temp->left) { temp->left = new_el; break; }
				temp = temp->left;
			}
			else if (temp->el <= el) {
				if (!temp->right) {  temp->right = new_el; break; }
				temp = temp->right;
			}
			//else break; //åñëè ìû õîòèì äåðåâî áåç ïîâòîðåíèé 
		}
		++t_size;
		new_el->parent = temp;
	}
	else {
		++t_size;
		kernel = new element<type>;
		kernel->el = el;
	}
}

template<typename type>
bool SearchBinaryTree<type>::find(type el)
{

	std::queue<element<type>*> T; //ìíîæåñòâî âåðøèí
	T.push(kernel);
	element<type>* temp;
	bool del = false;

	while (!T.empty())
	{
		if (T.front()->left) { T.push(T.front()->left); }
		if (T.front()->right) { T.push(T.front()->right);}
		temp = T.front();
		if ((temp->el == el) && !del) del = true;
		else if (temp->el == el && del) {
			if (!(temp->left || temp->right)) {
				if (temp->parent->left == temp) temp->parent->left = nullptr;
				if (temp->parent->right == temp) temp->parent->right = nullptr;
			}
			else if (temp->left && !temp->right) {
				if (temp->parent->left == temp) { temp->parent->left = temp->left; temp->left->parent = temp->parent; }
				if (temp->parent->right == temp) { temp->parent->right = temp->left;  temp->left->parent = temp->parent; }
			}
			else if (!temp->left && temp->right) {
				if (temp->parent->left == temp) { temp->parent->left = temp->right; temp->right->parent = temp->parent; }
				if (temp->parent->right == temp) { temp->parent->right = temp->right; temp->right->parent = temp->parent; }
			}
			else {

				element<type>* last_in_r = temp->right; //ïîñëåäíèé ëåâûé ëèñò, íà÷èíàÿ îò ïðàâîãî åëåìåíòà òåìïà

				while (last_in_r->left)
				{
					last_in_r = last_in_r->left;
				}

				if (temp->parent->left == temp) temp->parent->left = last_in_r;
				if (temp->parent->right == temp) temp->parent->right = last_in_r;

				last_in_r->parent->left = last_in_r->right;
				if (last_in_r->right) last_in_r->right->parent = last_in_r->parent;

				last_in_r->left = temp->left;
				last_in_r->right = temp->right;

				temp->left->parent = last_in_r;
				temp->right->parent = last_in_r;

				last_in_r->parent = temp->parent;

			}

			delete temp;
			--t_size;

		}

		T.pop();
	}
	return false;
}

template<typename type>
void SearchBinaryTree<type>::Infix(const element<type>* p) const
{
	if (p->left != NULL) {
		Infix(p->left);
	}
	std::cout << p->el << " " << std::endl;
	if (p->right != NULL) {
		Infix(p->right);
	}
}

template<typename type>
void SearchBinaryTree<type>::Postorder(const element<type>* p) const
{
	if (p->left != NULL) {
		Infix(p->left);
	}
	if (p->right != NULL) {
		Infix(p->right);
	}
	std::cout << p->el << " " << std::endl;
}

template<typename type>
std::ostream& operator<<(std::ostream& stream, const SearchBinaryTree<type>& my_tree)
{
	//stream << my_tree.kernel->el << std::endl;
	//stream << my_tree.kernel->left->el << "	" << my_tree.kernel->right->el << std::endl;

	std::queue<element<type>*> T; //ìíîæåñòâî âåðøèí
	T.push(my_tree.kernel);

	std::vector<char> l_or_r;
	while (!T.empty())
	{
		size_t t_size = T.size();
		stream << std::setw(21 - t_size);
		//stream << " ";
		for (size_t i = 0; i < t_size; ++i)
		{
			if (T.front()->left) { T.push(T.front()->left); l_or_r.push_back('/'); }
			if (T.front()->right) { T.push(T.front()->right); l_or_r.push_back('\\'); }
			if (!((T.front()->left) || (T.front()->right))) { l_or_r.push_back(' '); }
			stream << T.front()->el << "   ";
			T.pop();
		}
		stream <<  std::endl;
		stream << std::setw(20 - t_size);
		for (const auto& a : l_or_r)
		{
			stream << a << "  ";
		}
		stream << std::endl;
		l_or_r.clear();
	}

	return stream;
}

template<typename type>
std::istream& operator>>(std::istream& stream, SearchBinaryTree<type>& my_tree)
{
	std::string input;
	std::getline(stream, input);
	std::stringstream ss;
	ss << input;
	type buf;
	while (!ss.eof())
	{
		ss >> buf;
		ss.ignore(1);
		my_tree.add(buf);
	}
	return stream;
}
std::istream& operator>>(std::istream& stream, SearchBinaryTree<char>& my_tree)
{
	std::string input;
	std::getline(stream, input);
	std::stringstream ss;
	ss << input;
	char buf;
	while (ss >> buf)
	{
		my_tree.add(buf);
	}
	return stream;
}



int main() {

	SearchBinaryTree<char> tree;
	std::cin >> tree;
	std::cout << tree;
	tree.find('l');
	tree.Postorder(tree.begin());

	return 0;
}

