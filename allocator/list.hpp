#ifndef LIST_HPP
#define LIST_HPP

namespace tsk {
    template <class T>
    class list {
    private:
	struct node {
	    T data;
	    node *next;
	};

	node *head = nullptr;

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
	void push_front(const T &data) {
	    node *new_head = new node;
	    new_head->data = data;
	    new_head->next = head;
	    head = new_head;
	}

	~list() {
	    for (node *p = head; p != nullptr; ) {
		p = head->next;
		delete head;
		head  = p;
	    }
	}

    };
}

#endif /* LIST_HPP */
