#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>
namespace tsk {
    template <class T, class Allocator = std::allocator<T>>
    class list {
    private:
	struct node {
	    node(T && data_, node* next_) :
		next(next_), data(std::move(data_)) {}
	    node *next;
	    T data;
	};

	node *head = nullptr;
	// using node_allocator = typename std::allocator_traits<Allocator>:: template rebind_alloc<node> ;
	using node_allocator = typename Allocator:: template rebind<node>::other;
	node_allocator a;
    public:
	class iterator {
	public:
	    iterator(node *node_p) : current(node_p) {}
	    iterator& operator++() {
		current = current->next;
		return *this;
	    }
	    T& operator*() {
		return current->data;
	    }
	    bool operator!=(const iterator &other) {
		return current != other.current;
	    }
	private:
	    node *current;
	};
	iterator begin() {
	    return iterator{head};
	}
	iterator end() {
	    return iterator{nullptr};
	}
	void push_front(T && data) {
	    // node *new_head = new node;
	    auto new_head = a.allocate(1);

	    // new_head->data = data;
	    // new_head->next = head;
	    a.construct(new_head, std::move(data), head);
	    head = new_head;
	}

	~list() {
	    for (node *p = head; p != nullptr; ) {
		p = head->next;
		// delete head;
		a.destroy(head);
		a.deallocate(head, 1);
		head  = p;
	    }
	}

    };
}

#endif /* LIST_HPP */
