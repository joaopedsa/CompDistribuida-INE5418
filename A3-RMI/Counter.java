import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject; 
import java.util.concurrent.Semaphore;

public class Counter extends UnicastRemoteObject implements CounterInterface {
    
    private int count;
    static Semaphore semaphore = new Semaphore(1);
    
    public Counter(int count) throws RemoteException, InterruptedException {
        semaphore.acquire();
        this.count = count;
        semaphore.release();
    }

    public int getCount() throws RemoteException {
        return ++this.count;
    }
}
