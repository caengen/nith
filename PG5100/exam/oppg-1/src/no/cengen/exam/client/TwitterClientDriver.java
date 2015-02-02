package no.cengen.exam.client;

import no.cengen.exam.server.TwitterServerIF;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

/**
 * User: Cengen
 * Date: 02/12/13
 * Time: 13:02
 */
public class TwitterClientDriver {

    public static void main(String[] args) throws RemoteException, NotBoundException, MalformedURLException {
        String twitterServerURL = "rmi://localhost/TwitterServer";
        TwitterServerIF twitterServer = (TwitterServerIF) Naming.lookup(twitterServerURL);
        new Thread(new TwitterClient(args[0], twitterServer)).start();

    }
}
