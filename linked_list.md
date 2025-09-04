## Concept of dummy head

- for not having to update head we use a dummy head, such that dummy = new Node(-1) and dummy -> next = head
- then do all the operations that involves changing head and return dummy -> next
- like when we need to delete head only at times like in removing nodes occuring more than once or when reversing k groups of linked list

## Reversing an LL

- using 3 pointers p, q, r where p is at head and q, r right behind p. for change in links, do r = q, q = p, q -> next = r, p = p -> next if p is not null. stop this when q becomes null.
- using recursion: nhead is the new head of the reverse LL.

```cpp
ListNode *rev(ListNode *node, ListNode* &nhead) {
    if(!node) return nullptr;
    ListNode *nn = rev(node, nhead);
    if(nn) nn -> next = node;
    else nhead = node;
    return node;
}
//at last after calling rev(head, nhead), do head -> next = nullptr;
```

## Slow and Fast Pointers

- fast and slow pointers in LL help in variety of problems:
  - find or detect cycle
  - find middle of LL
  - find length of loop in LL
  - find start of loop of LL by again shifting sp to head and moving fp and sp by 1 until they meet again
  - finding next to middle of LL by stopping fp when while(fp -> next && fp -> next -> next)

```cpp
ListNode *sp = head, *fp = head;
while(fp && fp -> next) {
    sp = sp -> next;
    fp = fp -> next -> next;
    if(sp == fp) return sp;
}
```

## Checking Palindrome:

- find the middle using sp, fp in LL.
- in even nodes the middle shud be the first middle
- that is move the loop till `while(fp -> next && fp -> next -> next)`. (fp -> next) for odd and (fp -> next -> next) for even
- reverse the LL from middle to end using the reverse function
- use first pointer at head and second at new heaed returned by reverse and make sp -> next as nullptr and start comparing first and second till either of them reaches null
- if ever first is not equal to second, then return false. else return true.

## Finding nth node from end

- to know which node is (total nodes - n) from start, we use a fp that is already moved n positions ahead from sp(at head).
- move fp till end and sp also, both by 1 poisition. when fp reaches end, sp is at the required node.
- its a neat trick.

## Sorting a Linked List

- first in O(n) space, we can copy in array, sort the array, then copy back the values but that would be in linear space
- using a top - down merge sort approach, but it also takes a recursive stack space of $O(logn)$
- lastly we can use a bottom - up approach, which takes constant space and is the most efficient one and the most difficult to implement as well: https://leetcode.com/problems/sort-list/submissions/1719629996, heres the code for it
- heres the youtube explanation: https://youtu.be/Mpjm_5wEBrM?si=IrPrkxw9kLrHkW1a
- watch from example: 32:26 timestamp
- basic idea is to use a two way merge sort, splitting the list into blocks of 1, 2, 4, 8, 16 and so on and merging those blocks like we merge 2 linked list
- first split it in blocks of 1 width, then merge 2 of them, then split next then merge
- next start over as width < lenght and split in blocks of 2 width, merge 2 of them, then split then merge again
- repeat this process until width >= length of the linked list

## Removing duplicates from sorted linked list

- two variations: where you need to remove the node only if its present more than once, and where you need to remove jst the duplicates
- removing just the duplicates is fairly easy
- for removing the elemneet itslef, use the dummy node for managin head
- use prev and curr nodes, start prev from dummy and curr from dummy -> next
- if curr is not equal to curr -> next, do prev = curr
- if curr's next is equal to curr, then move curr until its curr -> next != curr and then do prev -> next = curr -> next
- you need to check if curr -> next == curr once also, if that condition is true once too, then you need to do prev -> next = curr -> next, otherwuse just prev = curr and move curr by one in both cases
- for checking if curr -> next == curr once too, use a flag variable, make it true if the conditoin is true and keep moving curr till its true
- if flag is true use prev -> next = curr -> next, else prev = curr and move curr by one

## Sorting a linked list of 0s, 1s, 2s

- use different heads for each linked list and different tails too
- use a temp var for traversing in the linked list
- if the temp's val is 0, then zero -> next = temp, zero = temp, do same for 1 and 2 too and at the end temp = temp -> next
- then link the heads of all 3 linked lists by:

```cpp
zero -> next = one -> next ? one -> next : two -> next ? two -> next : nullptr;
one -> next = two -> next ? two -> next : nullptr;
two -> next = nullptr;
```

- amd then lastly head = zeroHead -> next
- return head

## Finding intersection point of two linked lists

- have pa at heada, pb at headb
- while pa != pb, if pa is null, make pa = headb, else pa = pa -> next
- same for pb, if pb is null, make pb = heada, else pb = pb -> next
- when pa == pb, return pa or pb
- if pa is null, it means there was no intersection point
- this works as till the point the smaller linked list finishes and larger one still moves, the smaller linked list pointer moves as many times as larger pointer takes to reach the end of the list
- after pa and pb interchange their lists, pa and pb start from the same point only, hence they reach the intersection point or null(in case of no intersection) at the same time

## Reversing groups of size k in a linked list:

- see the leetcode solution for this one which i have written
- in the solution you will see that, first we have created a dummy so that head can be manipulated
- next we are having temp as heads of chunks of linked list we are breaking and reversing
- we are also having a prev pointer to which prev -> next = temp to join those chunks after reversal
- we are having a next pointer that points to the head of next chunk so that temp can be updated to this node after reversal
- we have a knode that is the node ahead of temp by k, useful for loop termination and mainly for updating the next so that temp can be updated to this node

## Rotating Linked List

- same concept as array
- reverse the array from 0 to k-1 and then from k to n-1
- then reverse the whole array
- likewise, use sp and fp concept to move sp to the node kth last node, (same concept used in removing nth last node)
- then reverse from head to sp
- then reverse from sp -> next to end
- then reverse from head to end
- here too use the dummy head concept

## Creating deepy copy of LL with random pointers:

- first approach is to use a map of oldNode to newNode
- then traverse the LL and update newNode[temp] -> next = newNode[temp -> next] and newNode[temp] -> random = newNode[temp -> random]
- return the new head

- second approach that does not use extra space is to copy the nodes between two original nodes creating an interweaved LL
- that is let the LL be 7 -> 13 -> 11 then create new nodes and LL will be 7 -> new7 -> 13 -> new13 -> 11 -> new11 -> nullptr
- then in the first loop update the random pointers, while(p), if(p -> random) then t -> random = p -> random -> next, otherwise t -> random = nullptr where t = p -> next;
- in the next loop we update the next pointers, for which we create a dummy node and start pointing to res -> next = p -> next, res = res -> next, p -> next = res -> next and p = p -> next -> next
- where res points to dummy at the beginning
- do this until p is null

## Merging two sorted LL in place

- use the similar concept of sorting 0s, 1s, 2s
- make a dummy node and a tail pointer = dummy
- have two pointers p and q for the two heads
- if(p -> val < q -> val) then tail -> next = p, tail = p, p = p -> next;
- else for q do the same
- return dummy -> next
- hence no need to create new nodes for merging

## Merging k sorted LL in place

- first approach is using extra O(n) space
