package queue

import "fmt"

type any interface{}

type Queue struct {
	elements []any
}

func New() *Queue { return new(Queue) }

func (q *Queue) Enqueue(element any) {
	q.elements = append(q.elements, element)
}

func (q *Queue) Dequeue() (any, error) {
	if len(q.elements) == 0 {
		return nil, fmt.Errorf("queue is empty")
	}
	firstElement := q.elements[0]
	q.elements = q.elements[1:]
	return firstElement, nil
}

func (q *Queue) Size() int {
	return len(q.elements)
}
