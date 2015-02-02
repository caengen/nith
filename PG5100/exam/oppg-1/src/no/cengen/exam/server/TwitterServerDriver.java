package no.cengen.exam.server;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;

/**
 * User: Cengen
 * Date: 02/12/13
 * Time: 13:03
 */
public class TwitterServerDriver {
    public static void main(String [] args) throws RemoteException, MalformedURLException {
        Naming.rebind("TwitterServer", new TwitterServer());
    }
}
