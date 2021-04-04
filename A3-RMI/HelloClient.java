import java.rmi.Naming;

class HelloClient extends Thread { 
    public static void main (String[] args) { 
        CounterInterface counter;
        int count;
        try {
            counter = (CounterInterface)Naming.lookup("rmi://localhost/getCount");
            while(true) {
                Thread.sleep(1000);
                count = counter.getCount();
                System.out.println(count);
            }
        } catch (Exception e) {
            System.out.println(e);
        } 
    } 
}