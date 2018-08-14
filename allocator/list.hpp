#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>

namespace tsk {
    template <class T, class Allocator = std::allocator<T>>
    class list {
    private:
        struct node {
            template<class... Args>
            node(node* next_, Args&& ... args) :
                next(next_), data(std::forward<Args>(args)...) {
                std::printf("node's address = %p\n", this);
            }
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

        template <class U>
        void push_front(U && data) {
            auto new_head = a.allocate(1);
            a.construct(new_head, head, std::forward<U>(data));
            head = new_head;
        }

        template<class ... Args>
        void emplace_back(Args&& ... args) {
            auto new_head = a.allocate(1);
            a.construct(new_head, head, std::forward<Args>(args)...);
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
