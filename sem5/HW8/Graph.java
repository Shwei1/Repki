import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

public class Graph {
    private Map<Integer, Set<Integer>> edges;
    private int nextID;

    public Graph(){
        this.edges = new HashMap<>();
        this.nextID = 0;
    }

    public void addVertex(){
        int id = nextID++;
        edges.put(id, new HashSet<>());
    }

    public boolean removeVertex(int u){
        if (edges.get(u) == null) return false;

        for (int v: edges.get(u)){
            removeEdge(u, v);
            removeEdge(v, u);
        }
        edges.remove(u);
        return true;
    }

    public void addEdge(int u, int v){
        edges.putIfAbsent(u, new HashSet<>());
        edges.putIfAbsent(v, new HashSet<>());

        edges.get(u).add(v);
        edges.get(v).add(u);
    }

    public boolean removeEdge(int u, int v){
        if (edges.containsKey(u) && edges.containsKey(v)){
            edges.get(u).remove(v);
            edges.get(v).remove(u);
            return true;
        }
        else 
            return false;
    }
}
