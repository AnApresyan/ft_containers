#ifndef RB_NODE_HPP
#define RB_NODE_HPP

namespace ft
{
	typedef enum s_node_color
	{
		RED,
		BLACK
	}	node_color;

	template <typename T>
	class rb_node
	{
		public:

			rb_node(): element(), right(NULL), left(NULL), p(NULL), color(RED) {}
			~rb_node() {}
			rb_node(const rb_node &other): element(other.element), right(other.right), left(other.left), p(other.p), color(other.color) {}
			rb_node(const T &element): element(element), right(NULL), left(NULL), p(NULL), color(RED) {}
			rb_node &operator=(const rb_node &other)
			{
				this->element = other.element;
				this->right = other.right;
				this->left = other.left;
				this->p = other.p;
				this->color = other.color;
				return (*this);
			}
			
			T 			element;
			rb_node		*right;
			rb_node		*left;
			rb_node		*p;
			node_color	color;
	};
};

#endif