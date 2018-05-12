#ifndef LIST_HPP
#define LIST_HPP

namespace tsk {
    template <class T>
    class list {
    public:
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

    private:
	struct node {
	    T data;
	    node *next;
	};

	node *head = nullptr;
    };
}

#endif /* LIST_HPP */
