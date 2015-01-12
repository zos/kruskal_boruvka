package containers;

import java.util.Arrays;

/**
 *
 * @author Jakub Kitaj
 */
public class MyVector<T> {

    private static final int DEFAULT_SIZE = 10;

    private int size = 0;
    private Object[] tab;

    public MyVector() {
        tab = new Object[DEFAULT_SIZE];
    }

    public MyVector(Object[] array, int size) {
        this.tab = array;
        this.size = size;
    }
    
    public void add (T t){
        if (size == tab.length) {
            upSize();
        }  
        tab[size++] = t;
    }
    
    public void putOn (T t, int index){
        if(index>0 && index<size){
            if (size == tab.length) {
                upSize();
            }  
            tab[index] = t;
            size = size++;
        }
    }
    
    private void upSize() {
        int newSize = tab.length * 2;
        tab = Arrays.copyOf(tab, newSize);
    }


    public int size() {
        return size;
    }

    
    public void resize(int newSize) {
        if(newSize > size){
            upSize();
        }
            
        size = newSize;
    }
    
    public T get(int index) {
        if (index>= size || index <0) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size " + index);
        }

        return (T) tab[index];
    }
    
    public int getIndex(T t) {
        for(int i=0; i<this.size; i++)
            if(this.tab[i].equals(t))
                return i;
        return -1;
    }
    
    public T remove (T t){
        int idx = getIndex(t);
        if(idx > -1){
            Object[] oldTab = tab;
            tab = Arrays.copyOfRange(oldTab, 0, idx);
            if(idx != oldTab.length-1){    //jesli usuwany jest nie oststanim element
                Object[] restTab = Arrays.copyOfRange(oldTab, idx+1, oldTab.length);
                tab = Arrays.copyOf(tab, tab.length+restTab.length);
                for(int i=0; i<restTab.length; i++)
                    tab[idx+i] = restTab[i];
            }
            size = size - 1;
            return (T) oldTab[idx];
        }  
        return null;
    }
    
    public boolean contain (T t){
        for(int i=0; i<this.size; i++)
            if(this.tab[i].equals(t))
                return true;
        
        return false;
    }
}