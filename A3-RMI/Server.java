import java.rmi.*;

class Server {

    public static void main (String[] argv) {
        try { 
            Naming.rebind("rmi://localhost/getCount", new Counter(0)); 
        }
        catch (Exception e) { }
    }
}
