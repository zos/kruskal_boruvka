package containers;

public class MyLinkedList<T>{

    private ListItem<T> head;
    
  
    public MyLinkedList() {
    }

    public MyLinkedList(T item) {
        if(item != null)
            head=new ListItem(item);         
    }

    // Construct a linked list from an array of objects
    public MyLinkedList(T[] items) {
        if(items != null) {
            for (T item : items) {
                addItem(item);
            }
        }
    }

    public T get(int indx) {
        ListItem<T> curr = head;
        for(int i=0; i<indx; i++)
            if(curr!=null)
                curr = curr.next;
            else
                return null;
        
        return curr.item;
    }
        
    public int size(){
        int s=0;
        ListItem curr = head;
        while(curr!=null){
            s++;
            curr = curr.next;
        }
        return s;
    }
    
    public void addItem(T item) {
        ListItem newEnd = new ListItem(item);       
        if(head == null)                           
            head = newEnd;                   
        else {
            ListItem curr = head;
            ListItem last = head;
            while(curr!=null){
                last = curr;
                curr = curr.next;
            }
            
            newEnd.prev = last;
            last.next = newEnd;                                                  
        }
    }
    
    public T removeItem(T item) {
        ListItem<T> toRemove = head;
        while(toRemove!=null){
            if(!toRemove.item.equals(item))
                toRemove = toRemove.next;
            else{
                ListItem<T> prevItem = toRemove.prev;
                ListItem<T> nextItem = toRemove.next;
                if(prevItem!=null)
                    prevItem.next = nextItem;
                else
                    head = nextItem;
                if(nextItem!=null)
                    nextItem.prev = prevItem;
                return toRemove.item;
            } 
        }
        return null;
    }    
            
    public T getFirst() {
        return head == null ? null : head.item;
    }
     
    private class ListItem<T> {
        private ListItem<T> next;               // Refers to next item in the list
        private ListItem<T> prev;               // Refers to prev item in the list
        private T item;                         // The item for this ListItem
        
        public ListItem(T item) {
            this.item = item;                  // Store the item
            next = null;                       
            prev = null;
        }
    }
}