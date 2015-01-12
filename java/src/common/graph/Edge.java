package common.graph;

public class Edge {
    
    private int begin;
    private int end;
    private int value;

    public int getBegin() {
        return begin;
    }

    public void setBegin(int begin) {
        this.begin = begin;
    }

    public int getEnd() {
        return end;
    }

    public void setEnd(int end) {
        this.end = end;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }


    public Edge(){
        this.begin=0;
        this.end=0;
        this.value=0;
    }

    public Edge(int begin, int end, int value) {
        this.begin = begin;
        this.end = end;
        this.value = value;
    }

    public Edge(Edge e){
        this.begin = e.begin;
        this.end = e.end;
        this.value = e.value;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Edge other = (Edge) obj;
        if (this.begin != other.begin) {
            return false;
        }
        if (this.end != other.end) {
            return false;
        }
        if (this.value != other.value) {
            return false;
        }
        return true;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 23 * hash + this.begin;
        hash = 23 * hash + this.end;
        hash = 23 * hash + this.value;
        return hash;
    }

    public boolean isLessThan (Edge e){
        Edge first = normalize(this);
        Edge secnd = normalize(e);

        return first.begin < secnd.begin || (first.begin == secnd.begin && first.end < secnd.end);
    }

    private Edge normalize(Edge edge) {
        if (edge.begin < edge.end)
            return edge;
        else
            return new Edge(edge.end, edge.begin, edge.value);
    }

}