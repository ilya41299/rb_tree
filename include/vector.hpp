#include <iostream>
#include <algorithm>
#include <cassert>


template <typename T>
class rb_tree {
	struct node_t {
		node_t * left;
		node_t * right;
		node_t * parent;
		bool color; // 0 - black, 1 - red
		T value;
	};
	node_t *root_;
public:
	rb_tree();
	node_t* root()
	{
		return root_;
	}
	void check_operator(std::ostream& stream, char op, T value);
	void insert(T value);
	bool find(T value) const;
	bool equal(node_t* a, node_t* b) const;
	void print(std::ostream& stream, int level, node_t* node);
	void destroy(node_t* node);
	~rb_tree();
	rb_tree(std::initializer_list<T> keys);
	auto operator==(rb_tree const & other) const;
	bool isEmpty()
	{
		if (root_ == nullptr)
		{
			return true;
		}
		return false;
	}
	node_t * grandparent(node_t * n) 
	{
		if (n != nullptr && n->parent != nullptr) 
		{
			return n->parent->parent;
		}
		else return nullptr;
	}
	node_t * uncle(node_t * n)
	{
		node_t * grand = grandparent(n);
		if (grand == nullptr) 
		{
			return nullptr; // если не существует grand, то нет и uncle
		}
		else if (n->parent == grand->left) 
		{
			return grand->right;
		}
		else return grand->left;
	}

	void rotate_left(node_t *n)
	{
		struct node *vetka = n->right;

		vetka->parent = n->parent; /* при этом, возможно, vetka становится корнем дерева */
		if (n->parent != nullptr) { // если у n есть отец
			if (n->parent->left == n) // и n-его левый сын
				n->parent->left = vetka; // перенаправим левый указатель отца на временный элемент
			else // если же n-правый сын
				n->parent->right = vetka; // перенаправим правый указатель отца на временный элемент
		}

		n->right = vetka->left; // переопределип правый указатель для n
		if (vetka->left != nullptr) // и если временный имеет левого сына
			vetka->left->parent = n; // то его отцом станет n

		n->parent = vetka; // отцом для n становится временный элемент
		vetka->left = n; // и левый указатель временного направляем на наш n  
	}

	void rotate_right(node_t *n) 
	{
		 node_t *vetka = n->left;

		vetka->parent = n->parent; 
		if (n->parent != nullptr) {
			if (n->parent->left == n)
				n->parent->left = vetka;
			else
				n->parent->right = vetka;
		}

		n->left = vetka->right;
		if (vetka->right != nullptr)
			vetka->right->parent = n;

		n->parent = vetka;
		vetka->right = n;
	}

	//*dd
	d
	*//

};

template <typename T>
void rb_tree<T>::insert(T value)
{
// Вставка в пустое дерево. Достаточно вставить чёрный элемент 
	if (root_ == nullptr) 
	{
		node_t* node = new node_t;
		node->value = value;
		node->right = nullptr;
		node->left = nullptr;
		root_->parent = nullptr;
		node->color = false;
		root_ = node;
	}

	//Иначе происходит поиск места для вставка красного элемента
	else
	{
		node_t* vetka = root_; 
		while (vetka != nullptr)
		{
			if (vetka->value > value)
			{
				// если левый сын отсутствует
				if (vetka->left==nullptr) 
				{
					vetka->left = new node_t; //выделяем память и заполняем структуру элемента
					vetka->left->parent = vetka;
					vetka = vetka->left;
					vetka->value = value;
					vetka->right = nullptr;
					vetka->left = nullptr;
					vetka->value = value;
					vetka->color = true;
					insert_case1(vetka); //вызываем функцию для возможной перекраски или поворота
					return;
				}
				else 
				{
					vetka = vetka->left;
				};
			}
			else if (vetka->value <= value)
			{
				if (vetka->right==nullptr) 
				{
					vetka->right = new node_t;
					vetka->right->parent = vetka;
					vetka = vetka->left;
					vetka->value = value;
					vetka->right = nullptr;
					vetka->right = nullptr;
					vetka->value = value;
					vetka->color = true;
					insert_case1(vetka);
					return;
				};
				else vetka = vetka->right;
			}
		}
	}
}



template <typename T>
rb_tree<T>::rb_tree(std::initializer_list<T> keys)
{
	root_ = nullptr;
	int n = keys.size();
	const int* _ptr = keys.begin();
	for (int i = 0; i < n; i++)
	{
		insert(_ptr[i]);
	}
}

template <typename T>
rb_tree<T>::rb_tree()
{
	root_ = nullptr;
}

template <typename T>
rb_tree<T>::~rb_tree()
{
	destroy(root_);
}

template <typename T>
void rb_tree<T>::check_operator(std::ostream& stream, char op, T value)
{
	switch (op)
	{
	case '+':
	{
		insert(value);
		break;
	}
	case '?':
	{
		if (find(value))
		{
			stream << "true";
		}
		else stream << "false";
		break;
	}
	case '=':
	{
		print(stream, 0, root_);
		break;
	}
	case 'q':
	{
		exit(0);
		break;
	}
	default:
	{
		stream << "Error of use operator";
	}
	}
}

template <typename T>
void rb_tree<T>::print(std::ostream& stream, int level, node_t* node)
{
	if (node == nullptr)
		return;

	print(stream, level + 1, node->right);

	for (size_t i = 0; i < level; i++)
	{
		stream << "---";
	}
	stream << node->value << std::endl;

	print(stream, level + 1, node->left);
}

template <typename T>
bool rb_tree<T>::find(T value) const
{
	node_t* node = root_;
	while (node != nullptr)
	{
		if (node->value == value)
		{
			return true;
		}
		else
		{
			if (value <= node->value)
			{
				node = node->left;
			}
			else
				node = node->right;
		}
	}
	return false;
}

template <typename T>
void rb_tree<T>::destroy(node_t* node)
{
	if (node != nullptr)
	{
		if (node->left)
		{
			destroy(node->left);
		}
		if (node->right)
		{
			destroy(node->right);
		}
		delete node;
	}
}

template <typename T>
bool rb_tree<T>::equal(node_t* first, node_t* second) const {
	if (first == nullptr && second == nullptr) return(true);
	else if (first != nullptr && second != nullptr)
	{
		return(
			first->value == second->value &&
			equal(first->left, second->left) &&
			equal(first->right, second->right)
			);
	}
	else return false;
}

template <typename T>
auto rb_tree<T>::operator==(rb_tree const & other) const {
	node_t* first = root_; node_t* second = other.root_;
	return (equal(first, second));
}
