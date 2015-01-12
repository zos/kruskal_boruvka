
import common.graph.Edge;
import common.graph.Graph;
import containers.MyLinkedList;
import containers.MyVector;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author jakub
 */
public class Main {
    public static void main(String[] args){
        MyLinkedList<Integer> my = new MyLinkedList<Integer>();
        for(int i=0; i<10; i++){
            my.addItem(i);
        }

        for(int e=0; e<my.size(); e++)
            System.out.print(my.get(e) + " ");

                
        System.out.println("\nremoved: "+my.removeItem(0)+"\n");
        
        for(int e=0; e<my.size(); e++)
            System.out.print(my.get(e) + " ");
     
        Edge tab[] = new Edge[] {new Edge(1, 2, 1), 
            new Edge(2, 3, 2), new Edge(3, 4, 6),
            new Edge(1, 4, 8)};
        
        MyLinkedList<Edge> r = new MyLinkedList<>(tab);
        Graph g = new Graph(r, r.size(), 4);
        
        MyVector<MyLinkedList<Edge>> neighbourhoodList = g.getNeighbourhoodList();
        
        g.printGraph();
        
        MyVector<MyVector<Integer>> neighbourhoodMap = g.getNeighbourhoodMap();
        
        for(int i=0; i<neighbourhoodMap.size(); i++){
            for(int j=0; j<neighbourhoodMap.get(i).size(); j++)
                System.out.print(" <" + neighbourhoodMap.get(i).get(j) + "> ");
            System.out.println();
        }
    }
    
}
