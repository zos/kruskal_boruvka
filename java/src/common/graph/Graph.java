package common.graph;

import containers.MyLinkedList;
import containers.MyVector;



/**
 *
 * @author Jakub Kitaj
 */
public class Graph {
    
    private MyLinkedList<Edge> edgeSet;
    private int edgeAmount;
    private int vertexAmount;

    public MyLinkedList<Edge> getEdgeSet() {
        return edgeSet;
    }

    public void setEdgeSet(MyLinkedList<Edge> edgeSet) {
        this.edgeSet = edgeSet;
    }

    public int getEdgeAmount() {
        return edgeAmount;
    }

    public void setEdgeAmount(int edgeAmount) {
        this.edgeAmount = edgeAmount;
    }

    public int getVertexAmount() {
        return vertexAmount;
    }

    public void setVertexAmount(int vertexAmount) {
        this.vertexAmount = vertexAmount;
    }
    
    public Graph(){
        edgeSet = new MyLinkedList<Edge>();
        edgeAmount = 0;
        vertexAmount = 0;
    }

    public Graph(MyLinkedList<Edge> edgeSet, int edgeAmount, int vertexAmount) {
        this.edgeSet = edgeSet;
        this.edgeAmount = edgeAmount;
        this.vertexAmount = vertexAmount;
    }
    
    public MyVector<MyLinkedList<Edge>> getNeighbourhoodList() {
        Object[] tab = new Object[vertexAmount];
        for(int c=0; c<vertexAmount; c++)
            tab[c] = new  MyLinkedList<>();
        MyVector<MyLinkedList<Edge>> list = new MyVector<>(tab, vertexAmount);
        list.resize(vertexAmount);
        for (int i=0; i<edgeSet.size(); i++) {
            Edge edg = edgeSet.get(i);
            list.get(edg.getBegin()-1).addItem(edg);
            list.get(edg.getEnd()-1).addItem(new Edge(edg.getEnd(), edg.getBegin(), edg.getValue()));
        }
        return list;
    }
    
    public MyVector<MyVector<Integer>> getNeighbourhoodMap() {
        Object[] column = new Object[vertexAmount];
        Object[] rows = new Object[vertexAmount];
        for(int c=0; c<vertexAmount; c++)
            column[c] = new  MyVector<>(rows, vertexAmount);
        MyVector<MyVector<Integer>> map = new MyVector<>(column, vertexAmount);

        for (int j=0; j<edgeSet.size(); j++) {
            Edge edge = edgeSet.get(j);
            map.get(edge.getBegin()-1).putOn(edge.getValue(), edge.getBegin());
            map.get(edge.getEnd()-1).putOn(edge.getValue(), edge.getBegin());
        }
        return map;
    }
    
    public void printGraph() {
        MyVector<MyLinkedList<Edge>> list = getNeighbourhoodList();
        int vertexes = getVertexAmount();
        
        for (int i = 0; i < vertexes; i++) {
            System.out.print(i+1 + " : ");
            MyLinkedList<Edge> edges = list.get(i);
            for (int j=0; j<edges.size(); j++) {
                Edge e = edges.get(j);
                System.out.print(e.getEnd() + " <" + e.getValue() + ">, ");
            }
            System.out.println();
        }
    }
}
