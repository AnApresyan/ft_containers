#ifndef RB_NODE_HPP
#define RB_NODE_HPP
#include <cstdio>

namespace ft
{
	typedef enum s_node_color
	{
		RED,
		BLACK
	}	node_color;

	class rb_base_node
	{
		public:

			rb_base_node(): right(NULL), left(NULL), p(NULL), color(RED) {}
			~rb_base_node() {}
			rb_base_node(const rb_base_node &other): right(other.right), left(other.left), p(other.p), color(other.color) {}
			rb_base_node &operator=(const rb_base_node &other)
			{
				this->right = other.right;
				this->left = other.left;
				this->p = other.p;
				this->color = other.color;
				return (*this);
			}
			
			rb_base_node		*right;
			rb_base_node		*left;
			rb_base_node		*p;
			node_color			color;
	};

	template <typename T>
	struct rb_node : public rb_base_node
	{
		T element;
	};
		
};

#endif